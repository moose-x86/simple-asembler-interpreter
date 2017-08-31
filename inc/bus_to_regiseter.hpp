#pragma once

#include <vector>
#include <functional>

#include "exec_unit_register.hpp"

namespace back_end
{

struct bus_to_register
{
  using bus_line = register_type_a::value_type;

  virtual bus_line get_bus_line(const std::uint32_t i) const = 0;
  virtual ~bus_to_register() = default;
};

struct bus_state_notifier
{
  using callback_type = std::function<void ()>;

  virtual void register_on_change(const callback_type&) = 0;
  virtual ~bus_state_notifier() = default;
};

class exec_unit_bus_to_register : public bus_to_register,
                                  public bus_state_notifier
{};


struct bus_state_notify_api
{
  virtual void impulse_on_state_change_bus_line(const exec_unit_register* reg) = 0;
  virtual ~bus_state_notify_api() = default;
};

class closeble_bus_to_register : public exec_unit_bus_to_register,
							     public bus_state_notify_api
{
public:
  closeble_bus_to_register();

  void close();
  void impulse_on_state_change_bus_line(const exec_unit_register* reg) override;

private:
  void register_on_change(const callback_type&) override;
  bus_line get_bus_line(const std::uint32_t) const override;

  const exec_unit_register* ptr_to_register_a{nullptr};
  std::vector<callback_type> state_change_notify_callbacks;
};

} /* namespace back_end */

