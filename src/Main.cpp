#include "InputGroup.hpp"
#include "InputProcedure.hpp"
#include "EquivalenceJudgment.hpp"
#include "OutputProcedure.hpp"
#include <iostream>

int
main()
{
  const auto& Groups = Phoenix::GetInputGroups();
  for (auto& Group : Groups) {
    const auto& Set = Hikari::EquivalenceJudgement(*Group);
    Violet::OutputResult(*Group, Set);
  }
  return 0;
}