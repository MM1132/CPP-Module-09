#include "BitcoinExchange.hpp"
#include "utils.hpp"

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <regex>
#include <exception>

BitcoinExchange::BitcoinExchange(std::string databaseFilename):
	m_databaseFilename(databaseFilename)
{
	std::ifstream inputFile(m_databaseFilename);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open the database file" << std::endl;
		return ;
	}

	std::regex dataLineRegex("([0-9]{4})-([0-9]{2})-([0-9]{2}),(\\d+.?\\d*)");

	std::string line;
	while (getline(inputFile, line))
	{
		std::smatch match;
		if (std::regex_search(line, match, dataLineRegex))
		{
			if (match.size() != 5)
				continue;
			
			try
			{
				int year = std::stoi(match[1]);
				int month = std::stoi(match[2]);
				int day = std::stoi(match[3]);
				Date date(year, month, day);

				float value = std::stof(match[4]);
				if (value < 0)
					throw "Price cannot be negative";
				
				this->m_quotes.push_back(Quote({ date, value }));
			}
			catch (const std::exception& e) {}
		}
	}

	inputFile.close();
}

void BitcoinExchange::printQuotes() const
{
	for (const auto& quote : this->m_quotes)
	{
		std::cout << "On date ";
		quote.date.print();
		std::cout << " the price was " << quote.price << std::endl;
	}
}

void BitcoinExchange::simulateAccount(std::string accountFilename) const
{
	std::ifstream accountFile(accountFilename);
	if (!accountFile.is_open())
	{
		std::cout << "Failed to open account file, simulation will not fun" << std::endl;
		return ;
	}

	std::regex accountLineRegex("([0-9]{4})-([0-9]{2})-([0-9]{2}) | (\\d+.?\\d*)");
	std::string line;
	while (getline(accountFile, line))
	{

	}
	accountFile.close();
};

float BitcoinExchange::getClosestPrice(Date date)
{
	
}
