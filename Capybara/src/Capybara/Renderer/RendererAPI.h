#pragma once


namespace Capybara
{
    using RendererID = uint32_t;
    enum class RendererAPIType
    {
        None = 0,
        OpenGL = 1
    };
    
    struct RenderAPICapabilities
    {
        std::string Vendor;
        std::string Renderer;
        std::string Version;

        int MaxSamples;
        float MaxAnisotropy;
    };
    
    class RendererAPI
    {
    public:
        static void Init();
        static void Shutdown();
        static void SetClearColor(float r, float g, float b, float a);
        static void Clear(float r, float g, float b, float a);
        static void DrawIndexed(unsigned int count, bool depthTest = true);
        inline static RenderAPICapabilities& GetCapabilities()
        {
            static RenderAPICapabilities caps;
            return caps;
        }
        inline static RendererAPIType Current() { return  s_CurrentRendererAPI; }
    private:
        static void LoadRequiredAssets();
        static RendererAPIType s_CurrentRendererAPI;
    };

}
