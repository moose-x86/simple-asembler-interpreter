#pragma once

#include "exec_unit_register.hpp"
#include "instruction.hpp"
#include <boost/variant.hpp>

namespace back_end
{
namespace instructions
{

class add : public instruction_of_type<add>
{
  struct visit : public boost::static_visitor<>
  {
      visit(exec_unit_register::label_type label,
            const execution_unit::exec_unit_reg_descriptor& d) : label(label), desc(d)
      {}

      void operator()(exec_unit_register::label_type source_label) const
      {
    	  const auto v1 = uint32_cast(*desc.at(label));
    	  const auto v2 = uint32_cast(*desc.at(source_label));

    	  *desc.at(label) = register_cast<exec_unit_register>(v1 + v2);
      }

      void operator()(exec_unit_register::hold_type sourec_value) const
      {
    	  const auto v1 = uint32_cast(*desc.at(label));
    	  *desc.at(label) = register_cast<exec_unit_register>(v1 + sourec_value);
      }

  private:
      exec_unit_register::label_type label;
      const execution_unit::exec_unit_reg_descriptor& desc;
  };

public:

  add(exec_unit_register::label_type label,
       exec_unit_register::hold_type source_value) : label(label), data(source_value)
  {}

  add(exec_unit_register::label_type label,
       exec_unit_register::label_type source_label) : label(label), data(source_label)
  {}

  void execute_using(const execution_unit::exec_unit_reg_descriptor& desc) const
  {
      boost::apply_visitor(visit(label, desc), data);
  }

private:
  exec_unit_register::label_type label;
  boost::variant<exec_unit_register::hold_type, exec_unit_register::label_type> data;
};

class mul : public instruction_of_type<mul>
{
  struct visit : public boost::static_visitor<>
  {
      visit(exec_unit_register::label_type label,
            const execution_unit::exec_unit_reg_descriptor& d) : label(label), desc(d)
      {}

      void operator()(exec_unit_register::label_type source_label) const
      {
    	  const auto v1 = uint32_cast(*desc.at(label));
    	  const auto v2 = uint32_cast(*desc.at(source_label));

    	  *desc.at(label) = register_cast<exec_unit_register>(v1 * v2);
      }

      void operator()(exec_unit_register::hold_type sourec_value) const
      {
    	  const auto v1 = uint32_cast(*desc.at(label));
    	  *desc.at(label) = register_cast<exec_unit_register>(v1 * sourec_value);
      }

  private:
      exec_unit_register::label_type label;
      const execution_unit::exec_unit_reg_descriptor& desc;
  };

public:

  mul(exec_unit_register::label_type label,
       exec_unit_register::hold_type source_value) : label(label), data(source_value)
  {}

  mul(exec_unit_register::label_type label,
       exec_unit_register::label_type source_label) : label(label), data(source_label)
  {}

  void execute_using(const execution_unit::exec_unit_reg_descriptor& desc) const
  {
      boost::apply_visitor(visit(label, desc), data);
  }

private:
  exec_unit_register::label_type label;
  boost::variant<exec_unit_register::hold_type, exec_unit_register::label_type> data;
};


struct no_operation : public instruction_of_type<no_operation>
{};


} // using instructions
} // using back_end
