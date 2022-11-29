#include "Test.hpp"
#include "InputGroup.hpp"
#include "InputProcedure.hpp"
#include "EquivalenceJudgment.hpp"
#include "OutputProcedure.hpp"
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
  const auto& Groups = Phoenix::GetInputGroups();
  for (auto& Group : Groups) {
    const auto& Set = Hikari::EquivalenceJudgement(*Group);
    Violet::OutputResult(*Group, Set);
  }
  std::cout << "Test Procedure 4 Completed" << std::endl;
}
