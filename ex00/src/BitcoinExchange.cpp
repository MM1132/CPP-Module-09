#include "BitcoinExchange.hpp"
#include "Date.hpp"

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <regex>
#include <exception>

BitcoinExchange::BitcoinExchange(std::string databaseFilename)
{
	std::ifstream inputFile(databaseFilename);
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
				
				this->m_quotes.insert_or_assign(date, value);
			}
			catch (const std::exception& e) {}
		}
	}

	inputFile.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other):
	m_quotes(other.m_quotes)
{}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		this->m_quotes = other.m_quotes;
	}
	return *this;
}

void BitcoinExchange::printQuotes() const
{
	for (const auto& quote : this->m_quotes)
	{
		std::cout << "On date ";
		quote.first.print();
		std::cout << " the price was " << quote.second << std::endl;
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

	std::regex accountLineRegex("([0-9]{4})-([0-9]{2})-([0-9]{2})\\s[|]\\s(-*\\d+.?\\d*)");
	std::string line;

	for (unsigned long lineNumber = 1; getline(accountFile, line); lineNumber++)
	{
		// Skip over the first line
		if (lineNumber == 1)
			continue ;

		std::smatch match;
		if (std::regex_match(line, match, accountLineRegex))
		{
			if (match.size() != 5)
				continue;
			
			try
			{
				Date date(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]));

				float amount = std::stof(match[4]);
				if (amount > 1000)
					throw std::runtime_error("too large a number");
				else if (amount < 0)
					throw std::runtime_error("bitcoin amount cannot be negative");

				float price = getClosestPrice(date);
				
				date.print();
				std::cout << " => " << amount << " = " << amount * price << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cout << "Error in line " << lineNumber << ": " << e.what() << std::endl;
			}
		}
		else
		{
			std::cout << "Error in line " << lineNumber << ": wrong format => '" << line << "'" << std::endl;
		}
	}
	accountFile.close();
};

float BitcoinExchange::getClosestPrice(Date date) const
{
	auto match = this->m_quotes.upper_bound(date);
	if (match == this->m_quotes.begin())
		throw "Price not found from database";
	return (*--match).second;
}
