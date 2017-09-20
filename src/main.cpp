#include "small_interpreter.hpp"
#include <iostream>
#include <sstream>
#include <regex>
#include <unistd.h>
#include <stdio.h>
#include <fstream>

namespace user_interface
{

bool is_terminal_prompt(const bool read_from_file = false)
{
  return isatty(fileno(stdin)) and !read_from_file;
}

void print_comand_prompt(const bool was_cout_written = false,
		                 const bool read_from_file = false)
{
  if(is_terminal_prompt(read_from_file))
  {
    if(was_cout_written)
	  std::cout << std::endl;

    std::cout << ">>> ";
  }
}

void main_loop(std::istream& ss, const bool read_from_file = false)
{
  if(is_terminal_prompt(read_from_file))
    std::cout << "Welcome to Simple assembler interpreter: " << std::endl;

  bool was_cout_written = false;
  print_comand_prompt(was_cout_written, read_from_file);

  small_interpreter si;
  si.register_on_out_command([&was_cout_written]{ was_cout_written = true; });

  std::string line;
  while(std::getline(ss, line) and line != "quit" and line != "q")
  {
      was_cout_written = false;
      si << line;

      print_comand_prompt(was_cout_written, read_from_file);
  }

  if(is_terminal_prompt(read_from_file))
    std::cout << std::endl << "Bye!!!" << std::endl;
}

}

int main(int argc, char* argv[])
{
  if(argc == 1)
  {
    user_interface::main_loop(std::cin);
  }
  else
  {
	std::ifstream f{argv[1]};
	user_interface::main_loop(f, true);
  }
}
