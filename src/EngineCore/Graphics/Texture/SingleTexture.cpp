#include <UWUEngine/Graphics/SingleTexture.h>
#include <GL/glew.h>
#include <iostream>
#include <stb_image.h>

SingleTexture::SingleTexture(const char* path)
{
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
		//TraceLogger::Log(TraceLogger::WARNING) << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}
}

SingleTexture::~SingleTexture()
{
	glDeleteTextures(1, &id);
}