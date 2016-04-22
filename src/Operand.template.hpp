#pragma once

#include "IOperand.interface.hpp"
#include "Exception.class.hpp"

#include <iostream>
inline double
opToDouble(IOperand const & op)
{
	return std::stod(op.toString());
}

inline int
opToInt(IOperand const & op)
{
	return std::stoi(op.toString());
}

static inline IOperand const *
do_op(IOperand const & operand1, IOperand const & operand2, char op)
{
	eOperandType	type(std::max(operand1.getType(), operand2.getType()));
	double			result;
	std::string		value;

//std::cout << "DEBUG: " << operand1.toString() << " " << op << " " << operand2.toString() << "\n";
	switch (op)
	{
		case '+':
			result = opToDouble(operand1) + opToDouble(operand2);
			break ;
		case '-':
			result = opToDouble(operand1) - opToDouble(operand2);
			break ;
		case '*':
			result = opToDouble(operand1) * opToDouble(operand2);
			break ;
		case '/':
			if (not opToDouble(operand2))
				throw (Exception(Error::DIV_ZERO));
			result = opToDouble(operand1) / opToDouble(operand2);
			break ;
		case '%':
			if (not opToDouble(operand2))
				throw (Exception(Error::DIV_ZERO));
			if (type >= FLOAT)
				throw (Exception(Error::MOD_ON_NON_INT));
			result = opToInt(operand1) % opToInt(operand2);
			break ;
		default: /* OOPS */
			throw (Exception("Impossible error.")) ;
	}
	if (type >= FLOAT)
		return OperandFactory::Get().createOperand(type, std::to_string(result));
	return OperandFactory::Get().createOperand(type, std::to_string(static_cast<int>(result)));
}


template<typename T>
class Operand : public IOperand
{
	friend class OperandFactory;

		T const					_value;

		/* Use OperandFactory to construct an Operand */
		Operand(T value) : _value(value)
		{
		}

	public:
		~Operand(void) = default;
		Operand(Operand const &) = default;
		Operand & operator=(Operand const &) = default;


		int
		getPrecision(void) const
		{
			return static_cast<int>(this->getType());
		}

		eOperandType
		getType(void) const;

		std::string
		toString(void) const
		{
			return std::to_string(_value);
		}


		IOperand const *
		operator +(IOperand const &rhs) const
		{ return do_op(*this, rhs, '+'); }

		IOperand const *
		operator -(IOperand const &rhs) const
		{ return do_op(*this, rhs, '-'); }

		IOperand const *
		operator *(IOperand const &rhs) const
		{ return do_op(*this, rhs, '*'); }

		IOperand const *
		operator /(IOperand const &rhs) const
		{ return do_op(*this, rhs, '/'); }

		IOperand const *
		operator %(IOperand const &rhs) const
		{ return do_op(*this, rhs, '%'); }
};
