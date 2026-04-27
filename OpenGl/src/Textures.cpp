#include"Textures.h"
#include"vendor/stb_image/stb_image.h"
Texture::Texture(const std::string& path)
	:m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);//数据加载到内存，4代表强制要求4通道（RGBA）

	GLCall(glGenTextures(1, &m_RendererID));//生成纹理对象，返回纹理ID
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));//绑定纹理对象，操作都在这个对象上进行

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));//四个纹理参数，必须要设置

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));//把纹理数据传给 GPU(显存)，生成纹理
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));//解绑纹理对象

	if(m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);//释放内存
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));//激活纹理单元，默认是0
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));//解绑纹理对象
}
