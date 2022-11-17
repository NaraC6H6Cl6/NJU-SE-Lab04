/**
 * @file RandomInputGenerator.cpp
 * @author your name (you@domain.com)
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
  for (int i = 0; i < 100; i++) {
    std::string& s = o.emplace_back(std::string());
    for (auto Input : Inputs) {
      s += Input->GenerateRandomInput();
      s += ' ';
    }
  }
  return o;
}

