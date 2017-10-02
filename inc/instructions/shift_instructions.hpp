#pragma once

#include "instruction.hpp"
#include <algorithm>
#include "exec_unit_register.hpp"

namespace back_end
{
namespace instructions
{

struct rrca : public instruction_of_type<rrca>
{
  rrca(exec_unit_register::label_type l = register_type_a::label) :  label(std::move(l)) {}
  void execute_using(const execution_unit::exec_unit_reg_descriptor& d) const
  {
    auto& a = *d.at(label);
    std::rotate(a.rbegin(), a.rbegin() + 1, a.rend());
  }

private:
    exec_unit_register::label_type label;
};

struct lrca : public instruction_of_type<lrca>
{
  lrca(exec_unit_register::label_type l = register_type_a::label) :  label(std::move(l)) {}
  void execute_using(const execution_unit::exec_unit_reg_descriptor& d) const
  {
    auto& a = *d.at(label);
    std::rotate(a.begin(), a.begin() + 1, a.end());
  }

private:
    exec_unit_register::label_type label;
};

}
}
