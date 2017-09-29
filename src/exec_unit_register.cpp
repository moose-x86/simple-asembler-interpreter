#include "exec_unit_register.hpp"
#include <numeric>

namespace back_end
{

const exec_unit_register::label_type register_type_a::label = "a";
const exec_unit_register::label_type register_type_b::label = "b";
const exec_unit_register::label_type register_type_c::label = "c";
const exec_unit_register::label_type register_type_d::label = "d";
const exec_unit_register::label_type register_type_e::label = "e";
const exec_unit_register::label_type register_type_f::label = "f";
const exec_unit_register::label_type register_type_g::label = "g";
const exec_unit_register::label_type register_type_h::label = "h";

std::set<exec_unit_register::label_type> register_spec::specs{
      register_type_a::label,
      register_type_b::label,
      register_type_c::label,
      register_type_d::label,
      register_type_e::label,
      register_type_f::label,
      register_type_g::label,
      register_type_h::label
};

exec_unit_register::hold_type uint32_cast(const exec_unit_register& r)
{
  static const auto pow2 = []{
    std::array<exec_unit_register::hold_type, exec_unit_register::length_in_bits> acc{{1}};
    std::generate(acc.begin() + 1, acc.end(), [p=1]() mutable { return p = 2*p; });

    return acc;
  }();

  return std::inner_product(pow2.begin(), pow2.end(), r.rbegin(), std::uint32_t{});
}

}
