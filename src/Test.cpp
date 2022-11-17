#include "Test.hpp"
#include "InputModule.hpp"
#include <iostream>


/**
 * ! WARNING:
 * ! THE FOLLOWING PROCEDURES WILL BE CLEARED IN RELEASE VERSION! 
 */


//  Reserved for Input Module
void
Sirius::TestProcedure1()
{
  auto Contents = Phoenix::InputProcedure();
  for (auto& Content : Contents) {
    auto& Group = Content.first;
    std::cout << Group->GetStdinFormatFile();
    for (auto& SourceFilePath : Group->GetSourceProgramFiles()) {
      std::cout << ' ' << SourceFilePath;
    }
    std::cout << std::endl;
  }
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
  std::cout << "Test Procedure 4 Completed" << std::endl;
}
