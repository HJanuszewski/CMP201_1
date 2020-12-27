#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <unordered_map>
#include <string>


unsigned short FindInLine(std::string content, std::string substring)
{


}

unsigned short subStringCount(std::string fileName, std::string subString )
{
	unsigned short count = 0; // number of times the substring we're looking for has appeared in the text
	unsigned short lastcount = 0;
	std::fstream file;
	std::string line = ""; //since the string we're looking for is a word, and book is formatted so that words are never split between two lines, we can treat each line separately.
	// IF that was not the case, we could ensure the substring is not missed by accident because of this by saving the last part of each line and considering it together with the beginning of the next one


	file.open(fileName, std::ios::in);

	while (file.good()) // while we have not reached the end of the file 
	{
		lastcount = 0;
		//std::cout << "NEW LINE !! " << "Count is: " << count << std::endl;
		std::getline(file, line); //get the next line of text
		//std::cout << line << std::endl;
		//std::cout << "So far there were " << count << " instances. in the previous line, there were " << lastcount << std::endl;

		lastcount=FindInLine(line, subString); //check how many times substring appears in it and increment the count by that amount 
		//std::cout << "I HAVE A " << count << " I HAVE " << lastcount;
		count += lastcount;
		//std::cout << " UGH, " << count << std::endl;
	}

	file.close();
	return count;
}



int main()
{
	//TODO: understand and implement the good suffix rule
	//TODO: find in the lectures all of the methods we're supposed to measure the performance of out programs and start to think about implementing them
	std::cout << "count of substrings found: " <<subStringCount("test.txt", "Raskolnikov");
	
	return 0;

}
/*
Raskolnikov


*/