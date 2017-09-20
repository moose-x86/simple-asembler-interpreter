#include "small_interpreter.hpp"
#include <iostream>
#include <vector>

small_interpreter::small_interpreter() : output(std::cerr)
{
}
small_interpreter::small_interpreter(std::ostream& ss) : output(ss)
{
}

std::istream& operator>>(std::istream& in, small_interpreter& i)
{
  std::string line;
  while(std::getline(in, line)) i << line;
  return in;
}

void small_interpreter::register_on_out_command(std::function<void()> f)
{
  hardware_driver.register_on_out_command(f);
}

small_interpreter& operator<<(small_interpreter& interpreter, const std::string& line)
{
  try
  {
     line >> interpreter.parser
          >> interpreter.translator
          >> interpreter.hardware_driver.get_serial_interface();
  }
  catch(const std::exception& e)
  {
     interpreter.output << "#error: " << e.what() << std::endl;
  }

  return interpreter;
}
