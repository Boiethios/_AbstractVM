#pragma once

#include <stdexcept>

enum class Error
{
	SYNTAX_ERROR,
	DIV_ZERO,
	POP_EMPTY_STACK,
	ASSERT_EMPTY_STACK,
	NON_PRINTABLE_TYPE,
	MOD_ON_NON_INT,
};

class Exception : public std::runtime_error
{
	public:
		Exception(std::string const & what);
		Exception(Error err);

		~Exception(void) = default;
		Exception(Exception const &) = default;
		Exception & operator=(Exception const &) = delete;

	private:
		std::string
		constructor(Error err);
};
