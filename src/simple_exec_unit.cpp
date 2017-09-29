#include "simple_exec_unit.hpp"
#include <iostream>
#include <boost/bind/apply.hpp>
#include "instructions/instruction_set_architecture.hpp"

namespace back_end
{

simple_execution_unit::simple_execution_unit(std::shared_ptr<out_command_callback> c) :
		                                        descriptor{
                                                    {register_type_a::label, std::addressof(reg_A)},
                                                    {register_type_b::label, std::addressof(reg_B)},
                                                    {register_type_c::label, std::addressof(reg_C)},
                                                    {register_type_d::label, std::addressof(reg_D)},
                                                    {register_type_e::label, std::addressof(reg_E)},
                                                    {register_type_f::label, std::addressof(reg_F)},
                                                    {register_type_g::label, std::addressof(reg_G)},
                                                    {register_type_h::label, std::addressof(reg_H)}},
													callbacks{c}
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
  boost::for_each(*callbacks, boost::apply<void>());
}

void simple_execution_unit::execute(const instructions::no_operation&)
{}

void simple_execution_unit::execute(const instructions::sleep& i)
{
  i.execute();
}

void simple_execution_unit::execute(const instructions::add& i)
{
  i.execute_using(descriptor);
}

void simple_execution_unit::execute(const instructions::bit_and& i)
{
  i.execute_using(descriptor);
}

void simple_execution_unit::execute(const instructions::bit_xor& i)
{
  i.execute_using(descriptor);
}

void simple_execution_unit::execute(const instructions::bit_or& i)
{
  i.execute_using(descriptor);
}

void simple_execution_unit::execute(const instructions::mul& i)
{
  i.execute_using(descriptor);
}

void simple_execution_unit::execute(const instructions::repeat& i)
{
  auto& last_inst_in_cache = *cache.back();
  assert(typeid(last_inst_in_cache) == typeid(instructions::repeat));

  i.execute_using(reg_IP);
  cache.pop_back();
}

void simple_execution_unit::execute(const instructions::rrca& i)
{
  i.execute_using(descriptor);
}

void simple_execution_unit::execute(const instructions::lrca& i)
{
  i.execute_using(descriptor);
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
  while(reg_IP < cache.size()) try
  {
    cache[reg_IP++].execute_on(*this);
  }
  catch(const std::exception& e)
  {
    std::cerr << "Execution error: " << e.what() << std::endl;
  }
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
