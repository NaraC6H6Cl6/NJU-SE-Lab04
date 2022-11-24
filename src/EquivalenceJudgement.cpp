/**
 * @file EquivalenceJudgement.cpp
 * @author Lingzhou Ai (https://github.com/NaraC6H6Cl6/)
 * @brief 
 * @version 0.1
 * @date 2022-11-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "EquivalenceJudgmentModule.hpp"
#include "InputModule.hpp"
#include <iostream>


bool
Hikari::Compare(const std::vector<std::pair<int, std::string>>& lhs,
                const std::vector<std::pair<int, std::string>>& rhs)
{
  if (lhs.size() != rhs.size()) {
    return false;
  }
  auto it1 = lhs.begin(), it2 = rhs.begin();
  while (it1 != lhs.end()) {
    if (it1->first != 0 || it2->first != 0 || it1->second != it2->second) {
      return false;
    }
  }
  return true;
}


std::vector<std::pair<std::string_view, std::string_view>>
Hikari::EquivalenceJudgement(const Phoenix::InputContent& Content)
{
  auto& ProgramFilePaths = Content.first->GetSourceProgramFiles();
  auto InputStrings = Hikari::GenerateRandomInput(Content.second);
  std::vector<std::pair<std::filesystem::path, Hikari::ExecutionResult>> OutputResults;  
  std::vector<std::string_view> PathStrings;
  for (auto& Path : ProgramFilePaths) {
    std::cout << Path.string() << std::endl;
    OutputResults.emplace_back(Path, Hikari::Execute(Path, InputStrings));
    PathStrings.emplace_back(Path.string());
  }
  std::vector<std::pair<std::string_view, std::string_view>> Ret;
  int n = OutputResults.size();
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      auto& Result1 = OutputResults[i].second;
      auto& Result2 = OutputResults[j].second;
      if (Result1.first != 0 || Result2.first != 0) {
        // Failed to compile
        continue;
      }
      bool bIsSameResults = Hikari::Compare(Result1.second, Result2.second);
      if (bIsSameResults) {
        Ret.emplace_back(PathStrings[i], PathStrings[j]);
      }
    }
  }
  return Ret;
}

