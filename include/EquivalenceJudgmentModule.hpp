/**
 * @file RandomInputGenerator.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <memory>
#include <vector>


namespace Mercury
{
  class InputType;
}

namespace Phoenix
{
  class InputContent;
}


namespace Hikari
{


std::vector<std::string> GenerateRandomInput(
  const std::vector<std::shared_ptr<Mercury::InputType>>&);

std::string Execute(const Phoenix::InputContent&);


}
