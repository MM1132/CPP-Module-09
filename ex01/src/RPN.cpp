#include "RPN.hpp"
#include <stack>
#include <regex>
#include <iostream>

int reversePolishNotation(std::string input)
{
	// Creating this regex took 1 hour and 40 minutes
	std::regex validInputRegex("^(?:\\d (?! )(?:[\\d\\-+*\\/](?![\\-+*\\/\\d])| (?! |$))+)|\\d$");

	std::smatch match;
	if (std::regex_match(input, match, validInputRegex))
	{
		std::stack<int> theStack;

		for (char c : match[0].str())
		{
			if (std::isdigit(c))
				theStack.push(c - '0');
			else
			{
				int result;
				switch (c)
				{
					case '+':
						if (theStack.size() < 2)
							throw "The stack did not have enough numbers for the operation";
						result = theStack.top();
						theStack.pop();
						result += theStack.top();
						theStack.top() = result;
						break;
					case '-':
						if (theStack.size() < 2)
							throw "The stack did not have enough numbers for the operation";
						result = theStack.top();
						theStack.pop();
						result = theStack.top() - result;
						theStack.top() = result;
						break;
					case '*':
						if (theStack.size() < 2)
							throw "The stack did not have enough numbers for the operation";
						result = theStack.top();
						theStack.pop();
						result = theStack.top() * result;
						theStack.top() = result;
						break;
					case '/':
						if (theStack.size() < 2)
							throw "The stack did not have enough numbers for the operation";
						result = theStack.top();
						if (result == 0)
							throw "Cannot divide by zero!";
						theStack.pop();
						result = theStack.top() / result;
						theStack.top() = result;
						break;
				}
			}
		}
		// It only returns if we have exactly one thing left
		if (theStack.size() == 1)
		{
			return theStack.top();
		}
	}
	else
	{
		throw "The awesome regex did not match";
	}
	throw "The expression was fauly. Please check it!";
}
