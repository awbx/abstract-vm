#include "instruction.hpp"

Instruction::Instruction(const std::string &op) {
  _op = op;
  _operand = nullptr;
}

const std::string &Instruction::getOp() const { return _op; }

void Instruction::setOperand(const IOperand *operand) { _operand = operand; }
const IOperand *Instruction::getOperand() const { return _operand; }

Instruction::~Instruction() {
  // TODO: figure out why this is causing a segfault
  // if (_operand) {
  //   delete _operand;
  // }
}

// TODO: remove
std::ostream &operator<<(std::ostream &os, const Instruction &instruction) {
  os << "Instruction: " << instruction.getOp();
  if (instruction.getOperand()) {
    os << " | Operand: " << instruction.getOperand()->toString();
  }
  return os;
}