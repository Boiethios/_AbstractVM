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
	for (i = 1 ; i < ops.size() - 5 ; ++i)
	{
		if (tok == ops[i])
		{
			_tokens.push({(Type)i, ""});
			return true;
		}
	}

	std::istringstream	il(tok);
	std::string			tok_n;
	std::getline(il, tok, '(');
	std::getline(il, tok_n, ')');
	for (; i < ops.size() ; ++i)
	{
		if (tok == ops[i])
		{
			_tokens.push({(Type)i, tok_n});
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
	std::regex_replace(line, _regex_commentary, "");
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
	return Token();
}

std::vector<std::string> const	Lexer::ops {
	"",
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
	"int8",
	"int16",
	"int32",
	"float",
	"double",
};

