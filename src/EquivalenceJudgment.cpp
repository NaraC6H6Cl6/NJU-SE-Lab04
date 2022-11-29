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

#include "EquivalenceJudgment.hpp"
#include "InputGroup.hpp"
#include <cstdio>
#include <iostream>
#include <memory>
#include <fstream>
#include <filesystem>


bool
Hikari::Compare(const std::vector<std::pair<int, std::string>>& lhs,
                const std::vector<std::pair<int, std::string>>& rhs)
{
  if (lhs.size() != rhs.size() || lhs.size() == 0) {
    return false;
  }
  auto it1 = lhs.begin(), it2 = rhs.begin();
  while (it1 != lhs.end()) {
    if (it1->first != 0 || it2->first != 0 || it1->second != it2->second) {
      return false;
    }
    it1++;
    it2++;
  }
  return true;
}


Hikari::ExecutionResult
Hikari::Execute(const std::filesystem::path& Path, const std::vector<std::string>& Inputs)
{
  auto ParentPath = Path.parent_path();
  std::string CompilerCommand = std::string("g++ ") + Path.string() + " -std=c++17 -O2 -o " + ParentPath.string() + "/a.out 2> log.txt";
  std::string Result;
  auto Pipe1 = popen(CompilerCommand.c_str(), "r");
  if (!Pipe1) {
    // Failed to open the compiler
    return std::make_pair<int, std::vector<std::pair<int, std::string>>>(
      2147483647, {}
    );
  }
  auto CompilerRet = pclose(Pipe1);
  if (CompilerRet != EXIT_SUCCESS) {
    // Compile failed
    return std::make_pair<int, std::vector<std::pair<int, std::string>>>(
      -1, {}
    );
  }
  std::vector<std::pair<int, std::string>> Ret;
  std::string ExecutionCommand = ParentPath.string() + "/a.out < input.txt > output.txt 2> log.txt";
  for (auto& Input : Inputs) {
    std::ofstream InputFile("input.txt");
    InputFile << Input;
    InputFile.close();
    auto Pipe2 = popen(ExecutionCommand.c_str(), "r");
    if (!Pipe2) {
      // Failed to execute the program
      return std::make_pair<int, std::vector<std::pair<int, std::string>>>(
        1, {}
      );
    }
    auto ProgramRet = pclose(Pipe2);
    if (ProgramRet != EXIT_SUCCESS) {
      Ret.emplace_back(-1, "");
    }
    std::ifstream OutputFile("output.txt");
    if (!OutputFile.is_open()) {
      return std::make_pair<int, std::vector<std::pair<int, std::string>>>(
        2, {}
      );
    }
    OutputFile.seekg(0, std::ios::end);
    size_t FileSize = OutputFile.tellg();
    OutputFile.seekg(0, std::ios::beg);
    std::string OutputStr;
    OutputStr.resize(FileSize);
    OutputFile.read(OutputStr.data(), FileSize);
    OutputFile.close();
    Ret.emplace_back(0, std::move(OutputStr));
  }
  return std::make_pair(0, std::move(Ret));
}


Cascade::UnionFindSet<std::filesystem::path>
Hikari::EquivalenceJudgement(const Plum::InputGroup& Group)
{
  const auto& SourceFilePaths = Group.GetSourceFilePaths();
  auto InputStrings = Hikari::GenerateRandomInput(Group.GetInputParameters());
  std::vector<std::pair<std::filesystem::path, Hikari::ExecutionResult>> OutputResults;  
  std::vector<std::string_view> FilePathStrings;
  for (auto& Path : SourceFilePaths) {
    std::cout << Path.string() << std::endl;
    OutputResults.emplace_back(Path, Hikari::Execute(Path, InputStrings));
    FilePathStrings.emplace_back(Path.string());
  }
  Cascade::UnionFindSet<std::filesystem::path> Ret;
  int n = OutputResults.size();
  for (int i = 0; i < n - 1; i++) {
    Ret.Insert(&SourceFilePaths[i]);
    for (int j = i + 1; j < n; j++) {
      Ret.Insert(&SourceFilePaths[j]);
      auto& Result1 = OutputResults[i].second;
      auto& Result2 = OutputResults[j].second;
      if (Result1.first != 0 || Result2.first != 0) {
        // Failed to compile
        continue;
      }
      bool bIsSameResults = Hikari::Compare(Result1.second, Result2.second);
      if (bIsSameResults) {
        Ret.Merge(&SourceFilePaths[i], &SourceFilePaths[j]);
        break;
      }
    }
  }
  return Ret;
}





