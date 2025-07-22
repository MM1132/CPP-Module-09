#pragma once

#include "Date.hpp"

#include <vector>
#include <string>
#include <ctime>
#include <map>

class BitcoinExchange
{
	private:
		std::map<Date, float> m_quotes;

	public:
		BitcoinExchange(std::string filename);
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange() = default;

		void printQuotes() const;
		void simulateAccount(std::string accountFilename) const;
		float getClosestPrice(Date date) const;
};
