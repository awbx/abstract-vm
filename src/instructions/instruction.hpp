
#pragma once

#include "common.hpp"
#include "ioperand.hpp"

class Instruction {
private:
  std::string _op;
  const IOperand *_operand;

public:
  Instruction(const std::string &op);

  const std::string &getOp() const;

  void setOperand(const IOperand *operand);
  const IOperand *getOperand() const;

  ~Instruction();
};

std::ostream &operator<<(std::ostream &os, const Instruction &instruction);