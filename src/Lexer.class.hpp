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
				INT8,
				INT16,
				INT32,
				FLOAT,
				DOUBLE,
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
			};

			Type		type;
			std::string	value;
			std::size_t	line;
		};

		typedef Token::Type Type;

		Lexer(void);

		~Lexer(void) = default;
		Lexer(Lexer const &) = delete;
		Lexer & operator=(Lexer const &) = delete;

		bool
		addLine(std::string line, std::size_t n_line);

		void
		addToken(Lexer::Token tok);

		Lexer::Token
		token(void);

	private:
		bool
		processToken(std::string & token, std::size_t n_line);

		std::queue<Token>			_tokens;

		std::regex const			_regex_commentary;

		static std::vector<std::string> const	ops;
};
