#include "ProgramInputType.hpp"
#include <chrono>
#include <algorithm>


Mercury::InputIntType::InputIntType()
  : NumberDistribution(INT32_MIN, INT32_MAX)
{}


Mercury::InputIntType::InputIntType(int MinLimit, int MaxLimit)
{
  if (MinLimit <= MaxLimit) {
    this->NumberDistribution =
      std::uniform_int_distribution<>(MinLimit, MaxLimit);
  } else {
    this->NumberDistribution =
      std::uniform_int_distribution<>(INT32_MIN, INT32_MAX);
  }
}


std::string
Mercury::InputIntType::GenerateRandomInput()
{
  static std::default_random_engine RandomEngine(
    std::chrono::system_clock::to_time_t(
      std::chrono::system_clock::now()
    ) ^ 0x5555'5555'5555'5555
  );
  int RandomNumber = NumberDistribution(RandomEngine);
  return std::to_string(RandomNumber);
}


std::uniform_int_distribution<char>
  Mercury::InputCharType::AsciiDistribution =
    std::uniform_int_distribution<char>(char(0x20), char(0x7f));


std::string
Mercury::InputCharType::GenerateRandomInput()
{
  static std::default_random_engine RandomEngine(
    std::chrono::system_clock::to_time_t(
      std::chrono::system_clock::now()
    ) ^ 0xaaaa'aaaa'aaaa'aaaa
  );
  char RandomAsciiChar = AsciiDistribution(RandomEngine);
  return std::string(&RandomAsciiChar, 1);
}


Mercury::InputStringType::InputStringType(std::size_t MinLength,
                                          std::size_t MaxLength)
{
  if (MinLength <= MaxLength) {
    this->LengthDistribution =
      std::uniform_int_distribution<size_t>(
         std::clamp<size_t>(MinLength, 1, 255),
         std::clamp<size_t>(MaxLength, 1, 255)
      );
  } else {
    this->LengthDistribution =
      std::uniform_int_distribution<size_t>(1, 255);
  }
}


std::string
Mercury::InputStringType::GenerateRandomInput()
{
  static std::default_random_engine RandomEngine(
    std::chrono::system_clock::to_time_t(
      std::chrono::system_clock::now()
    ) ^ 0x6969'6969'6969'6969
  );
}
