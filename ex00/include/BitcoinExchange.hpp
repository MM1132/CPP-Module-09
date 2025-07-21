#pragma once

#include "utils.hpp"

#include <vector>
#include <string>
#include <ctime>

struct Quote
{
	Date date;
	float value;
};

class BitcoinExchange
{
	private:
		std::string m_databaseFilename;
		std::vector<Quote> m_quotes;
		
	public:
		BitcoinExchange(std::string filename);

		void printQuotes() const;
};
