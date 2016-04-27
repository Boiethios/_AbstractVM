#include "Exception.class.hpp"

Exception::Exception(std::string const & what) :
	std::runtime_error(what)
{
}

Exception::Exception(Error err) :
	std::runtime_error(constructor(err))
{
}
std::string
Exception::constructor(Error err)
{
	switch (err)
	{
		case Error::DIV_ZERO:
			return "Divide by zero.";
		case Error::POP_EMPTY_STACK:
			return "Pop on empty stack.";
		case Error::ASSERT_EMPTY_STACK:
			return "Assert on empty stack.";
		case Error::NON_PRINTABLE_TYPE:
			return "The type is non printable.";
		case Error::MOD_ON_NON_INT:
			return "Modulo on non integer types.";
		case Error::SYNTAX_ERROR:
			return "Some syntax error occured, no execution.";
	}
	return "";
}
