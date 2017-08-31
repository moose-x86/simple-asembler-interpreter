#pragma once

#include <memory>

#include "bus_to_regiseter.hpp"
#include "led.hpp"

namespace back_end
{

class led_controller
{
public:
  led_controller(led_strip&, const std::shared_ptr<const bus_to_register>, const std::shared_ptr<bus_state_notifier>);

  void on_bus_state_change();

private:
  const std::shared_ptr<const bus_to_register> bus;
  const led_strip& leds;
};

} /* namespace back_end */

