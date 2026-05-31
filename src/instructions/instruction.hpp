#pragma once

#include "common.hpp"
#include "ioperand.hpp"

class Instruction {
private:
  std::string _op;
  std::shared_ptr<const IOperand> _operand;
  size_t _line;

public:
  Instruction();
  Instruction(const std::string &op, size_t line);
  Instruction(const Instruction &other);
  Instruction &operator=(const Instruction &other);
  ~Instruction();

  const std::string &getOp() const;
  size_t getLine() const;

  void setOperand(std::shared_ptr<const IOperand> operand);
  std::shared_ptr<const IOperand> getOperand() const;
};
