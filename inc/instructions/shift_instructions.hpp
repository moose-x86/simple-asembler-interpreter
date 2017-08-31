#pragma once

#include "instruction.hpp"
#include <algorithm>

namespace back_end
{
namespace instructions
{

struct rrca : public instruction_of_type<rrca>
{
  void execute_using(back_end::register_type_a& a) const
  {
    std::rotate(a.rbegin(), a.rbegin() + 1, a.rend());
  }
};

struct lrca : public instruction_of_type<lrca>
{
  void execute_using(back_end::register_type_a& a) const
  {
    std::rotate(a.begin(), a.begin() + 1, a.end());
  }
};

}
}
