#pragma once

#include "instruction.hpp"
#include "exec_unit_register.hpp"
#include <boost/variant.hpp>

namespace back_end
{
namespace instructions
{

struct load : public instruction_of_type<load>
{
  struct visit : public boost::static_visitor<>
  {
      visit(exec_unit_register::label_type label,
            const execution_unit::exec_unit_reg_descriptor& d) : label(label), desc(d)
      {}

      void operator()(exec_unit_register::label_type source_label) const
      {
          *desc.at(label) = *desc.at(source_label);
      }

      void operator()(exec_unit_register::hold_type sourec_value) const
      {
         *desc.at(label) = register_cast<exec_unit_register>(sourec_value);
      }

  private:
      exec_unit_register::label_type label;
      const execution_unit::exec_unit_reg_descriptor& desc;
  };

public:

  load(exec_unit_register::label_type label,
       exec_unit_register::hold_type source_value) : label(label), data(source_value)
  {}

  load(exec_unit_register::label_type label,
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

}
}

