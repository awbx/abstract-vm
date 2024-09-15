#include "int8.hpp"

Int8Operand::Int8Operand(std::string const value) {
  _value = std::stoi(value);
  _repl = value;
}

int Int8Operand::getPrecision(void) const { return 0; }

eOperandType Int8Operand::getType(void) const { return Int8; }

IOperand const *Int8Operand::operator+(IOperand const &rhs) const {

  auto result = _value + std::stoi(rhs.toString());

  return new Int8Operand(std::to_string(result));
}

IOperand const *Int8Operand::operator-(IOperand const &rhs) const {
  (void)rhs;
  return nullptr;
}

IOperand const *Int8Operand::operator*(IOperand const &rhs) const {
  (void)rhs;
  return nullptr;
}

IOperand const *Int8Operand::operator/(IOperand const &rhs) const {
  (void)rhs;
  return nullptr;
}

IOperand const *Int8Operand::operator%(IOperand const &rhs) const {
  (void)rhs;
  return nullptr;
}

std::string const &Int8Operand::toString(void) const { return _repl; }
