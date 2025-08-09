## Module 09: STL Containers

### Ex00: BitcoinExchange
In this exercise, we read in a database of bitcoin values on various different dates. The program is run by giving another file as input, with different amounts of bitcoin the user had on various dates. We must display in terminal the amount of value they have had on vairous dates. 

My implementation uses the regex capture groups to extract the data out of the files. The error messages the subject proposes seemed weird to me, so I improved them with my own custom logic, to give more info the user about in which line in the file they have what error. 
Custom parser for validating dates in the custom Date class. I also found a regex on the internet to do this super easily, but I couldn't entirely understand it so I didn't use it. 
