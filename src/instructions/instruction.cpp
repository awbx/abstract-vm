#include "instruction.hpp"

Instruction::Instruction(const std::string &op) {
  _op = op;
  _operand = nullptr;
}

const std::string &Instruction::getOp() const { return _op; }

void Instruction::setOperand(std::shared_ptr<const IOperand> operand) {
  _operand = operand;
}
std::shared_ptr<const IOperand> Instruction::getOperand() const { return _operand; }

Instruction::~Instruction() {}

// TODO: remove
std::ostream &operator<<(std::ostream &os, const Instruction &instruction) {
  os << "Instruction: " << instruction.getOp();
  if (instruction.getOperand()) {
    os << " | Operand: " << instruction.getOperand()->toString();
  }
  return os;
}