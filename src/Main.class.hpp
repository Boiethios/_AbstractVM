#pragma once

#include <vector>
#include <string>
#include <istream>

#include "Stack.class.hpp"
#include "Lexer.class.hpp"

class Main
{
	public:
		Main(int argc, char **argv);

		~Main(void);
		Main(Main const &) = delete;
		Main & operator=(Main const &) = delete;

		void
		process_args(void);

		int
		run(void);

	private:
		std::vector<std::string>	_args;
		std::istream				*_input = nullptr;
		Stack						_stack;
		Lexer						_lexer;
};
