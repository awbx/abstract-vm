#include "operand-factory.hpp"
#include "operand.hpp"
#include "runtime-exception.hpp"

std::shared_ptr<const IOperand>
OperandFactory::createOperand(eOperandType type, const std::string &value) const {

  typedef std::shared_ptr<const IOperand> (OperandFactory::*CreateFn)(
      const std::string &) const;

  CreateFn creators[] = {
      &OperandFactory::createInt8,  &OperandFactory::createInt16,
      &OperandFactory::createInt32, &OperandFactory::createFloat,
      &OperandFactory::createDouble,
  };

  size_t index = static_cast<size_t>(type);
  if (index >= sizeof(creators) / sizeof(creators[0]))
    throw RuntimeException("Unknown operand type");

  return (this->*creators[index])(value);
}

std::shared_ptr<const IOperand>
OperandFactory::createInt8(const std::string &value) const {
  return std::make_shared<Int8>(value, eOperandType::Int8, 0);
}

std::shared_ptr<const IOperand>
OperandFactory::createInt16(const std::string &value) const {
  return std::make_shared<Int16>(value, eOperandType::Int16, 1);
}

std::shared_ptr<const IOperand>
OperandFactory::createInt32(const std::string &value) const {
  return std::make_shared<Int32>(value, eOperandType::Int32, 2);
}

std::shared_ptr<const IOperand>
OperandFactory::createFloat(const std::string &value) const {
  return std::make_shared<Float>(value, eOperandType::Float, 3);
}

std::shared_ptr<const IOperand>
OperandFactory::createDouble(const std::string &value) const {
  return std::make_shared<Double>(value, eOperandType::Double, 4);
}
