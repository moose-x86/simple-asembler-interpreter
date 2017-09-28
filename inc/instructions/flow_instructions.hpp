#pragma once

#include "instruction.hpp"
#include "exec_unit_register.hpp"
#include <chrono>

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
   sleep(float time) : time(time) {}
   void execute() const
   {
       using namespace std::chrono_literals;
       using namespace std::chrono;
       auto ms = duration_cast<microseconds>(1s);
       usleep(ms.count() * time);
   }

private:
   const float time;
};

}
}
