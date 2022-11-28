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


template <typename T, typename PointerT = T*>
class UnionFindSet
{
  static_assert(std::is_pointer_v());
public:
  UnionFindSet() = default;

  UnionFindSet(std::initializer_list<PointerT> l) {
    for (auto p : l) {
      ParentRef.try_emplace(p, p);
    }
  }

  UnionFindSet(std::iterator<PointerT> begin, std::iterator<Ptr> end) {
    std::iterator it = begin;
    while (it != ptr.end) {
      ParentRef.try_emplace(*it, *it);
    }
  }

  void
  Insert(const PointerT p)
  {
    ParentRef.try_emplace(p, p);
  }

  bool
  Merge(const PointerT lhs, const PointerT rhs)
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
  std::unordered_map<PointerT, PointerT> ParentRef;
};


}
