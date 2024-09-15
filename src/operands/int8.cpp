#include "int8.hpp"
#include "operand-factory.hpp"


Int8Operand::Int8Operand(std::string const value) {
  long long val = std::stoll(value);
  if (val < std::numeric_limits<int8_t>::min() ||
      val > std::numeric_limits<int8_t>::max()) {
    throw std::overflow_error("Value out of range for Int8");
  }
  _value = static_cast<int8_t>(val);
  _repl = value;
}

int Int8Operand::getPrecision(void) const { return 0; }

eOperandType Int8Operand::getType(void) const { return eOperandType::Int8; }

std::shared_ptr<const IOperand> Int8Operand::operator+(IOperand const &rhs) const {
  eOperandType maxType = std::max(this->getType(), rhs.getType());
  int64_t result = static_cast<int64_t>(_value) + std::stoll(rhs.toString());

  OperandFactory factory;

  return factory.createOperand(maxType, std::to_string(result));
}

std::shared_ptr<const IOperand> Int8Operand::operator-(IOperand const &rhs) const {
  eOperandType maxType = std::max(this->getType(), rhs.getType());
  int64_t result = static_cast<int64_t>(_value) - std::stoll(rhs.toString());
  OperandFactory factory;

  return factory.createOperand(maxType, std::to_string(result));
}

std::shared_ptr<const IOperand> Int8Operand::operator*(IOperand const &rhs) const {
  eOperandType maxType = std::max(this->getType(), rhs.getType());
  int64_t result = static_cast<int64_t>(_value) * std::stoll(rhs.toString());
  OperandFactory factory;

  return factory.createOperand(maxType, std::to_string(result));
}

std::shared_ptr<const IOperand> Int8Operand::operator/(IOperand const &rhs) const {
  eOperandType maxType = std::max(this->getType(), rhs.getType());
  int64_t rhsValue = std::stoll(rhs.toString());
  if (rhsValue == 0) {
    throw std::runtime_error("Division by zero");
  }
  int64_t result = static_cast<int64_t>(_value) / rhsValue;
  OperandFactory factory;

  return factory.createOperand(maxType, std::to_string(result));
}

std::shared_ptr<const IOperand> Int8Operand::operator%(IOperand const &rhs) const {
  eOperandType maxType = std::max(this->getType(), rhs.getType());
  int64_t rhsValue = std::stoll(rhs.toString());
  if (rhsValue == 0) {
    throw std::runtime_error("Modulo by zero");
  }
  int64_t result = static_cast<int64_t>(_value) % rhsValue;
  OperandFactory factory;

  return factory.createOperand(maxType, std::to_string(result));
}

std::string const &Int8Operand::toString(void) const { return _repl; }

Int8Operand::~Int8Operand() { std::cout << "Int8Operand dtor" << std::endl; }