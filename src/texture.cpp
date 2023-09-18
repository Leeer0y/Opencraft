#include "texture.h"

Texture::Texture(GLenum TextureTarget, const std::string& FileName, int nrChannels) {
	m_textureTarget = TextureTarget;
	m_fileName = FileName;
	m_nrChannels = nrChannels;
}

bool Texture::Load() {
	stbi_set_flip_vertically_on_load(1);

	unsigned char* data = stbi_load(m_fileName.c_str(), &m_width, &m_height, &m_nrChannels, 0);
	if (!data) {
		std::cout << "TEXTURE::Failed to load image" << std::endl;
	}
	LoadInternal(data);

	stbi_image_free(data);



	return true;
}

void Texture::LoadInternal(void* image_data) {
	// bind hl object
	glGenTextures(1, &m_textureObj);
	glBindTexture(m_textureTarget, m_textureObj);

	if (m_textureTarget == GL_TEXTURE_2D) {
		switch (m_nrChannels) {
		case 1:
			// JPG
			glTexImage2D(m_textureTarget, 0, GL_RED, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, image_data);
			break;

		case 3:
			// ima be real i have no idea lol, whatever has the same colourspace as a JPG
			glTexImage2D(m_textureTarget, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
			break;

		case 4:
			// PNG
			glTexImage2D(m_textureTarget, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
			break;

		default:
			std::cout << "image bpp not implimented.";
		}
	}
	else {
		std::cout << "Support for the texture target, " << m_textureTarget << " , is not implimented" << std::endl;
		exit(1);
	}

	// set texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(m_textureTarget, 0); // unbind texture
}

void Texture::BindTexture(GLenum TextureUnit) {
	glActiveTexture(TextureUnit);
	glBindTexture(m_textureTarget, m_textureObj);
}