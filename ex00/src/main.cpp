#include "BitcoinExchange.hpp"

#include <iostream>
#include <exception>

int main(int ac, char** av)
{
	if (ac != 2)
	{
		std::cerr << "We only need one file as argument -_-" << std::endl;
		return 0;
	}

	try
	{
		BitcoinExchange bitcoinExchange("data.csv");
		(void)av[1];

		bitcoinExchange.printQuotes();
		// bitcoinExchange.simulateAccount(av[1]);
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}
