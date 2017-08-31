#include <boost/range/algorithm/for_each.hpp>
#include "../inc/bus_to_regiseter.hpp"

namespace back_end
{

closeble_bus_to_register::closeble_bus_to_register() : ptr_to_register_a{}
{
}

void closeble_bus_to_register::close()
{
  ptr_to_register_a = nullptr;
  state_change_notify_callbacks.clear();
}

void closeble_bus_to_register::impulse_on_state_change_bus_line(const exec_unit_register* reg)
{
  ptr_to_register_a = reg;
  boost::for_each(state_change_notify_callbacks, [](auto& p){ p(); });
}

bus_to_register::bus_line closeble_bus_to_register::get_bus_line(const std::uint32_t i) const
{
  if(not ptr_to_register_a)
    throw std::runtime_error("Error, bus interface is closed");

  try
  {
      return ptr_to_register_a->at(i);
  }
  catch(std::exception&)
  {}

  return {};
}

void closeble_bus_to_register::register_on_change(const callback_type& callback)
{
  state_change_notify_callbacks.push_back(callback);
}

} /* namespace back_end */
