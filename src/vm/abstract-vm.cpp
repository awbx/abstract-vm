#include "abstract-vm.hpp"

AbstractVM::AbstractVM() {}

AbstractVM::~AbstractVM() {}

void AbstractVM::exit(std::shared_ptr<const IOperand> operand) {
  (void)operand;
  std::exit(0);
}

void AbstractVM::push(std::shared_ptr<const IOperand> operand) { _stack.push(operand); }

void AbstractVM::print(std::shared_ptr<const IOperand> operand) {
  (void)operand;
  if (_stack.empty()) {
    throw std::runtime_error("Stack is empty");
  }

  auto top = _stack.top();
  if (top->getType() != eOperandType::Int8) {
    throw std::runtime_error("Expected Int8");
  }

  std::cout << top->toString() << std::endl;
}

void AbstractVM::add(std::shared_ptr<const IOperand> operand) {
  (void)operand;
  if (_stack.size() < 2) {
    throw std::runtime_error("Stack has less than 2 elements");
  }

  auto rhs = _stack.top();
  _stack.pop();
  auto lhs = _stack.top();
  _stack.pop();

  auto result = (*lhs) + (*rhs);
  _stack.push(result);
}

void AbstractVM::execute(const std::vector<Instruction> &instructions) {

  for (const auto &instr : instructions) {
    auto op = instr.getOp();

    std::map<std::string, void (AbstractVM::*)(std::shared_ptr<const IOperand>)> ops = {
        {"push", &AbstractVM::push},
        {"print", &AbstractVM::print},
        {"add", &AbstractVM::add},
        {"exit", &AbstractVM::exit},
        // {"pop", &AbstractVM::pop},
        // {"dump", &AbstractVM::dump},
        // {"assert", &AbstractVM::assert},
        // {"sub", &AbstractVM::sub},
        // {"mul", &AbstractVM::mul},
        // {"div", &AbstractVM::div},
        // {"mod", &AbstractVM::mod},
    };

    if (ops.find(op) == ops.end()) {
      throw std::runtime_error("Unknown operation");
    }

    auto operand = instr.getOperand();
    (this->*ops[op])(operand);
  }
}