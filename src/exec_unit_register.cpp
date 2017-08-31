#include "exec_unit_register.hpp"
#include <numeric>

namespace back_end
{

const exec_unit_register::label_type register_type_a::label = "a";
const exec_unit_register::label_type register_type_b::label = "b";
const exec_unit_register::label_type register_type_c::label = "c";
const exec_unit_register::label_type register_type_d::label = "d";

exec_unit_register::hold_type uint32_cast(const exec_unit_register& r)
{
  static const auto pow2 = []{
    std::array<exec_unit_register::hold_type, exec_unit_register::length_in_bits> acc{1};
    std::generate(acc.begin() + 1, acc.end(), [p=1]() mutable { return p = 2*p; });

    return acc;
  }();

  return std::inner_product(pow2.begin(), pow2.end(), r.rbegin(), std::uint32_t{});
}

}
