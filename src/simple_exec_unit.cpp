#include "simple_exec_unit.hpp"
#include <iostream>

#include "instructions/all_instructions.hpp"

namespace back_end
{

simple_execution_unit::simple_execution_unit() : descriptor{
                                                    {register_type_a::label, std::addressof(reg_A)},
                                                    {register_type_b::label, std::addressof(reg_B)},
                                                    {register_type_c::label, std::addressof(reg_C)},
                                                    {register_type_d::label, std::addressof(reg_D)}}
{}

simple_execution_unit::~simple_execution_unit()
{
  bus_interface->close();
}

void simple_execution_unit::execute(const instructions::djnz& i)
{
  i.execute_using(reg_B, reg_IP);
}

void simple_execution_unit::execute(const instructions::out_register& o)
{
  o.execute_using(descriptor, *bus_interface);
}

void simple_execution_unit::execute(const instructions::no_operation&)
{}

void simple_execution_unit::execute(const instructions::add& i)
{
  i.execute_using(descriptor);
}

void simple_execution_unit::execute(const instructions::mul& i)
{
  i.execute_using(descriptor);
}

void simple_execution_unit::execute(const instructions::repeat& i)
{
  assert(typeid(*cache.back()) == typeid(instructions::repeat));

  i.execute_using(reg_IP);
  cache.pop_back();
}

void simple_execution_unit::execute(const instructions::rrca& i)
{
  i.execute_using(reg_A);
}

void simple_execution_unit::execute(const instructions::lrca& i)
{
  i.execute_using(reg_A);
}

void simple_execution_unit::execute(const instructions::load& i)
{
  i.execute_using(descriptor);
}

void simple_execution_unit::execute(std::unique_ptr<instruction> i)
{
  cache.push_back(std::move(i));
  execute_from_cache();
}

void simple_execution_unit::execute_from_cache()
{
  while(reg_IP < cache.size())
    cache[reg_IP++].execute_on(*this);
}

void simple_execution_unit::save_to_cache(instructions_to_execute&& set)
{
  cache.read_and_save(std::move(set));
}

std::shared_ptr<exec_unit_bus_to_register> simple_execution_unit::get_bus_to_registers()
{
  return bus_interface;
}

execution_unit& operator>>(instructions_to_execute&& set, simple_execution_unit& eu)
{
  eu.save_to_cache(std::move(set));
  eu.execute_from_cache();

  return eu;
}

} /* namespace back_end */
