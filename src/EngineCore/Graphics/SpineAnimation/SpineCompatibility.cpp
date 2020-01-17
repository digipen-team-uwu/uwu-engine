/******************************************************************************/
/*!
\par        Project Umbra
\file       SpineCompatibility.cpp
\author     Brayan Lopez, Yi Qian
\date       2019/10/26
\brief      Interface with Spine for texture loading/unloading

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <spine/extension.h>
#include <GL/glew.h>

//Temporary texture loader
//Source::Fetch engine
#include <string>
#include <iostream>
#include "stb_image.h"
#include <UWUEngine/Graphics/SpineAnimation/SpineCompatibility.h>
#include <UWUEngine/Debugs/TraceLogger.h>

Texture::Texture(const char* path) {
	this->path = path;
	std::string filename = std::string(path);

	glGenTextures(1, &id);

	int nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format = 0;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
    TraceLogger::Log(TraceLogger::WARNING) << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}
}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}
//End of temporary texture Loader
//TODO::integrate the new texture loader

char* _spUtil_readFile(const char* path, int* length)
{
	return _spReadFile(path, length);
}

void _spAtlasPage_createTexture(spAtlasPage* self, const char* path)
{
	auto* texture = new Texture(path);
	self->rendererObject = texture;

	self->width = texture->width;
	self->height = texture->height;
}

void _spAtlasPage_disposeTexture(spAtlasPage* self)
{
	delete static_cast<Texture*>(self->rendererObject);
}
