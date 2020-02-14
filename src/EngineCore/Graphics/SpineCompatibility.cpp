/******************************************************************************/
/*!
\par        Project Umbra
\file       SpineCompatibility.cpp
\author     Brayan Lopez, Yi Qian
\date       2019/10/26
\brief      Interface with Spine for texture loading/unloading

Copyright (c) 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Graphics/SingleTexture.h>
#include <spine/extension.h>
#include <GL/glew.h>

//Temporary texture loader
//Source::Fetch engine
#include <string>
#include <iostream>
#include <UWUEngine/Graphics/SingleTexture.h>

//End of temporary texture Loader
//TODO::integrate the new texture loader

char* _spUtil_readFile(const char* path, int* length)
{
	return _spReadFile(path, length);
}

void _spAtlasPage_createTexture(spAtlasPage* self, const char* path)
{
	auto* texture = new SingleTexture(path);
	self->rendererObject = texture;

	self->width = texture->width;
	self->height = texture->height;
}

void _spAtlasPage_disposeTexture(spAtlasPage* self)
{
	delete static_cast<SingleTexture*>(self->rendererObject);
}
