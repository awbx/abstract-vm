#pragma once

#include "common.hpp"
#include "instruction.hpp"
#include "ioperand.hpp"

class AbstractVM {
private:
  std::stack<const IOperand *> _stack; // Stack to hold operands

public:
  // TODO: implement canonical form
  AbstractVM();
  ~AbstractVM();

  void execute(const std::vector<Instruction> &instructions);

  void push(const IOperand *operand);
  void print(const IOperand *operand);
  void add(const IOperand *operand);

private:
  //   void sub(const IOperand *operand);
  //   void mul(const IOperand *operand);
  //   void div(const IOperand *operand);
  //   void mod(const IOperand *operand);
  //   void exit(const IOperand *operand);
  //   void dump(const IOperand *operand);
  //   void assert(const IOperand *operand);
};