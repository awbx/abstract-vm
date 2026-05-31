#include "instruction.hpp"

Instruction::Instruction() : _op(""), _operand(nullptr), _line(0) {}

Instruction::Instruction(const std::string &op, size_t line)
    : _op(op), _operand(nullptr), _line(line) {}

Instruction::Instruction(const Instruction &other)
    : _op(other._op), _operand(other._operand), _line(other._line) {}

Instruction &Instruction::operator=(const Instruction &other) {
  if (this != &other) {
    _op = other._op;
    _operand = other._operand;
    _line = other._line;
  }
  return *this;
}

Instruction::~Instruction() {}

const std::string &Instruction::getOp() const { return _op; }
size_t Instruction::getLine() const { return _line; }

void Instruction::setOperand(std::shared_ptr<const IOperand> operand) {
  _operand = operand;
}

std::shared_ptr<const IOperand> Instruction::getOperand() const { return _operand; }
