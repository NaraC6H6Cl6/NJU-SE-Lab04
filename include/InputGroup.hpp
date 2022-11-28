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

#ifndef _InputGroup_H
#define _InputGroup_H


#include <memory>
#include <filesystem>
#include <vector>
#include <unordered_set>


namespace Mercury {
  class InputType;
}


namespace Plum
{


class InputGroup
{
public:
  static std::shared_ptr<InputGroup>
    MakeInputGroup(const std::filesystem::path& FolderPath);
  
  InputGroup(const InputGroup&) = delete;
  InputGroup& operator=(const InputGroup&) = delete;
  InputGroup(InputGroup&&) = default;

  const std::vector<std::shared_ptr<Mercury::InputType>>&
    GetInputParameters() const;
  const std::vector<std::filesystem::path>& GetSourceFilePaths() const;

private:
  InputGroup() = default;
  const static std::unordered_set<std::string>
    CompilableFileExtensions;

private:
  std::vector<std::shared_ptr<Mercury::InputType>> InputParameters;
  std::vector<std::filesystem::path> SourceFilePaths;
};


}


#endif
