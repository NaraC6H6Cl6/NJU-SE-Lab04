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


namespace Plum {
  class InputGroup;
}


namespace Phoenix
{

std::shared_ptr<Mercury::InputType> MakeInputByToken(std::string Token);

std::vector<std::shared_ptr<Plum::InputGroup>> GetInputGroups();

}

