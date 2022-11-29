/**
 * @file OutputProcedure.cpp
 * @author Lingzhou Ai (https://github.com/NaraC6H6Cl6/)
 * @brief 
 * @version 0.1
 * @date 2022-11-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "OutputProcedure.hpp"
#include "InputGroup.hpp"
#include <fstream>


void
Violet::OutputResult(const Plum::InputGroup& Group,
                     const Cascade::UnionFindSet<std::filesystem::path>& Set)
{
  const auto& FolderPath = Group.GetFolderPath();
  const auto& SourceProgramPaths = Group.GetSourceFilePaths();
  int n = SourceProgramPaths.size();
  std::vector<std::pair<const std::filesystem::path*,
                        const std::filesystem::path*>> EqualPairs;
  std::vector<std::pair<const std::filesystem::path*,
                        const std::filesystem::path*>> InequalPairs;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      const std::filesystem::path* p1 = &SourceProgramPaths[i];
      const std::filesystem::path* p2 = &SourceProgramPaths[j];
      bool bIsEqual = Set.IsSameUnion(p1, p2);
      if (bIsEqual) {
        EqualPairs.emplace_back(p1, p2);
      } else {
        InequalPairs.emplace_back(p1, p2);
      }
    }
  }
  std::ofstream EqualsResultFileStream(FolderPath.string() + "/equal.csv");
  EqualsResultFileStream << "file1,file2\n";
  for (auto& Pair : EqualPairs) {
    EqualsResultFileStream << Pair.first->string() << ','
                           << Pair.second->string() << '\n';
  }
  EqualsResultFileStream.close();
  std::ofstream InequalsResultFileStream(FolderPath.string() + "/inequal.csv");
  InequalsResultFileStream << "file1,file2\n";
  for (auto& Pair : InequalPairs) {
    InequalsResultFileStream << Pair.first->string() << ','
                             << Pair.second->string() << '\n';
  }
  InequalsResultFileStream.close();
}
