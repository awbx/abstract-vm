#pragma once

#include "common.hpp"
#include "ioperand.hpp"
#include "operand-factory.hpp"
#include "runtime-exception.hpp"

#include <cmath>
#include <iomanip>
#include <sstream>
#include <type_traits>

template <typename T> class Operand : public IOperand {
private:
  T _value;
  eOperandType _type;
  int _precision;
  std::string _repr;

  static std::string format(T value);
  static std::shared_ptr<const IOperand> makeResult(eOperandType type, long double value);
  static long double readValue(const IOperand &op);

public:
  Operand();
  Operand(const std::string &value, eOperandType type, int precision);
  Operand(const Operand &other);
  Operand &operator=(const Operand &other);
  ~Operand() override;

  int getPrecision() const override;
  eOperandType getType() const override;

  std::shared_ptr<const IOperand> operator+(const IOperand &rhs) const override;
  std::shared_ptr<const IOperand> operator-(const IOperand &rhs) const override;
  std::shared_ptr<const IOperand> operator*(const IOperand &rhs) const override;
  std::shared_ptr<const IOperand> operator/(const IOperand &rhs) const override;
  std::shared_ptr<const IOperand> operator%(const IOperand &rhs) const override;

  const std::string &toString() const override;
};

template <typename T>
Operand<T>::Operand() : _value(static_cast<T>(0)), _type(eOperandType::Int8), _precision(0) {
  _repr = format(_value);
}

template <typename T>
Operand<T>::Operand(const std::string &value, eOperandType type, int precision)
    : _type(type), _precision(precision) {

  if constexpr (std::is_integral_v<T>) {
    long long parsed = 0;
    try {
      parsed = std::stoll(value);
    } catch (const std::out_of_range &) {
      throw RuntimeException("Overflow on value '" + value + "'");
    } catch (const std::invalid_argument &) {
      throw RuntimeException("Invalid numeric value '" + value + "'");
    }
    if (parsed < static_cast<long long>(std::numeric_limits<T>::min()) ||
        parsed > static_cast<long long>(std::numeric_limits<T>::max())) {
      if (parsed < 0)
        throw RuntimeException("Underflow on value '" + value + "'");
      throw RuntimeException("Overflow on value '" + value + "'");
    }
    _value = static_cast<T>(parsed);
  } else {
    long double parsed = 0;
    try {
      parsed = std::stold(value);
    } catch (const std::out_of_range &) {
      throw RuntimeException("Overflow on value '" + value + "'");
    } catch (const std::invalid_argument &) {
      throw RuntimeException("Invalid numeric value '" + value + "'");
    }
    if (parsed > static_cast<long double>(std::numeric_limits<T>::max()))
      throw RuntimeException("Overflow on value '" + value + "'");
    if (parsed < static_cast<long double>(std::numeric_limits<T>::lowest()))
      throw RuntimeException("Underflow on value '" + value + "'");
    _value = static_cast<T>(parsed);
  }

  _repr = format(_value);
}

template <typename T>
Operand<T>::Operand(const Operand &other)
    : _value(other._value), _type(other._type), _precision(other._precision),
      _repr(other._repr) {}

template <typename T> Operand<T> &Operand<T>::operator=(const Operand &other) {
  if (this != &other) {
    _value = other._value;
    _type = other._type;
    _precision = other._precision;
    _repr = other._repr;
  }
  return *this;
}

template <typename T> Operand<T>::~Operand() {}

template <typename T> int Operand<T>::getPrecision() const { return _precision; }

template <typename T> eOperandType Operand<T>::getType() const { return _type; }

template <typename T> const std::string &Operand<T>::toString() const { return _repr; }

template <typename T> std::string Operand<T>::format(T value) {
  std::ostringstream oss;
  if constexpr (std::is_integral_v<T>)
    oss << static_cast<long long>(value);
  else
    oss << value;
  return oss.str();
}

template <typename T> long double Operand<T>::readValue(const IOperand &op) {
  try {
    return std::stold(op.toString());
  } catch (const std::exception &) {
    throw RuntimeException("Invalid numeric value '" + op.toString() + "'");
  }
}

template <typename T>
std::shared_ptr<const IOperand> Operand<T>::makeResult(eOperandType type, long double value) {
  if (!std::isfinite(value))
    throw RuntimeException("Result is not a finite number");

  OperandFactory factory;
  std::ostringstream oss;
  if (type <= eOperandType::Int32) {
    if (value > static_cast<long double>(std::numeric_limits<long long>::max()))
      throw RuntimeException("Overflow on arithmetic result");
    if (value < static_cast<long double>(std::numeric_limits<long long>::min()))
      throw RuntimeException("Underflow on arithmetic result");
    oss << static_cast<long long>(value);
  } else {
    oss << std::setprecision(std::numeric_limits<long double>::digits10 + 1) << value;
  }
  return factory.createOperand(type, oss.str());
}

template <typename T>
std::shared_ptr<const IOperand> Operand<T>::operator+(const IOperand &rhs) const {
  eOperandType resultType = std::max(getType(), rhs.getType());
  long double result = static_cast<long double>(_value) + readValue(rhs);
  return makeResult(resultType, result);
}

template <typename T>
std::shared_ptr<const IOperand> Operand<T>::operator-(const IOperand &rhs) const {
  eOperandType resultType = std::max(getType(), rhs.getType());
  long double result = static_cast<long double>(_value) - readValue(rhs);
  return makeResult(resultType, result);
}

template <typename T>
std::shared_ptr<const IOperand> Operand<T>::operator*(const IOperand &rhs) const {
  eOperandType resultType = std::max(getType(), rhs.getType());
  long double result = static_cast<long double>(_value) * readValue(rhs);
  return makeResult(resultType, result);
}

template <typename T>
std::shared_ptr<const IOperand> Operand<T>::operator/(const IOperand &rhs) const {
  eOperandType resultType = std::max(getType(), rhs.getType());
  long double b = readValue(rhs);
  if (b == 0.0L)
    throw RuntimeException("Division by zero");
  long double result = static_cast<long double>(_value) / b;
  return makeResult(resultType, result);
}

template <typename T>
std::shared_ptr<const IOperand> Operand<T>::operator%(const IOperand &rhs) const {
  eOperandType resultType = std::max(getType(), rhs.getType());
  long double b = readValue(rhs);
  if (b == 0.0L)
    throw RuntimeException("Modulo by zero");
  long double result = std::fmodl(static_cast<long double>(_value), b);
  return makeResult(resultType, result);
}

typedef Operand<int8_t> Int8;
typedef Operand<int16_t> Int16;
typedef Operand<int32_t> Int32;
typedef Operand<float> Float;
typedef Operand<double> Double;
