#pragma once

class IOperand;

#include "eOperandType.enum.hpp"

#include <array>

class OperandFactory
{
	public:
		OperandFactory(void);

		~OperandFactory(void) = default;
		OperandFactory(OperandFactory const &) = delete;
		OperandFactory & operator=(OperandFactory const &) = delete;

		IOperand const *
		createOperand(eOperandType type, std::string const & value) const;

	private:
		typedef IOperand const *(OperandFactory::*func_t)(std::string const &) const;

		IOperand const *
		createInt8(std::string const &value) const;

		IOperand const *
		createInt16(std::string const &value) const;

		IOperand const *
		createInt32(std::string const &value) const;

		IOperand const *
		createFloat(std::string const &value) const;

		IOperand const *
		createDouble(std::string const &value) const;

		std::array<func_t, 5>	_funcs;
};
