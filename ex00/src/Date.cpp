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
	const int allowedDays = m_daysInMonth[m_month - 1] + (m_month == 2 && isLeapYear());

	if (m_year < 1970 || m_year > 2100)
		return false;
	if (m_month < 1 || m_month > 12)
		return false;
	if (m_day < 1 || m_day > allowedDays)
		return false;
	
	return true;
}

bool Date::isLeapYear() const
{
	return (m_year % 4 == 0 && (m_year % 100 != 0 || m_year % 400 == 0));
}
