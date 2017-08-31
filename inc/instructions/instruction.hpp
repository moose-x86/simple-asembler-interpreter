#pragma once

#include "execution_unit.hpp"

namespace back_end
{

struct instruction
{
  virtual void execute_on(execution_unit&) const = 0;
  virtual ~instruction() = default;
};

template< typename T >
struct instruction_of_type : public instruction
{
  using instruction_type = T;

  void execute_on(execution_unit& eu) const override
  {
    eu.execute(static_cast<const instruction_type&>(*this));
  }
};

}
