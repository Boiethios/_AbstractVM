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
		void
		check_syntax(Lexer & lexer, Lexer & new_lexer);

		IOperand const *
		getOperand(Lexer & lexer);
};
