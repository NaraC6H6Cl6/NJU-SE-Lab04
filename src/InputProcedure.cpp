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

#include "InputProcedure.hpp"
#include "InputGroup.hpp"
#include "InputType.hpp"
#include <filesystem>
#include <regex>
#include <iostream>



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



std::vector<std::shared_ptr<Plum::InputGroup>>
Phoenix::GetInputGroups()
{
  std::vector<std::shared_ptr<Plum::InputGroup>> Groups;
  // Get the path of the application.
  std::filesystem::path CurrentPath = std::filesystem::current_path();
  // Every child folder may be an input group.
  for (auto& ChildDirectory : std::filesystem::directory_iterator(CurrentPath)) {
    auto& ChildPath = ChildDirectory.path();
    if (std::filesystem::is_directory(ChildPath)) {
      auto p = Plum::InputGroup::MakeInputGroup(ChildPath);
      // If the folder is a valid input group, the function will not return nullptr
      if (p != nullptr) {
        Groups.emplace_back(p);
      }
    }
  }
  return Groups;
}


