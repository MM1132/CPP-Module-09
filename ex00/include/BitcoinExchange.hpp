#pragma once

#include "utils.hpp"

#include <vector>
#include <string>
#include <ctime>

struct Quote
{
	Date date;
	float price;
};

class BitcoinExchange
{
	private:
		std::string m_databaseFilename;
		std::vector<Quote> m_quotes;
		
	public:
		BitcoinExchange(std::string filename);

		void printQuotes() const;
		void simulateAccount(std::string accountFilename) const;
		float getClosestPrice(Date date);
};
