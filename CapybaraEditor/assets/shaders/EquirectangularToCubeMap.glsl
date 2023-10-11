//#type compute
#version 450 core

// Converts equirectangular (lat-long) projection texture into a cubemap
layout(binding = 0) uniform sampler2D u_EquirectangularTex;
layout(binding = 0, rgba16f) restrict writeonly uniform imageCube o_CubeMap;
layout(local_size_x = 32, local_size_y = 32, local_size_z = 1) in;

const float PI = 3.141592;

// 采样的方向向量归一化到球面
vec3 GetCubeMapTexCoord()
{
//    glDispatchCompute(cubemapSize / 32, cubemapSize / 32, 6);
    vec2 st = gl_GlobalInvocationID.xy / vec2(imageSize(o_CubeMap));
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

void main()
{
    // 变换得到theta和phi角
	vec3 cubeTC = GetCubeMapTexCoord();
    // Calculate sampling coords for equirectangular texture
	// https://en.wikipedia.org/wiki/Spherical_coordinate_system#Cartesian_coordinates
	float phi = atan(cubeTC.z, cubeTC.x);
	float theta = acos(cubeTC.y);
    // 把这两个角度变换到0到1，到HDR图中去采样
    vec2 uv = vec2(phi / (2.0 * PI) + 0.5, theta / PI);
	vec4 color = texture(u_EquirectangularTex, uv);
	imageStore(o_CubeMap, ivec3(gl_GlobalInvocationID), color);
}
