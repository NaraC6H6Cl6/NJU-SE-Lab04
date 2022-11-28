/**
 * @file InputGroup.hpp
 * @author Lingzhou Ai (https://github.com/NaraC6H6Cl6/)
 * @brief 
 * @version 0.1
 * @date 2022-11-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "InputGroups.hpp"
#include "InputProcedures.hpp"
#include <memory>
#include <fstream>



std::shared_ptr<Plum::InputGroup>
Plum::InputGroup::MakeInputGroup(const std::filesystem::path& FolderPath)
{
  std::error_code ErrorCode;
  // The directory must be a folder.
  bool bIsDirectory = std::filesystem::is_directory(FolderPath, ErrorCode);
  if (!bIsDirectory) {
    return nullptr;
  }
  std::filesystem::path TempFormatFilePath;
  std::vector<std::filesystem::path> TempSourceFilePaths;
  // Traverse the child directories of the target file.
  for (auto& ChildDirectory : std::filesystem::directory_iterator(FolderPath)) {
    auto& ChildPath = ChildDirectory.path();
    if (ChildPath.filename() == "stdin_format.txt") {
      TempFormatFilePath = ChildPath;
    } else if (CompilableFileExtensions.find(std::string(ChildPath.extension()))
      != CompilableFileExtensions.end()
    ) {
      TempSourceFilePaths.push_back(ChildPath);
    }
  }
  // We know that a valid input folder should include a `stdin_format.txt` file
  // and a couple of compilable files.
  if (TempFormatFilePath != "" && TempSourceFilePaths.size() > 0) {
    std::ifstream FormatFileStream(TempFormatFilePath.string());
    if (!FormatFileStream.is_open()) {
      return nullptr;
    }
    std::string Token;
    std::vector<std::shared_ptr<Mercury::InputType>> TempInputParameters;
    while (FormatFileStream >> Token) {
      TempInputParameters.emplace_back(Phoenix::MakeInputByToken(Token));
    }
    FormatFileStream.close();
    Plum::InputGroup Ret;
    Ret.InputParameters = std::move(TempInputParameters);
    Ret.SourceFilePaths = std::move(TempSourceFilePaths);
    return std::make_shared<Plum::InputGroup>(std::move(Ret));
  } else {
    return nullptr;
  }
}


const std::vector<std::shared_ptr<Mercury::InputType>>&
Plum::InputGroup::GetInputParameters() const
{
  return this->InputParameters;
}


const std::vector<std::filesystem::path>&
Plum::InputGroup::GetSourceFilePaths() const
{
  return this->SourceFilePaths;
}


const std::unordered_set<std::string>
Plum::InputGroup::CompilableFileExtensions = {
  ".c", ".cc", ".cpp"
};