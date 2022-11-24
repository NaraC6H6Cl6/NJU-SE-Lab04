/**
 * @file ProgramExecutor.cpp
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
#include <cstdio>
#include <memory>
#include <fstream>
#include <filesystem>


Hikari::ExecutionResult
Hikari::Execute(const std::filesystem::path& Path, const std::vector<std::string>& Inputs)
{
  auto ParentPath = Path.parent_path();
  std::string CompilerCommand = std::string("g++ ") + Path.string() + " -std=c++17 -O2 -o " + ParentPath.string() + "/a.out 2> log.txt";
  std::array<char, 128> Buffer;
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


