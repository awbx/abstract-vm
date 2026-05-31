#include "abstract-vm.hpp"
#include "runtime-exception.hpp"

AbstractVM::AbstractVM() : _exited(false) {}

AbstractVM::AbstractVM(const AbstractVM &other)
    : _stack(other._stack), _exited(other._exited) {}

AbstractVM &AbstractVM::operator=(const AbstractVM &other) {
  if (this != &other) {
    _stack = other._stack;
    _exited = other._exited;
  }
  return *this;
}

AbstractVM::~AbstractVM() {}

void AbstractVM::execute(const std::vector<Instruction> &instructions) {
  typedef void (AbstractVM::*Handler)(const Instruction &);

  const std::map<std::string, Handler> dispatch = {
      {"push", &AbstractVM::doPush},     {"pop", &AbstractVM::doPop},
      {"dump", &AbstractVM::doDump},     {"assert", &AbstractVM::doAssert},
      {"add", &AbstractVM::doAdd},       {"sub", &AbstractVM::doSub},
      {"mul", &AbstractVM::doMul},       {"div", &AbstractVM::doDiv},
      {"mod", &AbstractVM::doMod},       {"print", &AbstractVM::doPrint},
      {"exit", &AbstractVM::doExit},
  };

  for (const auto &instr : instructions) {
    auto it = dispatch.find(instr.getOp());
    if (it == dispatch.end())
      throw RuntimeException("Line " + std::to_string(instr.getLine()) +
                             " : Unknown instruction '" + instr.getOp() + "'");
    try {
      (this->*(it->second))(instr);
    } catch (const RuntimeException &e) {
      throw RuntimeException("Line " + std::to_string(instr.getLine()) +
                             " : " + e.what());
    }
    if (_exited)
      return;
  }
  throw RuntimeException("Missing 'exit' instruction at end of program");
}

void AbstractVM::doPush(const Instruction &instr) {
  _stack.push_back(instr.getOperand());
}

void AbstractVM::doPop(const Instruction &) {
  if (_stack.empty())
    throw RuntimeException("Pop on empty stack");
  _stack.pop_back();
}

void AbstractVM::doDump(const Instruction &) {
  for (auto it = _stack.rbegin(); it != _stack.rend(); ++it)
    std::cout << (*it)->toString() << "\n";
}

void AbstractVM::doAssert(const Instruction &instr) {
  if (_stack.empty())
    throw RuntimeException("Assert on empty stack");
  auto top = _stack.back();
  auto expected = instr.getOperand();
  if (top->getType() != expected->getType() ||
      top->toString() != expected->toString())
    throw RuntimeException("Assertion failed: top is " + top->toString() +
                           " expected " + expected->toString());
}

void AbstractVM::requireBinaryOperands() {
  if (_stack.size() < 2)
    throw RuntimeException("Arithmetic instruction needs at least 2 values on stack");
}

std::pair<std::shared_ptr<const IOperand>, std::shared_ptr<const IOperand>>
AbstractVM::popPair() {
  auto rhs = _stack.back();
  _stack.pop_back();
  auto lhs = _stack.back();
  _stack.pop_back();
  return {lhs, rhs};
}

void AbstractVM::doAdd(const Instruction &) {
  requireBinaryOperands();
  auto [lhs, rhs] = popPair();
  _stack.push_back(*lhs + *rhs);
}

void AbstractVM::doSub(const Instruction &) {
  requireBinaryOperands();
  auto [lhs, rhs] = popPair();
  _stack.push_back(*lhs - *rhs);
}

void AbstractVM::doMul(const Instruction &) {
  requireBinaryOperands();
  auto [lhs, rhs] = popPair();
  _stack.push_back(*lhs * *rhs);
}

void AbstractVM::doDiv(const Instruction &) {
  requireBinaryOperands();
  auto [lhs, rhs] = popPair();
  _stack.push_back(*lhs / *rhs);
}

void AbstractVM::doMod(const Instruction &) {
  requireBinaryOperands();
  auto [lhs, rhs] = popPair();
  _stack.push_back(*lhs % *rhs);
}

void AbstractVM::doPrint(const Instruction &) {
  if (_stack.empty())
    throw RuntimeException("Print on empty stack");
  auto top = _stack.back();
  if (top->getType() != eOperandType::Int8)
    throw RuntimeException("Print expects an Int8 on top of the stack");
  int value = std::stoi(top->toString());
  std::cout << static_cast<char>(value) << "\n";
}

void AbstractVM::doExit(const Instruction &) { _exited = true; }
