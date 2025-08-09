#include "PmergeMe.hpp"

#include <iostream>

template<typename CONTAINER>
void printNumbers(CONTAINER& list)
{
	for (auto v : list)
	{
		std::cout << v << ", ";
	}
	std::cout << std::endl;
}

void read_inputs(std::list<int>& list, int ac, char** av)
{
	if (ac == 1)
		throw std::runtime_error("You must provide at least 1 number as input");
	for (int i = 1; i < ac; i++)
	{
		int convertedNumber = std::stoi(av[i]);
		if (convertedNumber <= 0)
			throw std::runtime_error("All input numbers must be valid positive numbers");
		list.push_back(convertedNumber);
	}
}

template<typename CONTAINER>
typename CONTAINER::iterator binaryInsertRecursion(typename CONTAINER::iterator first, typename CONTAINER::iterator second, int number)
{
	ptrdiff_t distance = std::distance(first, second);

	if (distance <= 1)
	{
		if (number < *first)
			return first;
		else
			return second;
	}

	auto newIterator = first;
	std::advance(newIterator, distance / 2);
	if (number < *newIterator)
	{
		std::advance(second, distance / -2);
	}
	else
	{
		std::advance(first, distance / 2);
	}

	return binaryInsertRecursion<CONTAINER>(first, second, number);
}

template<typename CONTAINER>
void binaryInsert(CONTAINER& sortedList, int number)
{
	typename CONTAINER::iterator insertPosition = binaryInsertRecursion<CONTAINER>(sortedList.begin(), sortedList.end(), number);
	sortedList.insert(insertPosition, number);
}

template<typename CONTAINER>
CONTAINER mergeInsertSort(CONTAINER list)
{
	bool sorted = std::is_sorted(list.begin(), list.end());
	if (sorted)
		return list;

	size_t size = list.size();
	CONTAINER smallerNumbers;
	CONTAINER biggerNumbers;

	// Loop through and flip numbers
	int loopUntil = size - size % 2 - 2;
	// std::cout << "loopUntil: " << loopUntil << std::endl;

	int index = 0;
	for (auto it = list.begin(); index <= loopUntil; ++++it, index += 2)
	{
		auto next = std::next(it);
		if (*next < *it)
		{
			// std::cout << "Swapping " << *it << " and " << *next << std::endl;
			std::swap(*it, *next);
		}
		smallerNumbers.push_back(*it);
		biggerNumbers.push_back(*next);
		// std::cout << *it << " and " << *next << std::endl;
	}

	if (biggerNumbers.size() > 1)
		biggerNumbers = mergeInsertSort(biggerNumbers);
	
	if (size % 2)
		smallerNumbers.push_back(list.back());

	// std::cout << "smaller numbers: " << std::endl;
	// printNumbers(smallerNumbers);
	// std::cout << "bigger numbers: " << std::endl;
	// printNumbers(biggerNumbers);
	// return list;

	// Binary insert all the numbers into the first list
	for (auto v : smallerNumbers)
	{
		// std::cout << "Before inserting:" << std::endl;
		// printNumbers(biggerNumbers);
		binaryInsert<CONTAINER>(biggerNumbers, v);
		// std::cout << "After inserting " << v << ":" << std::endl;
		// printNumbers(biggerNumbers);
	}

	return biggerNumbers;

	// Check if the size of odd, and if it is, insert the last number too
}
