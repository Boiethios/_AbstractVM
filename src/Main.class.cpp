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

void
Main::process_line(std::string & line)
{
std::cout << "Line [" << line << "]\n";
}

int
Main::run(void)
{
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
		process_line(buff);
	}
	// Process stored infos
	return 0;
}
