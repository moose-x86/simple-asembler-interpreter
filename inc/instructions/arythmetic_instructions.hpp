#pragma once

#include "exec_unit_register.hpp"
#include "instruction.hpp"
#include <boost/variant.hpp>
#include <functional>

namespace back_end
{
namespace instructions
{
namespace detail
{

template<typename operation>
class arythmetic_instructon
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

          operation op;
    	  *desc.at(label) = register_cast<exec_unit_register>(op(v1,v2));
      }

      void operator()(exec_unit_register::hold_type sourec_value) const
      {
    	  const auto v1 = uint32_cast(*desc.at(label));

          operation op;
    	  *desc.at(label) = register_cast<exec_unit_register>(op(v1, sourec_value));
      }

  private:
      exec_unit_register::label_type label;
      const execution_unit::exec_unit_reg_descriptor& desc;
  };

  exec_unit_register::label_type label;
  boost::variant<exec_unit_register::hold_type, exec_unit_register::label_type> data;

public:
  arythmetic_instructon(exec_unit_register::label_type label,
                        exec_unit_register::hold_type source_value) : label(label), data(source_value){}

  arythmetic_instructon(exec_unit_register::label_type label,
                        exec_unit_register::label_type source_label) : label(label), data(source_label){}

  void execute_using(const execution_unit::exec_unit_reg_descriptor& desc) const
  {
      boost::apply_visitor(visit(label, desc), data);
  }
};
}

struct add : public instruction_of_type<add>,
             public detail::arythmetic_instructon<std::plus<exec_unit_register::hold_type>>
{
  using arythmetic_instructon<std::plus<exec_unit_register::hold_type>>::arythmetic_instructon;
};

struct mul : public instruction_of_type<mul>,
             public detail::arythmetic_instructon<std::multiplies<exec_unit_register::hold_type>>
{
  using arythmetic_instructon<std::multiplies<exec_unit_register::hold_type>>::arythmetic_instructon;
};

struct bit_and : public instruction_of_type<bit_and>,
                 public detail::arythmetic_instructon<std::bit_and<exec_unit_register::hold_type>>
{
  using arythmetic_instructon<std::bit_and<exec_unit_register::hold_type>>::arythmetic_instructon;
};

struct bit_or : public instruction_of_type<bit_or>,
                 public detail::arythmetic_instructon<std::bit_or<exec_unit_register::hold_type>>
{
  using arythmetic_instructon<std::bit_or<exec_unit_register::hold_type>>::arythmetic_instructon;
};

struct bit_xor : public instruction_of_type<bit_xor>,
                 public detail::arythmetic_instructon<std::bit_xor<exec_unit_register::hold_type>>
{
  using arythmetic_instructon<std::bit_xor<exec_unit_register::hold_type>>::arythmetic_instructon;
};


} // using instructions
} // using back_end
