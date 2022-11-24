#include "Test.hpp"
#include "InputModule.hpp"
#include "EquivalenceJudgmentModule.hpp"
#include <iostream>


/**
 * ! WARNING:
 * ! THE FOLLOWING PROCEDURES WILL BE CLEARED IN RELEASE VERSION! 
 */


//  Reserved for Input Module
void
Sirius::TestProcedure1()
{
  std::cout << "Test Procedure 1 Completed" << std::endl;
}

//  Reserved for Equivalence Judger Module
void
Sirius::TestProcedure2()
{
  auto Contents = Phoenix::InputProcedure();
  for (auto& Content : Contents) {
    auto Result = Hikari::EquivalenceJudgement(Content);
    for (auto& [Path1, Path2] : Result) {
      std::cout << Path1 << ' ' << Path2 << std::endl;
    }
  }
  std::cout << "Test Procedure 2 Completed" << std::endl;
}

//  Reserved for Equivalence Confirmation Module
void
Sirius::TestProcedure3()
{
  std::cout << "Test Procedure 3 Completed" << std::endl;
}

// Reserved for Output Module
void
Sirius::TestProcedure4()
{
  std::cout << "Test Procedure 4 Completed" << std::endl;
}
