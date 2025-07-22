#include "Date.hpp"

#include <iostream>
#include <ctime>
#include <exception>

Date::Date(int year, int month, int day):
	m_year(year), m_month(month), m_day(day)
{
	if (!isValid())
		throw InvalidDateException();
}

Date::Date(const Date& other):
	m_year(other.m_year), m_month(other.m_month), m_day(other.m_day)
{}

Date& Date::operator=(const Date& other)
{
	if (this != &other)
	{
		this->m_year = other.m_year;
		this->m_month = other.m_month;
		this->m_day = other.m_day;
	}
	return *this;
}

bool Date::operator==(const Date& other) const
{
	return (
		m_year == other.m_month && 
		m_month == other.m_month &&
		m_day == other.m_day);
}

bool Date::operator<(const Date& other) const
{
	if (m_year != other.m_year)
		return m_year < other.m_year;

	if (m_month != other.m_month)
		return m_month < other.m_month;
	
	return m_day < other.m_day;
}

bool Date::operator>(const Date& other) const
{
	return other < *this;
}

void Date::print() const
{
	std::cout << m_year;
	std::cout << "-";
	if (m_month < 10)
		std::cout << "0";
	std::cout << m_month;
	std::cout << "-";
	if (m_day < 10)
		std::cout << "0";
	std::cout << m_day;
	std::cout << std::flush;
}

bool Date::isValid() const
{
	struct tm date;

	date.tm_year = m_year - 1900;
	date.tm_mon = m_month - 1;
	date.tm_mday = m_day;
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
		date.tm_year != m_year - 1900 ||
		date.tm_mon != m_month - 1 ||
		date.tm_mday != m_day
	)
		return false;
	
	return true;
}
