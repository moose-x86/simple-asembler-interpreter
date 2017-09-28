#pragma once

#include <unordered_map>
#include <functional>
#include "exec_unit_cache.hpp"
#include "parser.hpp"

namespace front_end
{

class translator
{
public:
  translator();
  back_end::instructions_to_execute create_instruction_from(const parser::command& cmd);

private:
  std::uint32_t code_lines{0};

  using ret = back_end::instructions_to_execute;
  using handler = std::function<ret(const parser::command&)>;

  std::unordered_map<parser::token, handler> inst{};
  std::unordered_map<parser::token, std::uint32_t> labels{};

  ret create_load(const parser::command&);
  ret create_out (const parser::command&);
  ret create_rrca(const parser::command&);
  ret create_lrca(const parser::command&);
  ret create_djnz(const parser::command&);
  ret create_add(const parser::command&);
  ret create_mul(const parser::command&);
  ret create_sleep(const parser::command&);
  ret create_repeat(const parser::command&);
  ret create_bit_and(const parser::command&);
  ret create_bit_or(const parser::command&);
  ret create_bit_xor(const parser::command&);
};

back_end::instructions_to_execute operator>>(parser::command&&, translator&);

} /* namespace front_end */

