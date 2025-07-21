#pragma once

#include <iostream>
#include <ctime>
#include <exception>

inline bool isDateValid(int year, int month, int day)
{
	struct tm date;

	date.tm_year = year - 1900;
	date.tm_mon = month - 1;
	date.tm_mday = day;
	date.tm_hour = 0;
	date.tm_min = 0;
	date.tm_sec = 0;
	date.tm_isdst = 0;

	time_t time = mktime(&date);

	if (time == -1)
	{
		return false;
	}
		
	if (
		date.tm_year != year - 1900 ||
		date.tm_mon != month - 1 ||
		date.tm_mday != day
	)
		return false;
	
	return true;
}

inline void printDate(int year, int month, int day)
{
	std::cout << year << "-" << month << "-" << day << std::flush;
}

struct InvalidDateException : public std::exception
{
	virtual const char* what() const noexcept override
	{
		return "The date could not be parsed";
	}
};

class Date
{
	private:
		int m_year, m_month, m_day;

	public:
		Date(int year, int month, int day):
			m_year(year), m_month(month), m_day(day)
		{
			if (!isDateValid(m_year, m_month, m_day))
				throw InvalidDateException();
		}

		void print() const
		{
			printDate(m_year, m_month, m_day);
		}
};
