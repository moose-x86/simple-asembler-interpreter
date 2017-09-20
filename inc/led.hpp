#pragma once
#include <memory>
#include <forward_list>
#include <ostream>

namespace back_end
{

struct led
{
  virtual void switch_on() = 0;
  virtual void switch_off() = 0;
  virtual ~led() = default;
};

using led_strip = std::forward_list<std::unique_ptr<led>>;

struct blue_led : public led
{
  blue_led(std::ostream& os) : physical_layer(os) {}

  void switch_on() { physical_layer << "*"; }
  void switch_off() { physical_layer << "."; }

private:
  std::ostream& physical_layer;
};

struct empty_led : public led
{
  empty_led(std::ostream& os) : physical_layer(os) {}

  void switch_on()
  {
      physical_layer << "\r";
      physical_layer.flush();
  }
  void switch_off()
  {
      physical_layer << "\r";
      physical_layer.flush();
  }

private:
  std::ostream& physical_layer;
};

} /* namespace back_end */
