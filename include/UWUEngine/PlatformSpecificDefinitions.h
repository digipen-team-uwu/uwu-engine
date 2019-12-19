#pragma once

#ifdef _MSVC
#define FUNCTION_SIGNATURE __FUNCSIG__
#else
#define FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#endif