/******************************************************************************/
/*!
\par        Project Umbra
\file       SingleTexture.h
\author     Yi Qian
\date       2019/12/05
\brief      Implement spine texture loader and file io,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#pragma once
#include <string>

class SingleTexture
{
public:
	// Variables
	unsigned int id{};
	int width{};
	int height{};
	std::string type;
	std::string path;

	// Constructor
	explicit SingleTexture(const char* path);
	// Destructor
	~SingleTexture();
};
