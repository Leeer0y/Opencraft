#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <iostream>
#include <string>

#include "stb_image.h"

// based off https://www.youtube.com/watch?v=n8t7nvHCqek by OGLDEV
// https://github.com/emeiri/ogldev/blob/master/Common/ogldev_texture.cpp

class Texture {
public:
	Texture(GLenum TextureTarget, const std::string& FileName, int nrChannels = 0); // constructor

	bool Load(); // loads an image using stbi
	void BindTexture(GLenum TextureUnit); // binds the gl object


private:
	void LoadInternal(void* image_data); // internally creats gl texture object and links image data to it.

	std::string m_fileName;
	GLenum m_textureTarget;
	GLuint m_textureObj;

	int m_width = 0;
	int m_height = 0;
	int m_nrChannels = 0;
};

#endif // !TEXTURE_H

