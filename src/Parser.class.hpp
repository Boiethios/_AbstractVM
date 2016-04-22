#pragma once

#include "Lexer.class.hpp"
#include "Stack.class.hpp"

class Parser
{
	public:
		Parser(void) = default;
		~Parser(void) = default;
		Parser(Parser const &) = delete;
		Parser & operator=(Parser const &) = delete;

		int
		operator()(Lexer & lexer, Stack & stack);

	private:
		IOperand const *
		getOperand(Lexer & lexer);
};
