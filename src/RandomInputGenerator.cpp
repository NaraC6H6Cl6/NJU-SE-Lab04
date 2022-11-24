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
#include "ProgramInputType.hpp"
#include <random>
#include <chrono>


std::vector<std::string>
Hikari::GenerateRandomInput(
  const std::vector<std::shared_ptr<Mercury::InputType>>& Inputs)
{
  std::vector<std::string> o;
  o.reserve(48);
  for (int i = 0; i < 48; i++) {
    std::string& s = o.emplace_back(std::string());
    for (auto Input : Inputs) {
      s += Input->GenerateRandomInput();
      s += ' ';
    }
  }
  return o;
}

