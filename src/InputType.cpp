/**
 * @file ProgramInputType.cpp
 * @author Lingzhou Ai (https://github.com/NaraC6H6Cl6/)
 * @brief 
 * @version 0.1
 * @date 2022-11-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "InputType.hpp"
#include <chrono>
#include <algorithm>


Mercury::InputIntType::InputIntType() noexcept
  : MinLimit(INT32_MIN)
  , MaxLimit(INT32_MAX)
{}


Mercury::InputIntType::InputIntType(int MinLimit, int MaxLimit) noexcept
{
  if (MinLimit <= MaxLimit) {
    this->MinLimit = MinLimit;
    this->MaxLimit = MaxLimit;
  } else {
    this->MinLimit = INT32_MIN;
    this->MaxLimit = INT32_MAX;
  }
}


std::uniform_int_distribution<size_t>
Mercury::InputIntType::SpecialDistribution =
  std::uniform_int_distribution<size_t>(0, 63);


std::string
Mercury::InputIntType::GenerateRandomInput() const
{
  static std::default_random_engine RandomEngine(
    std::chrono::system_clock::to_time_t(
      std::chrono::system_clock::now()
    ) ^ 0x5555'5555'5555'5555
  );
  int SpecialIndex = SpecialDistribution(RandomEngine);
  if (SpecialIndex < 14
    && SpecialValues[SpecialIndex] >= MinLimit
    && SpecialValues[SpecialIndex] <= MaxLimit
  ) {
    return std::to_string(SpecialValues[SpecialIndex]);
  } else {
    std::uniform_int_distribution<> NumberDistribution(MinLimit, MaxLimit);
    int RandomNumber = NumberDistribution(RandomEngine);
    return std::to_string(RandomNumber);
  }
}


std::uniform_int_distribution<char>
Mercury::InputCharType::AsciiDistribution =
  std::uniform_int_distribution<char>(char(0x20), char(0x7f));


std::string
Mercury::InputCharType::GenerateRandomInput() const
{
  static std::default_random_engine RandomEngine(
    std::chrono::system_clock::to_time_t(
      std::chrono::system_clock::now()
    ) ^ 0xaaaa'aaaa'aaaa'aaaa
  );
  char RandomAsciiChar = AsciiDistribution(RandomEngine);
  return std::string(1, RandomAsciiChar);
}


Mercury::InputStringType::InputStringType(
  std::size_t MinLength, std::size_t MaxLength) noexcept
{
  if (MinLength <= MaxLength) {
    this->MinLength = std::clamp<size_t>(MinLength, 1, 4095);
    this->MaxLength = std::clamp<size_t>(MaxLength, 1, 4095);
  } else {
    this->MinLength = 1;
    this->MaxLength = 4095;
  }
}


std::string
Mercury::InputStringType::GenerateRandomInput() const
{
  static std::default_random_engine RandomEngine(
    std::chrono::system_clock::to_time_t(
      std::chrono::system_clock::now()
    ) ^ 0x6969'6969'6969'6969
  );
  std::uniform_int_distribution<size_t> LengthDistribution(
    MinLength, MaxLength
  );
  size_t RandomLength = LengthDistribution(RandomEngine);
  std::string s;
  s.resize(RandomLength);
  for (size_t i = 0; i < RandomLength; i++) {
    char RandomAsciiChar = AsciiDistribution(RandomEngine);
    s[i] = RandomAsciiChar;
  }
  return s;
}
