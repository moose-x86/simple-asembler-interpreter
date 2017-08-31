#pragma once

#include "exec_unit_cache.hpp"
#include <memory>

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

private:
  std::shared_ptr<hardware_bord> hw{};
};

}

