#pragma once

namespace UWUTest
{

template <unsigned SIZE> struct TypeWithSize 
{ 
    // Empty by default.  Rely on specializations for details.
    // Unsupported values of SIZE will give compile-time errors on purpose.
};
 
template <> struct TypeWithSize<1> 
{
    typedef   signed char Int;   // 1 byte signed integer type
    typedef unsigned char UInt;  // 1 byte unsigned integer type
};
 
template <> struct TypeWithSize<2> 
{
    typedef   signed short Int;   // 2 byte signed integer type
    typedef unsigned short UInt;  // 2 byte unsigned integer type
};
 
template <> struct TypeWithSize<4> 
{
    typedef   signed int Int;   // 4 byte signed integer type
    typedef unsigned int UInt;  // 4 byte unsigned integer type
    typedef float Float;        // 4 byte floating point type
};
 
template <> struct TypeWithSize<8> 
{
    typedef   signed long long Int;   // 8 byte signed integer type
    typedef unsigned long long UInt;  // 8 byte unsigned integer type
    typedef double Float;             // 8 byte floating point type
};

}