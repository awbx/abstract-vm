
#pragma once

#include "common.hpp"

enum eOperandType { Int8, Int16, Int32, Float, Double };

class IOperand {
public:
  virtual int getPrecision(void) const = 0;     // Precision of the type of the instance
  virtual eOperandType getType(void) const = 0; // Type of the instance
  virtual std::shared_ptr<const IOperand> operator+(IOperand const &rhs) const = 0; // Sum
  virtual std::shared_ptr<const IOperand>
  operator-(IOperand const &rhs) const = 0; // Difference
  virtual std::shared_ptr<const IOperand>
  operator*(IOperand const &rhs) const = 0; // Product
  virtual std::shared_ptr<const IOperand>
  operator/(IOperand const &rhs) const = 0; // Quotient
  virtual std::shared_ptr<const IOperand>
  operator%(IOperand const &rhs) const = 0; // Modulo
  virtual std::string const &
  toString(void) const = 0; // String representation of the instance
  virtual ~IOperand(void) {}
};