#include "Main.class.hpp"
#include "Exception.class.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
	Main		app(argc, argv);

	try
	{
		return app.run();
	}
	catch (Exception const &e)
	{
		std::cout << "Exception: " << e.what() << "\n";
	}
	catch (...)
	{
		std::cout << "OOPS !?!\n";
	}

	return -1;
}
