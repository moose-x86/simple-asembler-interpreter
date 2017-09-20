#pragma once

#include "instructions/instruction.hpp"

#include <vector>
#include <memory>
#include <algorithm>
#include <iterator>
#include <cassert>

namespace back_end
{

class exec_unit_cache : private std::vector<std::unique_ptr<instruction>>
{
public:
  using cache_line = std::unique_ptr<instruction>;
  using cache_lines = std::vector<cache_line>;
  using cache_lines::size;
  using cache_lines::push_back;
  using cache_lines::value_type;
  using cache_lines::pop_back;
  using cache_lines::back;

  exec_unit_cache() { reserve(128); }

  instruction& operator[](const std::size_t i)
  {
    return *cache_lines::operator[](i);
  }

  void read_and_save(cache_lines&& movable)
  {
    assert(std::all_of(movable.begin(), movable.end(), [](auto& p){ return p != nullptr; }));
    std::move(movable.begin(), movable.end(), std::back_inserter(*this));
  }
};

using instructions_to_execute = exec_unit_cache::cache_lines;

}
