
#include "operand-factory.hpp"
#include "int8.hpp"

std::shared_ptr<const IOperand>
OperandFactory::createOperand(eOperandType type, std::string const &value) const {

  // Array of member function pointers to the specific operand creation functions
  typedef std::shared_ptr<const IOperand> (OperandFactory::*CreateOperandFn)(std::string const &value)
      const;

  CreateOperandFn createOperandFns[] = {
      &OperandFactory::createInt8, &OperandFactory::createInt8,
      &OperandFactory::createInt8, &OperandFactory::createInt8,
      &OperandFactory::createInt8,
      // TODO: Implement the rest of the operand creation functions
      //    &OperandFactory::createInt16,
      //   &OperandFactory::createInt32, &OperandFactory::createFloat,
      //   &OperandFactory::createDouble
  };

  return (this->*createOperandFns[type])(value);
}

std::shared_ptr<const IOperand>
OperandFactory::createInt8(std::string const &value) const {

  return std::make_shared<Int8Operand>(value);
}