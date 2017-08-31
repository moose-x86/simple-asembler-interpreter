#pragma once

#include <array>
#include <string>
#include <cmath>
#include <algorithm>
#include <cassert>

namespace back_end
{

using register_bit = bool;

struct exec_unit_register : private std::array<register_bit, 32>
{
  using this_type = std::array<register_bit, 32>;
  using hold_type = std::uint32_t;
  using label_type = std::string;
  enum { length_in_bits = this_type{}.size() };
  exec_unit_register() : this_type{{}} {}

  using this_type::value_type;
  using this_type::size;
  using this_type::begin;
  using this_type::end;
  using this_type::rbegin;
  using this_type::rend;
  using this_type::at;
};

struct register_type_a : public exec_unit_register
{
	static const label_type label;
};

struct register_type_b : public exec_unit_register
{
	static const label_type label;
};

struct register_type_c : public exec_unit_register
{
	static const label_type label;
};

struct register_type_d : public exec_unit_register
{
	static const label_type label;
};

using register_type_ip = std::uint32_t;
exec_unit_register::hold_type uint32_cast(const exec_unit_register& r);

template<typename register_type>
inline register_type register_cast(exec_unit_register::hold_type n)
{
  register_type r;
  std::for_each(r.rbegin(), r.rend(), [&n](auto& b){ b = n & 1; n /= 2; });

  return r;
}

}
