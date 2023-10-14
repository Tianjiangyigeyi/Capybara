# C++游戏引擎—Capybara

developing...🛠️（这不是最终的项目文档，仅仅只是过程中的一些记录）

> 关于**Capybara**名字的由来，那天我问我npy：“我现在在做一个很伟大的项目，你帮我想一个牛逼的英文名吧”，她当时被一首歌洗脑了，根本没听我说话，一直在哼“Capybara, CapybaraCapybaraCapybara, Capybara~”，于是这个引擎就有了这个名字Capybara（水豚，一个情绪稳定的动物，寓意项目稳定）

---

- 程序的入口在`EntryPoint`函数中，首先执行的是`InitializeCor`e, 这个函数的作用是初始化日志，以便我们在后续的代码中可以使用宏来打印输出。

- 紧接着是通过`CreateApplication`方法来生成application主体，注意：这个函数仅在引擎内核中声明，具体实现在客户端中，作为一个客户端实现的application，它是必须派生自内核中`Application`类。

- `Application`类：
  
  - 成员变量Window指针，指向当前打开的window，`Window`的作用主要是用来处理用户的输入，并通过事件系统来处理输入的逻辑。在Application的run循环中会先调用所有的layerstack中的layer的update函数，然后调用window的的update
  - 成员变量layerstack，用来将所有需要显示的layer入栈，方便app层中知道需要更新哪些layer，layerstack虽然名字叫stack，但其实这个类的底层并不是用栈来实现的，因为栈没有遍历的功能，其内部只是维护了一个简单的vector
  - 在Application的Init函数中要执行Renderer的Init函数
    - Renderer::Init函数是用来对准备渲染所需要的一些东西，初始化shaderLibrary和初始化RenderCommandQueue，初始化图形API（目前是OpenGL），并且执行**`SceneRenderer::Init`**，在SceneRenderer:Init中会简单初始化一些通用的数据，还有相机、天空盒、辐照度贴图还没有绑定
  
- 程序的执行逻辑是在每一帧都调用window和layer的update，而window的update只是获取io输入用，真正的渲染以及逻辑部分其实是在layer中，目前程序只有两个layer，一个是imguiLayer，用于前端gui的显示，一个是EditorLayer，负责编辑器的渲染工作与相关逻辑。

- `EditorLayer`类：
  - EditorLayer目前还是一个较为臃肿的类，其中也穿插了很多imgui的元素，换句话来说就是耦合性稍微有点大，但是主体的流程是相对清晰的
  
  - 我希望在editorlayer绑定到我的Application上时才调用它的生命周期函数OnAttach，在OnAttach函数里，完成了以下工作：
    - 加载hdr图，这里是从等距圆柱体投影->立方体投影->radiance mipmap -> 卷积irradiance
    - 初始化两个场景，ModelScene和SphereScene
  
  - Update函数：update相机和当前activeScene
  
    - Camera::OnUpdate: （后续将考虑不在update里面检测而是全都放在onEvent里）根据用户的输入可以执行三个操作：Pan平移，Rotate旋转，Zoom缩放，其中Pan和Zoom是用来改变FocalPoint和Distance的，Rotate是改变Yaw和Pitch，因为鼠标的输入是二维的，所以其实不可能能同时操作yaw roll pitch三个角度，实际上相机一般不会用到roll，（暂时）我们认为相机是始终\*正立\*的。在这之后根据focalpoint和distance计算出相机位置，根据pitch和yaw转换成四元数，最后根据四元数和position计算出view矩阵和rotation向量
  
    - Scene::update：遍历场景中的所有entity，每个entity都有绑定一个mesh（mesh是很多面的集合），对mesh执行update函数，主要作用是播放模型的动画；然后是调用SceneRenderer::BeginScene->SceneRenderer::SubmitEntity所有entity（存下来所有entity的mesh、material、transform到drawlist中）-> SceneRenderer::EndScene调用SceneRenderer::FlushDrawList，对drawlist中的所有数据执行两个pass，Geometrypass和Compositepass
  
      - GeometryPass：对每个mesh设置着色器中的viewProjection、CameraPosition、EnvRadianceTex、EnvIrradianceTex、BRDFLUTTexture，最后将其提交到渲染命令队列
      - CompositePass：主要是后处理用到，在执行着色器之前我们已经拥有了每个点的color，现在要对这些color首先乘上曝光率，然后利用一个公式计算出亮度（绿色对亮度的贡献最大，蓝色最小），根据色调映射算法将hdr的亮度映射位ldr亮度，根据这个新算出来的亮度与原来亮度的比值乘上color获得新的color，这还没完，还要经过gamma矫正，color的1/2.2次方才是最后绘制到屏幕上的像素的颜色
  
      > 关于Scene和SceneRenderer的关系：
      >
      > - SceneRenderer通过BeginScene函数的参数获得Scene指针，它不会修改Scene当中的数据，而是将Scene当中的我所需要的数据相机、天空盒、辐照度贴图存到一个静态局部变量s_Data中，至此，s_Data中包含了SceneRenderer所需要的所有数据
      > - 所以其实可以认为SceneRenderer是Scene的一个表现层，Scene负责数据的更新，而SceneRenderer负责把这些数据渲染到屏幕上

