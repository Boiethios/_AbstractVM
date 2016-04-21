#include "Stack.class.hpp"

#include "Exception.class.hpp"

#include <iostream>

Stack::Stack(void)
{
}


void
Stack::push(IOperand const *operand)
{
	this->push_front(operand);
}

IOperand const *
Stack::pop(void)
{
	if (this->empty())
		throw Exception(Error::POP_EMPTY_STACK);
	IOperand const *op(this->front());

	this->pop_front();
	return op;
}

void
Stack::dump(void) const
{
	static std::string const type_names[]{
		"\033[4mInt8    \033[0m ",
		"\033[4mInt16   \033[0m ",
		"\033[4mInt32   \033[0m ",
		"\033[4mFloat   \033[0m ",
		"\033[4mDouble  \033[0m ",
	};

	std::cout << "\033[7m[TOP]   \033[0m\n";
	if (this->empty())
		std::cout << "(empty)\n";
	else for (auto & op : *this)
		std::cout << type_names[op->getPrecision()] << op->toString() << "\n";
}

void
Stack::assert(IOperand const *operand) const
{
	if (this->empty())
		throw Exception(Error::ASSERT_EMPTY_STACK);
	if (this->front()->toString() != operand->toString())
		throw Exception(std::string("Assertion failed: ") + this->front()->toString()
						+ "!=" + operand->toString());
}

void
Stack::print(void) const
{
	if (this->empty())
		throw Exception(Error::ASSERT_EMPTY_STACK);
	if (this->front()->getType() != INT8)
		throw Exception(Error::NON_PRINTABLE_TYPE);
	std::cout << static_cast<char>(std::stoi(this->front()->toString()));
}


void
Stack::add(void)
{
	IOperand const	*op1(this->pop());
	this->push(*(this->pop()) + *op1);
}

void
Stack::sub(void)
{
	IOperand const	*op1(this->pop());
	this->push(*(this->pop()) - *op1);
}

void
Stack::mul(void)
{
	IOperand const	*op1(this->pop());
	this->push(*(this->pop()) * *op1);
}

void
Stack::div(void)
{
	IOperand const	*op1(this->pop());
	this->push(*(this->pop()) / *op1);
}

void
Stack::mod(void)
{
	IOperand const	*op1(this->pop());
	this->push(*(this->pop()) % *op1);
}
