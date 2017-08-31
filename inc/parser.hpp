#pragma once

#include <vector>
#include <string>

namespace front_end
{

class parser
{
public:
  using token = std::string;
  using command = std::vector<token>;

  command parse_line(const std::string&);
};

parser::command operator>>(const std::string&, parser&);

} /* namespace front_end */

