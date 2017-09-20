#pragma once

#include "instruction.hpp"
#include "exec_unit_register.hpp"
#include "bus_to_regiseter.hpp"

namespace back_end
{
namespace instructions
{

struct out_register : public instruction_of_type<out_register>
{
    out_register(exec_unit_register::label_type l) :  label(std::move(l)) {}

    void execute_using(const execution_unit::exec_unit_reg_descriptor& d, bus_state_notify_api& b) const
    {
        b.notify_on_change_of(d.at(label));
    }

private:
    exec_unit_register::label_type label;
};

}
}
