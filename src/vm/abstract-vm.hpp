#pragma once

#include "common.hpp"
#include "instruction.hpp"
#include "ioperand.hpp"

class AbstractVM {
private:
  std::stack<std::shared_ptr<const IOperand>> _stack; // Stack to hold operands

public:
  // TODO: implement canonical form
  AbstractVM();
  ~AbstractVM();

  void execute(const std::vector<Instruction> &instructions);

  void push(std::shared_ptr<const IOperand> operand);
  void print(std::shared_ptr<const IOperand> operand);
  void add(std::shared_ptr<const IOperand> operand);
  void exit(std::shared_ptr<const IOperand> operand);

private:
  // void sub(std::shared_ptr<const IOperand> operand);
  // void mul(std::shared_ptr<const IOperand> operand);
  // void div(std::shared_ptr<const IOperand> operand);
  // void mod(std::shared_ptr<const IOperand> operand);
  // void dump(std::shared_ptr<const IOperand> operand);
  // void assert(std::shared_ptr<const IOperand> operand);
};