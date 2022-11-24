/**
 * @file UnionFindSet.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <vector>
#include <unordered_map>


namespace Cascade {


template <typename T>
class UnionFindSet
{
public:
  UnionFindSet() = default;

  UnionFindSet(std::initializer_list<T*> l) {

  }

  UnionFindSet(std::iterator<T*> begin, std::iterator<T*> end) {

  }

  void
  Insert(const T*)
  {
    
  }

  bool
  Merge(const T* lhs, const T* rhs)
  {
    if (Match.find(lhs) == Match.end() || Match.find(rhs) == Match.end()) {
      return false;
    }
    size_t Index1 = Match[lhs];
    size_t Index2 = Match[rhs];
    ...
    return true;
  }





private:
  std::unordered_map<T*, size_t> Match;
  std::vector<std::pair<T*, size_t>> Data;
};


}
