/**
 * @file InputModule.hpp
 * @author Lingzhou Ai (https://github.com/NaraC6H6Cl6/)
 * @brief 
 * @version 0.1
 * @date 2022-11-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <memory>
#include <filesystem>
#include <vector>
#include <unordered_set>
#include <regex>


namespace Mercury {
  class InputType;
}


namespace Phoenix {


class InputGroup
{
public:
  static std::shared_ptr<InputGroup> MakeInputGroup(const std::filesystem::path&);
  InputGroup(const InputGroup&) = delete;
  InputGroup& operator=(const InputGroup&) = delete;
  InputGroup(InputGroup&&) = default;

  const std::filesystem::path& GetStdinFormatFile() const;
  const std::vector<std::filesystem::path>& GetSourceProgramFiles() const;

private:
  InputGroup() = default;
  const static std::unordered_set<std::string>
    CompilableFileExtensions;

private:
  std::filesystem::path StdinFormatFile;
  std::vector<std::filesystem::path> SourceProgramFiles;
};


using InputGroups = std::vector<std::shared_ptr<InputGroup>>;


using InputContents = std::vector<
  std::pair<
    std::shared_ptr<Phoenix::InputGroup>,
    std::vector<std::shared_ptr<Mercury::InputType>>
  >
>;


Phoenix::InputGroups GetInputGroups();

std::shared_ptr<Mercury::InputType> MakeInputByToken(std::string Token);

Phoenix::InputContents MakeInputs(Phoenix::InputGroups& Groups);

Phoenix::InputContents InputProcedure();


}

