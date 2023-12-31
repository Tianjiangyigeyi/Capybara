//#type compute
#version 450 core
// 这个着色器是用于通过GGX NDF重要性采样来预过滤环境立方体贴图的。它是用于镜面IBL（Image-Based Lighting）的分裂和求和近似的一部分：
// 
// 1. 定义了一些常量和变量，如PI、TwoPI、Epsilon、NumSamples和InvNumSamples。
// 2. 声明了输入和输出的纹理单元，并设置了绑定点。
// 3. 实现了Van der Corput反序列化和Hammersley点集采样函数。
// 4. 实现了固定粗糙度值的GGX法线分布函数的重要性采样函数。
// 5. 实现了获取立方体贴图纹理坐标的函数。
// 6. 实现了计算从切线/着色空间到世界空间的正交基的函数。
// 7. 实现了从切线/着色空间到世界空间的转换函数。
// 8. 在主函数中，首先检查当前线程是否在输出纹理范围内，以避免写入超出范围的数据。
// 9. 计算单个立方体贴图纹素在零级mipmap上的固定立体角。
// 10. 计算切线/着色空间中的法线方向N，并将其设置为观察方向Lo。
// 11. 计算切线/着色空间的正交基S和T。
// 12. 初始化颜色和权重变量。
// 13. 使用GGX NDF重要性采样方法对环境贴图进行卷积。
// 14. 根据余弦项进行加权，因为它通常可以提高质量。
// 15. 在每个样本上计算反射方向Li，通过将观察方向Lo绕半向量Lh进行反射。
// 16. 计算Li与法线方向N的余弦值。
// 17. 如果余弦值大于0，则使用多级贴图过滤重要性采样来提高收敛性。
// 18. 计算样本的固定立体角和概率密度函数。
// 19. 计算采样的mip级别。
// 20. 根据权重和余弦值对颜色进行累加。
// 21. 最后，将归一化的颜色存储到输出纹理中。
// 
// 总体上，这个着色器实现了对环境立方体贴图进行GGX NDF重要性采样的预过滤操作，以用于镜面IBL的分裂和求和近似。

const float PI = 3.141592;
const float TwoPI = 2 * PI;
const float Epsilon = 0.00001;

const uint NumSamples = 1024;
const float InvNumSamples = 1.0 / float(NumSamples);

const int NumMipLevels = 1;
layout(binding = 0) uniform samplerCube inputTexture;
layout(binding = 0, rgba16f) restrict writeonly uniform imageCube outputTexture[NumMipLevels];

// Roughness value to pre-filter for.
layout(location=0) uniform float roughness;

#define PARAM_LEVEL     0
#define PARAM_ROUGHNESS roughness

// Compute Van der Corput radical inverse
// See: http://holger.dammertz.org/stuff/notes_HammersleyOnHemisphere.html
float radicalInverse_VdC(uint bits)
{
	bits = (bits << 16u) | (bits >> 16u);
	bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
	bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
	bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
	bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
	return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}

// Sample i-th point from Hammersley point set of NumSamples points total.
vec2 sampleHammersley(uint i)
{
	return vec2(i * InvNumSamples, radicalInverse_VdC(i));
}

// Importance sample GGX normal distribution function for a fixed roughness value.
// This returns normalized half-vector between Li & Lo.
// For derivation see: http://blog.tobias-franke.eu/2014/03/30/notes_on_importance_sampling.html
vec3 sampleGGX(float u1, float u2, float roughness)
{
	float alpha = roughness * roughness;

	float cosTheta = sqrt((1.0 - u2) / (1.0 + (alpha*alpha - 1.0) * u2));
	float sinTheta = sqrt(1.0 - cosTheta*cosTheta); // Trig. identity
	float phi = TwoPI * u1;

	// Convert to Cartesian upon return.
	return vec3(sinTheta * cos(phi), sinTheta * sin(phi), cosTheta);
}

// GGX/Towbridge-Reitz normal distribution function.
// Uses Disney's reparametrization of alpha = roughness^2.
float ndfGGX(float cosLh, float roughness)
{
	float alpha   = roughness * roughness;
	float alphaSq = alpha * alpha;

	float denom = (cosLh * cosLh) * (alphaSq - 1.0) + 1.0;
	return alphaSq / (PI * denom * denom);
}

