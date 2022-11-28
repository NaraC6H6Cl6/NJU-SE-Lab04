/**
 * @file RandomInputGenerator.cpp
 * @author Lingzhou Ai (https://github.com/NaraC6H6Cl6/)
 * @brief 
 * @version 0.1
 * @date 2022-11-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "EquivalenceJudgmentModule.hpp"
#include "InputType.hpp"
#include <random>
#include <chrono>


std::vector<std::string>
Hikari::GenerateRandomInput(
  const std::vector<std::shared_ptr<Mercury::InputType>>& Inputs
)
{
  std::vector<std::string> Ret;
  Ret.reserve(32);
  for (int i = 0; i < 32; i++) {
    std::string& s = Ret.emplace_back(std::string());
    for (auto Input : Inputs) {
      s += Input->GenerateRandomInput();
      s += ' ';
    }
  }
  return Ret;
}

