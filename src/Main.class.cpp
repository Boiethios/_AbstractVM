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
	std::size_t	n_line(0);
	bool		ok(true);
	while (_input->good())
	{
		std::string		buff;
		std::getline(*_input, buff);
		ok &= _lexer.addLine(buff, ++n_line);
		if(_input == &std::cin)
		{
			if (not *_input)
				throw Exception("End of stream (std::cin).");
			if (buff.find(";;") != std::string::npos)
				_input->setstate(std::ios_base::eofbit);
			if (not ok)
				return -2;
		}
	}
	if (not ok)
		return -2;

	return _parser(_lexer, _stack);
}
