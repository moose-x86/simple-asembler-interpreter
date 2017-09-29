#pragma once

#include "exec_unit_register.hpp"
#include "execution_unit.hpp"
#include "exec_unit_cache.hpp"
#include <boost/range/algorithm/for_each.hpp>
#include "bus_to_regiseter.hpp"

namespace back_end
{

class simple_execution_unit final : public execution_unit
{
public:
  simple_execution_unit(std::shared_ptr<out_command_callback> c);
  ~simple_execution_unit();

  void execute_from_cache();
  void save_to_cache(instructions_to_execute&&);
  void execute(std::unique_ptr<instruction>);
  std::shared_ptr<exec_unit_bus_to_register> get_bus_to_registers();

private:
  void execute(const instructions::djnz&) override;
  void execute(const instructions::rrca&) override;
  void execute(const instructions::lrca&) override;
  void execute(const instructions::load&) override;
  void execute(const instructions::repeat&) override;
  void execute(const instructions::add&) override;
  void execute(const instructions::mul&) override;
  void execute(const instructions::no_operation&) override;
  void execute(const instructions::out_register&) override;
  void execute(const instructions::sleep&) override;
  void execute(const instructions::bit_or&) override;
  void execute(const instructions::bit_xor&) override;
  void execute(const instructions::bit_and&) override;

  const exec_unit_reg_descriptor descriptor{};
  exec_unit_cache  cache{};
  register_type_a  reg_A{};
  register_type_b  reg_B{};
  register_type_c  reg_C{};
  register_type_d  reg_D{};
  register_type_e  reg_E{};
  register_type_f  reg_F{};
  register_type_g  reg_G{};
  register_type_h  reg_H{};
  register_type_ip reg_IP{};

  std::shared_ptr<closeble_bus_to_register> bus_interface = std::make_shared<closeble_bus_to_register>();
  std::shared_ptr<out_command_callback> callbacks;
};

execution_unit& operator>>(instructions_to_execute&& i, simple_execution_unit& eu);

}

