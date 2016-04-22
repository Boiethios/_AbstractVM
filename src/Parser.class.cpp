#include "Parser.class.hpp"

#include "Exception.class.hpp"

int
Parser::operator()(Lexer & lexer, Stack & stack)
{
	Lexer::Token	token;

	while (true)
	{
		token = lexer.token();
		switch (token.type)
		{
			case Lexer::Type::END_OF_STREAM:
				throw Exception(Error::NO_EXIT);
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

	if (type > DOUBLE)
		throw Exception("Syntax error: Operand expected.");
	return OperandFactory::Get().createOperand(type, token.value);;
}
