#pragma once

#include "exec_unit_cache.hpp"
#include <memory>
#include <vector>
#include <functional>
#include "execution_unit.hpp"

namespace back_end
{
struct hardware_bord;

struct serial_interface
{
  serial_interface(std::shared_ptr<hardware_bord> h);
  friend serial_interface& operator>>(back_end::instructions_to_execute&& soi, serial_interface& si);

private:
  std::shared_ptr<hardware_bord> hw;
};

class hardware_driver
{
public:
    hardware_driver();
	serial_interface& get_serial_interface();
	void register_on_out_command(std::function<void()>);

private:
  std::shared_ptr<hardware_bord> hw{};
  std::shared_ptr<execution_unit::out_command_callback> callbacks_set{};
};

}

