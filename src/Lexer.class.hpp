#pragma once

#include <string>
#include <queue>
#include <regex>
#include <vector>

class Lexer
{
	public:
		struct Token
		{
			enum class Type
			{
				END_OF_STREAM,
				PUSH,
				POP,
				DUMP,
				ASSERT,
				ADD,
				SUB,
				MUL,
				DIV,
				MOD,
				PRINT,
				EXIT,
				INT8,
				INT16,
				INT32,
				FLOAT,
				DOUBLE,
			};

			Type		type;
			std::string value;
		};

		typedef Token::Type Type;

		Lexer(void);

		~Lexer(void) = default;
		Lexer(Lexer const &) = default;
		Lexer & operator=(Lexer const &) = default;

		bool
		addLine(std::string line);

		Lexer::Token
		token(void);

	private:
		bool
		processToken(std::string & token);

		std::queue<Token>	_tokens;

		std::regex const	_regex_commentary;

		static std::vector<std::string> const	ops;
};
