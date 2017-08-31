#include "small_interpreter.hpp"
#include <iostream>
#include <sstream>
#include <regex>
#include <unistd.h>
#include <stdio.h>

void print_comand_prompt()
{
  if(isatty(fileno(stdin)))
    std::cout << ">>> ";
}

int main(int, char**)
{
  std::cout << "Welcome to Simple assembler interpreter: " << std::endl;
  print_comand_prompt();

  small_interpreter si;
  std::string line;

  while(std::getline(std::cin, line) and line != "quit" and line != "q")
  {
      si << line;
      print_comand_prompt();
  }

  std::cout << "Bye!!!" << std::endl;
}
