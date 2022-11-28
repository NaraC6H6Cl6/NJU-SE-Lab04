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

#ifndef _UnionFindSet_H
#define _UnionFindSet_H


#include <memory>
#include <vector>
#include <unordered_map>


namespace Cascade {


template <typename T,
          typename HashT = std::hash<T>,
          typename EqualT = std::equal_to<T>>
class UnionFindSet
{
public:
  UnionFindSet() {}

  UnionFindSet(std::initializer_list<T*> l) {
    for (auto p : l) {
      ParentRef.try_emplace(p, std::make_pair<const T*, int>(p, 0));
    }
  }

  template <typename InputIt>
  UnionFindSet(InputIt begin, InputIt end) {
    static_assert(std::is_same_v<T*,
        typename std::iterator_traits<InputIt>::value_type
      > && std::is_base_of_v<std::input_iterator_tag,
        typename std::iterator_traits<InputIt>::iterator_category
      >
    );
    InputIt it = begin;
    while (it < end) {
      ParentRef.try_emplace(*it, *it);
      it++;
    }
  }

  void
  Insert(const T* p)
  {
    ParentRef.try_emplace(p, p);
  }

  void
  Merge(const T* lhs, const T* rhs)
  {
    if (ParentRef.find(lhs) != ParentRef.end()
      && ParentRef.find(rhs) != ParentRef.end()
    ) {
      const T* p1 = FindRoot(lhs);
      const T* p2 = FindRoot(rhs);
      if (p1 != p2) {
        const T*& pp2 = GetParent(p2);
        int& r1 = GetRank(p1);
        int& r2 = GetRank(p2);
        if (r1 <= r2) {
          GetParent(p1)= p2;
          if (r1 == r2) {
            r2 += 1;
          }
        } else {
          GetParent(p2) = p1;
          if (r1 == r2) {
            r1 += 1;
          }
        }
      }
    }
  }

  void
  Clear()
  {
    ParentRef.clear();
  }

  bool
  In(const T* o) const
  {
    return ParentRef.find(o) != ParentRef.end();
  }

  bool
  IsSameUnion(const T* lhs, const T* rhs) const
  {
    return ParentRef.find(lhs) != ParentRef.end()
      && ParentRef.find(rhs) != ParentRef.end()
      && FindRoot(lhs) == FindRoot(rhs);
  }

private:
  std::unordered_map<T*, std::pair<const T*, int>, HashT, EqualT> ParentRef;

  const T*&
  GetParent(const T* p) const
  {
    return ParentRef.at(p).first;
  }

  int&
  GetRank(const T* p) const
  {
    return ParentRef.at(p).second;
  }

  const T*
  FindRoot(const T* p) const
  { 
    const T* pp = GetParent(p);
    while (pp != p) {
      p = pp;
      pp = GetParent(p);
    }
    return p;
  }

};


}


#endif
