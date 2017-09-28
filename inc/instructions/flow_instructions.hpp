#pragma once

#include "instruction.hpp"
#include "exec_unit_register.hpp"

namespace back_end
{
namespace instructions
{

struct no_operation : public instruction_of_type<no_operation>
{};

struct repeat : public instruction_of_type<repeat>
{
  void execute_using(register_type_ip& ip) const
  {
    ip = {};
  }
};

struct sleep : public instruction_of_type<sleep>
{
public:
   sleep(std::uint32_t time) : time(time) {}
   void execute() const { usleep(time); }

private:
   std::uint32_t time{};
};

}
}
