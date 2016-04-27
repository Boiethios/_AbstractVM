#include "Parser.class.hpp"
#include "Exception.class.hpp"

#include <iostream>

enum class SyntaxError
{
	NO_EXIT,
	INEXPECTED_OPERAND,
	OPERAND_WAS_NEEDED,
};

static inline bool
disp_error(SyntaxError err, std::size_t n_line)
{
	std::cout << "[" << n_line << "] Syntax error: ";
	switch (err)
	{
		case SyntaxError::NO_EXIT:
			std::cout << "No exit instruction encoutered.\n";
			break;
		case SyntaxError::INEXPECTED_OPERAND:
			std::cout << "Operand without push or assert instruction.\n";
			break;
		case SyntaxError::OPERAND_WAS_NEEDED:
			std::cout << "Operand needed.\n";
			break;
	}
	return true;
}

void
Parser::check_syntax(Lexer & lexer, Lexer & new_lexer)
{
	Lexer::Token	token;
	std::size_t		last_line(0ul);
	bool			must_be_operand(false);
	bool			exit_found(false);
	bool			error(false);

	while (true)
	{
		token = lexer.token();
		switch (token.type)
		{
			case Lexer::Type::END_OF_STREAM:
				if (not exit_found)
				{
					error = disp_error(SyntaxError::NO_EXIT, last_line + 1);
				}
				if (error)
					throw Exception(Error::SYNTAX_ERROR);
				return ;
			case Lexer::Type::INT8:
			case Lexer::Type::INT16:
			case Lexer::Type::INT32:
			case Lexer::Type::FLOAT:
			case Lexer::Type::DOUBLE:
				if (not must_be_operand)
					error = disp_error(SyntaxError::INEXPECTED_OPERAND, token.line);
				else
					must_be_operand = false;
				break ;
			case Lexer::Type::PUSH:
			case Lexer::Type::ASSERT:
				must_be_operand = true;
				break ;
			case Lexer::Type::POP:
			case Lexer::Type::DUMP:
			case Lexer::Type::ADD:
			case Lexer::Type::SUB:
			case Lexer::Type::MUL:
			case Lexer::Type::DIV:
			case Lexer::Type::MOD:
			case Lexer::Type::PRINT:
				if (must_be_operand)
				{
					error = disp_error(SyntaxError::OPERAND_WAS_NEEDED, token.line);
					must_be_operand = false;
				}
				break ;
			case Lexer::Type::EXIT:
				exit_found = true;
		}
		last_line = token.line;
		new_lexer.addToken(token);
	}
}

int
Parser::operator()(Lexer & old_lexer, Stack & stack)
{
	Lexer::Token	token;
	Lexer			lexer;

	check_syntax(old_lexer, lexer);

	while (true)
	{
		token = lexer.token();
		switch (token.type)
		{
			case Lexer::Type::END_OF_STREAM:
				// never happen
			case Lexer::Type::INT8:
			case Lexer::Type::INT16:
			case Lexer::Type::INT32:
			case Lexer::Type::FLOAT:
			case Lexer::Type::DOUBLE:
				throw Exception("Syntax error: Operand without instruction.");
			case Lexer::Type::PUSH:
				stack.push(getOperand(lexer));
				break ;
			case Lexer::Type::POP:
				stack.pop();
				break ;
			case Lexer::Type::DUMP:
				stack.dump();
				break ;
			case Lexer::Type::ASSERT:
				stack.assert(getOperand(lexer));
				break ;
			case Lexer::Type::ADD:
				stack.add();
				break ;
			case Lexer::Type::SUB:
				stack.sub();
				break ;
			case Lexer::Type::MUL:
				stack.mul();
				break ;
			case Lexer::Type::DIV:
				stack.div();
				break ;
			case Lexer::Type::MOD:
				stack.mod();
				break ;
			case Lexer::Type::PRINT:
				stack.print();
				break ;
			case Lexer::Type::EXIT:
				return 0;
		}
	}
	/* Never reached */
	return 0;
}

IOperand const *
Parser::getOperand(Lexer & lexer)
{
	Lexer::Token	token(lexer.token());
	eOperandType	type(static_cast<eOperandType>(static_cast<int>(token.type) - 1));

	if (type > Double)
		throw Exception("Syntax error: Operand expected.");
	return OperandFactory::Get().createOperand(type, token.value);;
}
