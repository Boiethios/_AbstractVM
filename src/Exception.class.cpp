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
	}
	return "";
}
