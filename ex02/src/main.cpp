#include "PmergeMe.hpp"

#include <iostream>
#include <list>
#include <deque>
#include <chrono>

template<typename CONTAINER>
void printInfo(CONTAINER before, CONTAINER after, double listTime, double dequeTime)
{
	/*
		Before: 3 5 9 7 4
		After: 3 4 5 7 9
		Time to process a range of 5 elements with std::[..] : 0.00031 us
		Time to process a range of 5 elements with std::[..] : 0.00014 us
	*/
	std::cout << "Before: ";
	printNumbers(before);
	std::cout << "After: ";
	printNumbers(after);
	std::cout << "Time to process a range of " << after.size() << " elements with std::list : " << listTime << " us" << std::endl;
	std::cout << "Time to process a range of " << after.size() << " elements with std::deque : " << dequeTime << " us" << std::endl;
}

int main(int ac, char** av)
{
	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::microseconds;

	std::list<int> list;

	try
	{
		read_inputs(list, ac, av);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Could not convert numbers into int" << std::endl;
		return 1;
	}

	std::deque<int> deque(list.begin(), list.end());
	// std::cout << "std::deque, before sorting ->" << std::endl;
	// printNumbers(deque);
	auto t1 = high_resolution_clock::now();
	auto sortedDeque = mergeInsertSort<std::deque<int>>(deque);
	auto t2 = high_resolution_clock::now();
	duration<double, std::milli> dequeTime = t2 - t1;
	// std::cout << "std:deque after sorting ->" << std::endl;
	// printNumbers(sortedDeque);
	// std::cout << "Deque took time: " << ns_after - ns_before << std::endl;
	// std::cout << "Is deque sorted: " << std::is_sorted(sortedDeque.begin(), sortedDeque.end()) << std::endl;

	// std::cout << std::endl;

	// std::cout << "std::list, before sorting ->" << std::endl;
	// printNumbers(list);
	t1 = high_resolution_clock::now();
	auto sortedList = mergeInsertSort<std::list<int>>(list);
	t2 = high_resolution_clock::now();
	duration<double, std::milli> listTime = t2 - t1;
	// std::cout << "std:list after sorting ->" << std::endl;
	// printNumbers(sortedList);
	// std::cout << "List took time: " << ns_after - ns_before << std::endl;
	// std::cout << "Is list sorted: " << std::is_sorted(sortedList.begin(), sortedList.end()) << std::endl;
	
	printInfo(list, sortedList, listTime.count(), dequeTime.count());

	return 0;
}
