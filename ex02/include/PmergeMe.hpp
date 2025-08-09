#pragma once

#include <list>
#include <string>

void read_inputs(std::list<int>& list, int ac, char** av);

template<typename CONTAINER>
CONTAINER mergeInsertSort(CONTAINER list);

template<typename CONTAINER>
void printNumbers(CONTAINER& list);

template<typename CONTAINER>
void binaryInsert(CONTAINER& sortedList, int number);

#include "PmergeMe.tpp"