vec3 GetCubeMapTexCoord()
{
    vec2 st = gl_GlobalInvocationID.xy / vec2(imageSize(outputTexture[PARAM_LEVEL]));
    vec2 uv = 2.0 * vec2(st.x, 1.0 - st.y) - vec2(1.0);

    vec3 ret;
    if (gl_GlobalInvocationID.z == 0)      ret = vec3(  1.0, uv.y, -uv.x);
    else if (gl_GlobalInvocationID.z == 1) ret = vec3( -1.0, uv.y,  uv.x);
    else if (gl_GlobalInvocationID.z == 2) ret = vec3( uv.x,  1.0, -uv.y);
    else if (gl_GlobalInvocationID.z == 3) ret = vec3( uv.x, -1.0,  uv.y);
    else if (gl_GlobalInvocationID.z == 4) ret = vec3( uv.x, uv.y,   1.0);
    else if (gl_GlobalInvocationID.z == 5) ret = vec3(-uv.x, uv.y,  -1.0);
    return normalize(ret);
}

/* 这段代码是用来计算从切线/着色空间到世界空间的正交基向量。它使用了给定的法线向量N来计算切线向量S和副切线向量T。具体的计算步骤如下： 
 * 
 * 1. 初始化副切线向量T为与N垂直的向量(0.0, 1.0, 0.0)的叉乘结果。 
 * 2. 使用混合函数(mix)来选择非退化的副切线向量T。如果T与自身的点积大于一个很小的阈值(Epsilon)，则选择与N叉乘的结果作为新的T值。 
 * 3. 对副切线向量T进行归一化。 
 * 4. 计算切线向量S，它是N和T的叉乘结果，并对其进行归一化。 
 *  
 * 这样就可以得到一个从切线/着色空间到世界空间的正交基向量(S, T, N)。
 */
void computeBasisVectors(const vec3 N, out vec3 S, out vec3 T)
{
	// Branchless select non-degenerate T.
	T = cross(N, vec3(0.0, 1.0, 0.0));
	T = mix(cross(N, vec3(1.0, 0.0, 0.0)), T, step(Epsilon, dot(T, T)));

	T = normalize(T);
	S = normalize(cross(N, T));
}

// Convert point from tangent/shading space to world space.
vec3 tangentToWorld(const vec3 v, const vec3 N, const vec3 S, const vec3 T)
{
	return S * v.x + T * v.y + N * v.z;
}

layout(local_size_x=32, local_size_y=32, local_size_z=1) in;
void main(void)
{
	// 确保写入的是正确的mipmap
	ivec2 outputSize = imageSize(outputTexture[PARAM_LEVEL]);
	if(gl_GlobalInvocationID.x >= outputSize.x || gl_GlobalInvocationID.y >= outputSize.y) {
		return;
	}
	
	// Solid angle associated with a single cubemap texel at zero mipmap level.
	// This will come in handy for importance sampling below.
	vec2 inputSize = vec2(textureSize(inputTexture, 0));
	float wt = 4.0 * PI / (6 * inputSize.x * inputSize.y);
	
	// 采样的方向向量归一化到球面
	vec3 N = GetCubeMapTexCoord();
	vec3 Lo = N;
	
	// 切线空间，N法线，S切线，T副切线
	vec3 S, T;
	computeBasisVectors(N, S, T);

	vec3 color = vec3(0);
	float weight = 0;

	// Convolve environment map using GGX NDF importance sampling.
	// Weight by cosine term since Epic claims it generally improves quality.
	for(uint i = 0; i < NumSamples; i++) {
		// Hammersley采样，就是利用计算机使用二进制表示的特性，来构造均匀分布的2D随机采样点。
		vec2 u = sampleHammersley(i);
		vec3 Lh = tangentToWorld(sampleGGX(u.x, u.y, PARAM_ROUGHNESS), N, S, T);

		// Compute incident direction (Li) by reflecting viewing direction (Lo) around half-vector (Lh).
		vec3 Li = 2.0 * dot(Lo, Lh) * Lh - Lo;

		float cosLi = dot(N, Li);
		if(cosLi > 0.0) {
			// Use Mipmap Filtered Importance Sampling to improve convergence.
			// See: https://developer.nvidia.com/gpugems/GPUGems3/gpugems3_ch20.html, section 20.4

			float cosLh = max(dot(N, Lh), 0.0);

			// GGX normal distribution function (D term) probability density function.
			// Scaling by 1/4 is due to change of density in terms of Lh to Li (and since N=V, rest of the scaling factor cancels out).
			float pdf = ndfGGX(cosLh, PARAM_ROUGHNESS) * 0.25;

			// Solid angle associated with this sample.
			float ws = 1.0 / (NumSamples * pdf);

			// Mip level to sample from.
			float mipLevel = max(0.5 * log2(ws / wt) + 1.0, 0.0);

			color  += textureLod(inputTexture, Li, mipLevel).rgb * cosLi;
			weight += cosLi;
		}
	}
	color /= weight;

	imageStore(outputTexture[PARAM_LEVEL], ivec3(gl_GlobalInvocationID), vec4(color, 1.0));
}
