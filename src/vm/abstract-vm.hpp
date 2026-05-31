#pragma once

#include "common.hpp"
#include "instruction.hpp"
#include "ioperand.hpp"

class AbstractVM {
private:
  std::vector<std::shared_ptr<const IOperand>> _stack;
  bool _exited;

public:
  AbstractVM();
  AbstractVM(const AbstractVM &other);
  AbstractVM &operator=(const AbstractVM &other);
  ~AbstractVM();

  void execute(const std::vector<Instruction> &instructions);

private:
  void doPush(const Instruction &instr);
  void doPop(const Instruction &instr);
  void doDump(const Instruction &instr);
  void doAssert(const Instruction &instr);
  void doAdd(const Instruction &instr);
  void doSub(const Instruction &instr);
  void doMul(const Instruction &instr);
  void doDiv(const Instruction &instr);
  void doMod(const Instruction &instr);
  void doPrint(const Instruction &instr);
  void doExit(const Instruction &instr);

  void requireBinaryOperands();
  std::pair<std::shared_ptr<const IOperand>, std::shared_ptr<const IOperand>>
  popPair();
};
