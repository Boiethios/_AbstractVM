#pragma once

#include "eOperandType.enum.hpp"
#include "OperandFactory.class.hpp"

#include <string>

class IOperand
{
	public:
//		static OperandFactory		factory;

		virtual int					getPrecision( void ) const = 0;
		virtual eOperandType		getType( void ) const = 0;

		virtual IOperand const		*operator+( IOperand const &rhs ) const = 0;
		virtual IOperand const		*operator-( IOperand const &rhs ) const = 0;
		virtual IOperand const		*operator*( IOperand const &rhs ) const = 0;
		virtual IOperand const		*operator/( IOperand const &rhs ) const = 0;
		virtual IOperand const		*operator%( IOperand const &rhs ) const = 0;

		virtual std::string			toString( void ) const = 0;

		virtual ~IOperand( void )	{}
};
