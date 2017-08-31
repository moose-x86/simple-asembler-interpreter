#pragma once

#include "instruction.hpp"
#include "exec_unit_register.hpp"

namespace back_end
{
namespace instructions
{

struct djnz : public instruction_of_type<djnz>
{
  djnz(const register_type_ip a) : ip_value{a} {}
  void execute_using(back_end::register_type_b& b, register_type_ip& ip) const
  {
    const auto n = uint32_cast(b);

    if(n > 0)
    {
      b = register_cast<register_type_b>(n - 1);
      ip = ip_value;
    }
  }

private:
  register_type_ip ip_value{0};
};

struct repeat : public instruction_of_type<repeat>
{
  void execute_using(register_type_ip& ip) const
  {
    ip = {};
  }
};

}

}
