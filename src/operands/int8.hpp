#pragma once

#include "ioperand.hpp"
#include "operand-factory.hpp"

class Int8Operand : public IOperand {
  int8_t _value;
  std::string _repl;

public:
  Int8Operand(std::string const value);

  int getPrecision(void) const override;
  eOperandType getType(void) const override;
  IOperand const *operator+(IOperand const &rhs) const override;
  IOperand const *operator-(IOperand const &rhs) const override;
  IOperand const *operator*(IOperand const &rhs) const override;
  IOperand const *operator/(IOperand const &rhs) const override;
  IOperand const *operator%(IOperand const &rhs) const override;
  std::string const &toString(void) const override;

  ~Int8Operand() override = default;
};
