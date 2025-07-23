#include "RPN.hpp"

#include <iostream>
#include <exception>

int main(int ac, char** av)
{
	if (ac != 2)
	{
		std::cerr << "Enter all the arguments as a single string" << std::endl;
		return 0;
	}

	try
	{
		int result = reversePolishNotation(av[1]);
		std::cout << "Result: " << result << std::endl;
	}
	catch (char const *e)
	{
		std::cout << "Error: " << e << std::endl;
	}

	return 0;
}
