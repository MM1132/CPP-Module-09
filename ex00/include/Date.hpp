#pragma once

#include <iostream>
#include <ctime>
#include <exception>

class Date
{
	private:
		int m_year, m_month, m_day;

	public:
		Date(int year, int month, int day);
		Date(const Date& other);
		Date& operator=(const Date& other);
		~Date() = default;

		// Needed since we are using the Date as key in the map
		bool operator==(const Date& other) const;
		bool operator<(const Date& other) const;
		bool operator>(const Date& other) const;

		struct InvalidDateException : public std::exception
		{
			virtual const char* what() const noexcept override
			{
				return "The date could not be parsed";
			}
		};

		void print() const;
		bool isValid() const;
};
