#include "PmergeMe.hpp"

#include <iostream>
#include <list>
#include <deque>
#include <chrono>

// using std::chrono::nanoseconds;
// using std::chrono::duration_cast;
using std::chrono::system_clock;

auto get_time()
{
	return system_clock::now().time_since_epoch().count();
}

int main(int ac, char** av)
{
	std::list<int> list;
	long long ns_before, ns_after;

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
	ns_before = get_time();
	auto sortedDeque = mergeInsertSort(deque);
	ns_after = get_time();
	// std::cout << "std:deque after sorting ->" << std::endl;
	// printNumbers(sortedDeque);
	std::cout << "Deque took time: " << ns_after - ns_before << std::endl;
	std::cout << "Is deque sorted: " << std::is_sorted(sortedDeque.begin(), sortedDeque.end()) << std::endl;

	std::cout << std::endl;

	// std::cout << "std::list, before sorting ->" << std::endl;
	// printNumbers(list);
	ns_before = get_time();
	auto sortedList = mergeInsertSort(list);
	ns_after = get_time();
	// std::cout << "std:list after sorting ->" << std::endl;
	// printNumbers(sortedList);
	std::cout << "List took time: " << ns_after - ns_before << std::endl;
	std::cout << "Is list sorted: " << std::is_sorted(sortedList.begin(), sortedList.end()) << std::endl;
	
	return 0;
}
