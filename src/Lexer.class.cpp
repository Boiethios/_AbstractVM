#include "Lexer.class.hpp"
#include "Exception.class.hpp"

#include <iostream>

Lexer::Lexer(void) :
	_regex_commentary(";.*$")
{
}


bool
Lexer::processToken(std::string & tok)
{
	std::size_t	i;
	for (i = ops.size() - 1 ; i > 5 ; --i)
	{
		if (tok == ops[i])
		{
			_tokens.push({static_cast<Type>(i), ""});
			return true;
		}
	}

	std::istringstream	il(tok);
	std::string			tok_n;
	std::getline(il, tok, '(');
	std::getline(il, tok_n, ')');
	for (; i ; --i)
	{
		if (tok == ops[i])
		{
			_tokens.push({static_cast<Type>(i), tok_n});
			std::getline(il, tok);
			if (not tok.empty())
				break ;
			return true;
		}
	}
	std::cout << "Invalid token: [" << tok << "]\n";
	return false;
}

bool
Lexer::addLine(std::string line)
{
	line = std::regex_replace(line, _regex_commentary, "");
	for(char & c : line)
		if (c == '\t') c = ' ';

	bool				ret(true);
	std::istringstream	il(line);
	std::string			tok;
	while (std::getline(il, tok, ' '))
	{
		if (tok.empty())
			continue ;
		if (not processToken(tok))
			ret = false;
	}
	return ret;
}

Lexer::Token
Lexer::token(void)
{
	if (_tokens.empty())
		return {Type::END_OF_STREAM, ""};
	Token	token(_tokens.front());
	_tokens.pop();
	return Token(token);
}

std::vector<std::string> const	Lexer::ops {
	"",
	"int8",
	"int16",
	"int32",
	"float",
	"double",
	"push",
	"pop",
	"dump",
	"assert",
	"add",
	"sub",
	"mul",
	"div",
	"mod",
	"print",
	"exit",
};

