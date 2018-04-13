#pragma once

#include "instruction.hpp"
#include "exec_unit_register.hpp"
#include <chrono>
#include <thread>

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
   sleep(float alfa) : time(time) {}
   void execute() const
   {
       using namespace std::chrono_literals;
       using namespace std::chrono;
       std::this_thread::sleep_for(alfa * 1s);
   }

private:
   const float time;
};

}
}
