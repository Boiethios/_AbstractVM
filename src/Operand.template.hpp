#pragma once

#include "IOperand.interface.hpp"
#include "Exception.class.hpp"

static inline IOperand const *
do_op(IOperand const & operand1, IOperand const & operand2, char op)
{
	eOperandType	type(std::max(operand1.getType(), operand2.getType()));
	double			result;
	std::string		value;

	// TODO: operation
	switch (op)
	{
		case '+':
			result = operand1.toDouble() + operand2.toDouble();
			break ;
		case '-':
			result = operand1.toDouble() - operand2.toDouble();
			break ;
		case '*':
			result = operand1.toDouble() * operand2.toDouble();
			break ;
		case '/':
			if (not operand2.toDouble())
				throw (Exception(Error::DIV_ZERO));
			result = operand1.toDouble() / operand2.toDouble();
			break ;
		case '%':
			if (not operand2.toDouble())
				throw (Exception(Error::DIV_ZERO));
			result = 0.;
			break ;
		default:
			/* OOPS */
			throw (Exception("Impossible error.")) ;
	}
	(void)result;
	return IOperand::factory.createOperand(type, value);
}


template<typename T>
class Operand : public IOperand
{
		T const					_value;

	public:
		Operand(T value) : _value(value)
		{
		}

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
		str(void) const
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


		double
		toDouble(void) const
		{
			return static_cast<double>(_value);
		}
};
