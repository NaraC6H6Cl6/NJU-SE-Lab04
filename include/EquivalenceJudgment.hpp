/**
 * @file RandomInputGenerator.hpp
 * @author Lingzhou Ai (https://github.com/NaraC6H6Cl6/)
 * @brief 
 * @version 0.1
 * @date 2022-11-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _EquivalenceJudgment_H
#define _EquivalenceJudgment_H


#include "UnionFindSet.hpp"
#include <memory>
#include <filesystem>
#include <vector>
#include <string_view>


namespace Mercury
{
  class InputType;
}

namespace Plum
{
  class InputGroup;
}


namespace Hikari
{

using ExecutionResult = std::pair<int, std::vector<std::pair<int, std::string>>>;


bool Compare(const std::vector<std::pair<int, std::string>>&,
             const std::vector<std::pair<int, std::string>>&);

std::vector<std::string>
GenerateRandomInput(const std::vector<std::shared_ptr<Mercury::InputType>>&);

ExecutionResult 
Execute(
  const std::filesystem::path& Path, const std::vector<std::string>& Inputs
);

Cascade::UnionFindSet<std::filesystem::path>
EquivalenceJudgement(const Plum::InputGroup& Group);


}


#endif
