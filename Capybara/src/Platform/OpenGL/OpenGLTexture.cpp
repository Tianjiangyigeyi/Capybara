﻿#include "precomp.h"
#include "OpenGLTexture.h"

#include "stb_image.h"
#include "glad/glad.h"

namespace Capybara
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
        : m_Path(path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        CPBR_CORE_ASSERT(data, "Failed to load image!");
        m_Width = width;
        m_Height = height;

         glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
		
        glTexParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);

    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTexture(slot, m_RendererID);
    }
}
