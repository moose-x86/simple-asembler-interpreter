#include "parser.hpp"
#include <iostream>
#include <regex>
#include <boost/algorithm/string.hpp>

namespace front_end
{

parser::command operator>>(const std::string& s, parser& p)
{
  return p.parse_line(s);
}

parser::command parser::parse_line(const std::string& line)
{
  command cmd;
  token copy{line};

  boost::trim(copy);

  if(copy.front() != '#')
  {
    std::regex re("[a-z]+|[().0-9]+");
    std::sregex_iterator next(copy.begin(), copy.end(), re);
    std::sregex_iterator end;

    while (next != end)
        cmd.push_back(std::smatch{*next++}.str());

  }
  return cmd;
}


} /* namespace front_end */
