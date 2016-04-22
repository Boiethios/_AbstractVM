#include "Main.class.hpp"

#include <iostream>
#include <fstream>

#include "Exception.class.hpp"

Main::Main(int argc, char **argv) :
	_args(argc)
{
	for (int i(0) ; i < argc ; ++i)
		_args[i] = argv[i];
	process_args();
}
Main::~Main(void)
{
	if (_input != &std::cin)
		delete _input;
}


void
Main::process_args(void)
{
	if (_args.size() == 1)
		_input = &std::cin;
	else if (_args.size() == 2)
		_input = new std::ifstream(_args[1]);
	else
		throw Exception("Too much arguments.");
	if (not _input or not *_input)
		throw Exception("Invalid stream.");
}

int
Main::run(void)
{
	bool	ok(true);
	while (*_input)
	{
		std::string		buff;
		std::getline(*_input, buff);
		if(_input == &std::cin)
		{
			if (not *_input)
				throw Exception("End of stream (std::cin).");
			if (buff[0] == ';' and buff[1] == ';')
				break ;
		}
		ok &= _lexer.addLine(buff);
	}
	if (not ok)
		return -2;
	return _parser(_lexer, _stack);
}
