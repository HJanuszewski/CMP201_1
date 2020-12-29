#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <unordered_map>
#include <string>
#include <cmath>


unsigned short FindInLine(std::string content, std::string substring)
{

	if (content.length() < substring.length())
	{
		return 0;
	}

	// hash = (ascii value)* (94)^(.length() - 1 ) + (next ascii value) * (94)^(.length() -2 ) + ...
	// ascii value of the character we're supposed to hash
	// 94 because there's that many printable ascii characters that can appear
	unsigned int hash_substring = 0;
	unsigned int hash_checked = 0;
	unsigned int move = 0;
	for (int i = substring.length() -1 ; i >= 0 ; i--)
	{
		hash_substring += (substring[i] * (94 ^ substring.length() - i) % 1009);
	}


	std::cout << hash_substring << std::endl;
	
	for (int i = 0+move; i < substring.length() +move; i++)//first hash i guess?
	{
		hash_checked += (content[i] * (94 ^ (substring.length() - i)) % 1009);
	}
	for (move = 0; move < content.length() - substring.length(); move++)
	{
		
	}
	return hash_substring;
	//im too tired to work on this longer today I think. Continue by implementing a function or sth to change the value of the hash that is to be examined. Make sure that the hashing function was in fact properly implemented and does not just spew out random garbage (does it even compile lmao)


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
		
		std::getline(file, line); //get the next line of text
		
		lastcount=FindInLine(line, subString); //check how many times substring appears in it and increment the count by that amount 
		
		count += lastcount;
		
	}

	file.close();
	return count;
}



int main()
{
	//TODO: understand and implement the good suffix rule
	//TODO: find in the lectures all of the methods we're supposed to measure the performance of out programs and start to think about implementing them
	std::cout << "count of substrings found: " <<subStringCount("test.txt", "piesek") ;
	
	return 0;

}
/*
Raskolnikov


*/