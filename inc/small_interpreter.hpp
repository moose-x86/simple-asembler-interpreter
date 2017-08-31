#pragma once

#include <istream>
#include <vector>
#include "hardware_board.hpp"
#include "parser.hpp"
#include "translator.hpp"

class small_interpreter
{
public:
  small_interpreter();
  small_interpreter(std::ostream& s);

  friend std::istream& operator>>(std::istream&, small_interpreter&);
  friend small_interpreter& operator<<(small_interpreter& i, const std::string& s);

private:
  std::ostream& output;
  front_end::parser parser;
  front_end::translator translator;
  back_end::hardware_driver hardware_driver;
};


