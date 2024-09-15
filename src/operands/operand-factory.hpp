#pragma once

#include "common.hpp"
#include "ioperand.hpp"

class OperandFactory {
public:
  std::shared_ptr<const IOperand> createOperand(eOperandType type,
                                                std::string const &value) const;

  std::shared_ptr<const IOperand> createInt8(std::string const &value) const;
  std::shared_ptr<const IOperand> createInt16(std::string const &value) const;
  std::shared_ptr<const IOperand> createInt32(std::string const &value) const;
  std::shared_ptr<const IOperand> createFloat(std::string const &value) const;
  std::shared_ptr<const IOperand> createDouble(std::string const &value) const;
};
