/**
 * @file InputModule.cpp
 * @author Lingzhou Ai (https://github.com/NaraC6H6Cl6/)
 * @brief 
 * @version 0.1
 * @date 2022-11-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "InputModule.hpp"
#include "InputType.hpp"
#include <filesystem>
#include <fstream>
#include <regex>
#include <iostream>



std::shared_ptr<Phoenix::InputGroup>
Phoenix::InputGroup::MakeInputGroup(const std::filesystem::path& DirectoryPath)
{
  std::error_code ErrorCode;

  bool bIsDirectory = std::filesystem::is_directory(DirectoryPath, ErrorCode);
  if (!bIsDirectory) {
    return nullptr;
  }

  std::filesystem::path TempStdinFormatFile;
  std::vector<std::filesystem::path> TempSourceProgramFiles;
  for (auto& ChildDirectory : std::filesystem::directory_iterator(DirectoryPath)) {
    auto& ChildPath = ChildDirectory.path();
    if (ChildPath.filename() == "stdin_format.txt") {

      TempStdinFormatFile = ChildPath;

    } else if (CompilableFileExtensions.find(std::string(ChildPath.extension()))
        != CompilableFileExtensions.end()
      ) {

      TempSourceProgramFiles.push_back(ChildPath);
    }

  }

  if (TempStdinFormatFile != "" && TempSourceProgramFiles.size() > 0) {
    Phoenix::InputGroup o;
    o.StdinFormatFile = std::move(TempStdinFormatFile);
    o.SourceProgramFiles = std::move(TempSourceProgramFiles);
    return std::make_shared<Phoenix::InputGroup>(std::move(o));
  } else {
    return nullptr;
  }

}


const std::filesystem::path&
Phoenix::InputGroup::GetStdinFormatFile() const
{
  return this->StdinFormatFile;
}


const std::vector<std::filesystem::path>&
Phoenix::InputGroup::GetSourceProgramFiles() const
{
  return this->SourceProgramFiles;
}


const std::unordered_set<std::string>
  Phoenix::InputGroup::CompilableFileExtensions = {
    ".c", ".cc", ".cpp"
  };


Phoenix::InputGroups
Phoenix::GetInputGroups()
{
  Phoenix::InputGroups Groups;

  std::filesystem::path CurrentPath = std::filesystem::current_path();

  for (auto& ChildDirectory : std::filesystem::directory_iterator(CurrentPath)) {
    auto& ChildPath = ChildDirectory.path();
    if (std::filesystem::is_directory(ChildPath)) {

      auto p = Phoenix::InputGroup::MakeInputGroup(ChildPath);
      if (p != nullptr) {
        Groups.emplace_back(p);
      }

    }
  }

  return Groups;
}


std::shared_ptr<Mercury::InputType>
Phoenix::MakeInputByToken(std::string Token)
{
  const static std::regex PatternInt("int\\(-?\\d+,-?\\d+\\)");
  const static std::regex PatternChar("char");
  const static std::regex PatternString("string\\(\\d+,\\d+\\)");
  const static std::regex SubPatternInt1("-?\\d+(?=,)");
  const static std::regex SubPatternInt2("-?\\d+(?=\\))");
  const static std::regex SubPatternString1("\\d+(?=,)");
  const static std::regex SubPatternString2("\\d+(?=\\))");

  if (std::regex_match(Token, PatternInt)) {
    std::smatch SubMatch1, SubMatch2;
    std::regex_search(Token, SubMatch1, SubPatternInt1);
    std::regex_search(Token, SubMatch2, SubPatternInt2);
    int MinLimit = std::stoi(std::string(SubMatch1[0]));
    int MaxLimit = std::stoi(std::string(SubMatch2[0]));
    return std::make_shared<Mercury::InputType>(
      Mercury::InputIntType(MinLimit, MaxLimit)
    );

  } else if (std::regex_match(Token, PatternChar)) {
    return std::make_shared<Mercury::InputType>(
      Mercury::InputCharType()
    );

  } else if (std::regex_match(Token, PatternString)) {
    std::smatch SubMatch1, SubMatch2;
    std::regex_search(Token, SubMatch1, SubPatternString1);
    std::regex_search(Token, SubMatch2, SubPatternString2);
    std::size_t MinLength = std::stoul(std::string(SubMatch1[0]));
    std::size_t MaxLength = std::stoul(std::string(SubMatch2[0]));
    return std::make_shared<Mercury::InputType>(
      Mercury::InputStringType(MinLength, MaxLength)
    );

  } else {
    return nullptr;

  }

}


Phoenix::InputContents
Phoenix::MakeInputs(Phoenix::InputGroups& Groups)
{
  Phoenix::InputContents Contents;

  for (auto Group : Groups) {
    std::shared_ptr<Mercury::InputType> TempInputType;
    std::vector<std::shared_ptr<Mercury::InputType>> InputTypes;

    const auto& StdinFormatFilePath = Group->GetStdinFormatFile();
    std::ifstream StdinFormatFileStream(StdinFormatFilePath);

    if (StdinFormatFileStream.is_open()) {
      // Successfully opened the file
      std::string Token;
      while (StdinFormatFileStream >> Token) {
        TempInputType = Phoenix::MakeInputByToken(Token);
        if (TempInputType == nullptr) {
          // Failed to analyze token
          StdinFormatFileStream.close();
          goto AnalyzationFailed;
        }
      }
    } else {
      // Failed to open the file, so go to the next folder
      continue;
    }
    // Successfully analyzed one format
    StdinFormatFileStream.close();
    Contents.emplace_back(Group, std::move(InputTypes));
    continue;
AnalyzationFailed:
    StdinFormatFileStream.close();
    continue;
  }

  return Contents;
}


Phoenix::InputContents
Phoenix::InputProcedure()
{
  auto Groups = GetInputGroups();
  auto Contents = MakeInputs(Groups);
  return Contents;
}

