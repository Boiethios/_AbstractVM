#pragma once

#include <stdexcept>

enum class Error
{
	DIV_ZERO,
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
