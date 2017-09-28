#include "led_controller.hpp"
#include <boost/range/adaptor/indexed.hpp>
#include <boost/range/algorithm/copy.hpp>

namespace back_end
{

led_controller::led_controller(led_strip& leds,
                               const std::shared_ptr<const bus_to_register> br,
                               const std::shared_ptr<bus_state_notifier> bn) : bus(br), leds(leds)
{
  bn->register_on_change( [this]{ on_bus_state_change(); } );
}

void led_controller::on_bus_state_change()
{
  using namespace boost::adaptors;

  for(const auto& led : leds | indexed(0))
  {
    if ( bus->get_bus_line(led.index()) )
    {
      led.value()->switch_on();
    }
    else
    {
      led.value()->switch_off();
    }
  }
}

} /* namespace back_end */
