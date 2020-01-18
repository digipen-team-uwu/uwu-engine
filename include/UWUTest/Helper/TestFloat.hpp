#pragma once

#include <limits>
#include <algorithm> /* min, max */

#include "TypeWithSize.hpp"

namespace UWUTest
{

template<typename FloatType>
class IEEE_754
{
public:

  // Constants

  // An unsigned integer of the same size as the floating point number.
  // Used to easily access the raw bit data of the float.
  typedef typename TypeWithSize<sizeof(FloatType)>::UInt BitData;

  // Total number of bits in the float.
  static constexpr size_t bitCount = 8 * sizeof(FloatType);

  // Number of bits for the significand in a float.
  static constexpr size_t significandBitCount = std::numeric_limits<FloatType>::digits - 1;

  // Number of bits for the exponent in a float. The 1 is for the sign bit.
  static constexpr size_t exponentBitCount = bitCount - 1 - significandBitCount;

  // Mask for the sign bit, which is the most significant bit in IEEE-754.
  static constexpr BitData signBitMask = BitData(1) << (bitCount - 1);

  // Mask for the significand bits, which are at the least significant end in IEEE-754.
  static constexpr BitData significandBitMask = ~BitData(0) >> (exponentBitCount + 1);

  // Mask for the exponent bits, which are between sign and significand bits in IEEE-754.
  static constexpr BitData exponentBitMask = ~(signBitMask | significandBitMask);

  static constexpr size_t tolerance = 4;

  // Constructor

  // Construct from a raw floating point value.
  constexpr IEEE_754(FloatType const & f) : data_(f) {}

  constexpr IEEE_754(FloatType const && f) : data_(f) {}

  // Construct from another IEEE-754 representation class.
  constexpr IEEE_754(IEEE_754 const && rhs) : data_(rhs.data_.float_) {}

  // Conversion operator to a raw floating point value, to enable using test floats in expressions.
  constexpr operator FloatType const&() const
  {
    return data_.float_;
  }

  // Conversion operator to a raw floating point value, to enable using test floats in expressions.
  constexpr operator FloatType& ()
  {
      return data_.float_;
  }

  // Non-static methods

  // Returns the exponent bits of this float.
  constexpr BitData exponent_bits() const
  {
    return exponentBitMask & data_.bit_;
  }

  // Returns the fraction bits of this float.
  constexpr BitData significand_bits() const
  {
    return significandBitMask & data_.bit_;
  }

  // Returns the sign bit of this float.
  constexpr BitData sign_bit() const
  {
    return signBitMask & data_.bit_;
  }

  // Returns whether a float represents NaN.
  constexpr bool is_nan() const
  {
    // The IEEE-754 standard defines a NaN as a number with all ones in the exponent, and a non-zero significand.
    return (exponent_bits() == exponentBitMask) && (significand_bits() != 0);
  }

  // Tests whether two floats are equal or close enough to be considered equal.
  constexpr bool operator==(IEEE_754<FloatType> const && rhs) const
  {
    // NaN are not equal to anything, including other NaN.
    if (is_nan() || rhs.is_nan())
    {
      return false;
    }
    
    return DistanceBetweenSignAndMagnitudeNumbers(data_.bit_, rhs.data_.bit_) <= tolerance;
  }

  friend constexpr bool operator==(FloatType lhs, IEEE_754<FloatType> const&& rhs);

  // 

private:

  union Data
  {
    constexpr Data(FloatType f) : float_(f) {}
    mutable FloatType float_;
    BitData   bit_;
  };

  Data data_;


  // The following 2 methods courtesy of Google:

  // Converts an integer from the sign-and-magnitude representation to
  // the biased representation.  More precisely, let N be 2 to the
  // power of (kBitCount - 1), an integer x is represented by the
  // unsigned number x + N.
  //
  // For instance,
  //
  //   -N + 1 (the most negative number representable using
  //          sign-and-magnitude) is represented by 1;
  //   0      is represented by N; and
  //   N - 1  (the biggest number representable using
  //          sign-and-magnitude) is represented by 2N - 1.
  //
  // Read http://en.wikipedia.org/wiki/Signed_number_representations
  // for more details on signed number representations.
  static constexpr BitData SignAndMagnitudeToBiased(BitData const& sam)
  {
    if (signBitMask & sam)
    {
      // sam represents a negative number.
      return ~sam + 1;
    }
    else
    {
      // sam represents a positive number.
      return signBitMask | sam;
    }
  }

  // Given two numbers in the sign-and-magnitude representation,
  // returns the distance between them as an unsigned number.
  static constexpr BitData DistanceBetweenSignAndMagnitudeNumbers(const BitData &sam1, const BitData &sam2)
  {
    constexpr BitData biased1 = SignAndMagnitudeToBiased(sam1);
    constexpr BitData biased2 = SignAndMagnitudeToBiased(sam2);
    return std::max(biased1, biased2) - std::min(biased1, biased2);
  }

};

template <typename FloatType>
constexpr bool operator==(FloatType lhs, IEEE_754<FloatType> const&& rhs)
{
  return IEEE_754<FloatType>(lhs) == rhs;
}

typedef IEEE_754<float>  t_float;
typedef IEEE_754<double> t_double;

}