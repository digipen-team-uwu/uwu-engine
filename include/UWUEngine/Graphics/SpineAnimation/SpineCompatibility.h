/******************************************************************************/
/*!
\par        Project Umbra
\file       SpineCompatibility.h
\author     Yi Qian
\date       2019/12/05
\brief      Implement spine texture loader and file io,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#pragma once
#include <string>

class Texture {
public:
	// Variables
	unsigned int id{};
	int width{};
	int height{};
	std::string type;
	std::string path;

	// Constructor
	explicit Texture(const char* path);
	// Destructor
	~Texture();
};
