#include "translator.hpp"

#include <iostream>
#include <memory>

#include "instructions/instruction_set_architecture.hpp"

namespace front_end
{

translator::translator()
{
    using namespace std::placeholders;

    inst["mul"] = std::bind(&translator::create_mul, this, _1);
    inst["add"] = std::bind(&translator::create_add, this, _1);
    inst["ld"]   = std::bind(&translator::create_load, this, _1);
    inst["out"]  = std::bind(&translator::create_out,  this, _1);
    inst["rrca"] = std::bind(&translator::create_rrca, this, _1);
    inst["lrca"] = std::bind(&translator::create_lrca, this, _1);
    inst["djnz"] = std::bind(&translator::create_djnz, this, _1);
    inst["sleep"] = std::bind(&translator::create_sleep, this, _1);
    inst["repeat"] = std::bind(&translator::create_repeat, this, _1);
    inst["and"] = std::bind(&translator::create_bit_and, this, _1);
    inst["or"] = std::bind(&translator::create_bit_or, this, _1);
    inst["xor"] = std::bind(&translator::create_bit_xor, this, _1);
}

back_end::instructions_to_execute translator::create_instruction_from(const parser::command& c)
{
  using namespace back_end;

  instructions_to_execute instructions;
  auto is_label = [this](auto& v){ return v.size() == 1 and inst.count(v.front()) == 0; };

  try
  {
    if(not c.empty())
    {
      if(is_label(c))
      {
        instructions.push_back(std::make_unique<instructions::no_operation>());
        labels.insert({c.at(0), code_lines});
      }
      else
      {
        auto i = inst.at(c.at(0))(c);
        std::move(i.begin(), i.end(), std::back_inserter(instructions));
      }
    }
  }
  catch(std::out_of_range& e)
  {
    throw std::logic_error{"unknown instruction " + c.front()};
  }
  catch(std::exception& e)
  {
    throw std::logic_error{"syntax error in <" + c.front() + ">: " + e.what()};
  }

  code_lines += instructions.size();
  return instructions;
}

translator::ret translator::create_load(const parser::command& c)
{
  using namespace back_end;

  ret result{};

  try
  {
    auto val = std::stoul(c.at(2));
    result.push_back(std::make_unique<instructions::load>(c.at(1), val));
  }
  catch(std::logic_error&)
  {
    result.push_back(std::make_unique<instructions::load>(c.at(1), c.at(2)));
  }

  return result;
}

translator::ret translator::create_bit_and(const parser::command& c)
{
  using namespace back_end;

  ret result{};

  try
  {
    auto val = std::stoul(c.at(2));
    result.push_back(std::make_unique<instructions::bit_and>(c.at(1), val));
  }
  catch(std::logic_error&)
  {
    result.push_back(std::make_unique<instructions::bit_and>(c.at(1), c.at(2)));
  }

  return result;
}

translator::ret translator::create_bit_or(const parser::command& c)
{
  using namespace back_end;

  ret result{};

  try
  {
    auto val = std::stoul(c.at(2));
    result.push_back(std::make_unique<instructions::bit_or>(c.at(1), val));
  }
  catch(std::logic_error&)
  {
    result.push_back(std::make_unique<instructions::bit_or>(c.at(1), c.at(2)));
  }

  return result;
}

translator::ret translator::create_bit_xor(const parser::command& c)
{
  using namespace back_end;

  ret result{};

  try
  {
    auto val = std::stoul(c.at(2));
    result.push_back(std::make_unique<instructions::bit_xor>(c.at(1), val));
  }
  catch(std::logic_error&)
  {
    result.push_back(std::make_unique<instructions::bit_xor>(c.at(1), c.at(2)));
  }

  return result;
}

translator::ret translator::create_add(const parser::command& c)
{
  using namespace back_end;

  ret result{};

  try
  {
    auto val = std::stoul(c.at(2));
    result.push_back(std::make_unique<instructions::add>(c.at(1), val));
  }
  catch(std::logic_error&)
  {
    result.push_back(std::make_unique<instructions::add>(c.at(1), c.at(2)));
  }

  return result;
}

translator::ret translator::create_mul(const parser::command& c)
{
  using namespace back_end;

  ret result{};

  try
  {
    auto val = std::stoul(c.at(2));
    result.push_back(std::make_unique<instructions::mul>(c.at(1), val));
  }
  catch(std::logic_error&)
  {
    result.push_back(std::make_unique<instructions::mul>(c.at(1), c.at(2)));
  }

  return result;
}

translator::ret translator::create_out(const parser::command& c)
{
  using namespace back_end;
  auto registers = register_spec::specs;
  ret instructions{};

  if(c.at(1) != "(0)")
    throw std::runtime_error{"first parameter should be 0"};

  if(not registers.count(c.at(2)))
      throw std::runtime_error{"second parameter should be register"};

  instructions.push_back(std::make_unique<instructions::out_register>(c.at(2)));
  return instructions;
}

translator::ret translator::create_sleep(const parser::command& c)
{
  using namespace back_end;

  ret instructions{};
  instructions.push_back(std::make_unique<instructions::sleep>(std::stof(c.at(1))));

  return instructions;
}

translator::ret translator::create_rrca(const parser::command& c)
{
  using namespace back_end;

  ret instructions{};
  instructions.push_back(std::make_unique<instructions::rrca>(c.at(1)));

  return instructions;
}

translator::ret translator::create_lrca(const parser::command& c)
{
  using namespace back_end;

  ret instructions{};
  instructions.push_back(std::make_unique<instructions::lrca>(c.at(1)));

  return instructions;
}

translator::ret translator::create_djnz(const parser::command& c)
{
  using namespace back_end;

  ret instructions{};
  instructions.push_back(std::make_unique<instructions::djnz>(labels.at(c.at(1))));

  return instructions;
}

translator::ret translator::create_repeat(const parser::command& c)
{
  using namespace back_end;

  ret instructions{};
  instructions.push_back(std::make_unique<instructions::repeat>());

  return instructions;
}


back_end::instructions_to_execute operator>>(parser::command&& cmd, translator& t)
{
  return t.create_instruction_from(cmd);
}

} /* namespace front_end */
