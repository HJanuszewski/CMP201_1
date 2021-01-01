#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <unordered_map>
#include <string>
#include <cmath>
#include <sstream>


unsigned short FindInLine(int hash_substring,int hash_content, std::string content, std::string substring)
{

	if (content.length() < substring.length())
	{
		return 0;
	}

	// hash = (ascii value)* (94)^(.length() - 1 ) + (next ascii value) * (94)^(.length() -2 ) + ...
	// ascii value of the character we're supposed to hash
	// 94 because there's that many printable ascii characters that can appear
	 int hash_checked = hash_content;
	
	unsigned short count = 0;
	unsigned long long p = 1;

	
	
	std::cout << "substring hash: "<< hash_substring << std::endl << "checked hash: " << hash_checked << std::endl << std::endl;

	for (short i = 0; i < content.length() - substring.length(); i++)
	{
		if (hash_checked == hash_substring) // if the hashes match
		{
			std::cout << "OY THERE MIGHT BE SOMETHING HERE " << i << std::endl;
			short j;// will be checked after the loop is finished, but is not needed elsewhere in the function
			for ( j = 0; j < substring.length(); j++)
			{
				if (substring[j] != content[i + j]) break; //if a letter from the substring does not match a letter from the main string, break
			}
			if (j == substring.length())  // if the loop above did not break (if all characters matched)
			{ 
				count++; 
				std::cout << "Found something boss" << std::endl;
			}
		}
		

			//UNDER\OVERFLOWS THE HELL OUT OF THIS HASH, I WANT TO GIVE UP AND GO CURL UP IN A BALL IN THE CORNER
			//p = (p * 53) % 7919;
			std::cout << "Subtracting letter: " << content[i] << std::endl;
			hash_checked = 53 * (hash_checked - (int)content[i] * p + (int)content[i + substring.length()]) % 7919;
			std::cout << "Adding letter: " << content[ i + substring.length()] << std::endl;
			
		

			if (hash_checked <= 0) hash_checked += 7919;
			
	
			//hash_checked -= (content[i] * (pow(53, substring.length()-1))) ;
			//hash_checked = hash_checked * 53;
			//hash_checked += (content[i+substring.length()] * (pow(53,0))) ;
		//hash_checked = (hash_checked - (content[i] * (94 ^ (substring.length() - i)))) * 94 + content[i + substring.length()] % 7919;
			 // subtract the leftmost letter from the hash, add the next letter from the right to the hash
		
		std::cout << "substring hash: " << hash_substring << std::endl << "checked hash: " << hash_checked << std::endl << std::endl;

	}
	return count;
	//im too tired to work on this longer today I think. Continue by implementing a function or sth to change the value of the hash that is to be examined. Make sure that the hashing function was in fact properly implemented and does not just spew out random garbage (does it even compile lmao)


}



unsigned short subStringCount(std::string fileName, std::string subString )
{
	unsigned short count = 0; // number of times the substring we're looking for has appeared in the text
	unsigned short lastcount = 0;
	int iterator = 0;
	short substring_hash = 0;
	short content_hash = 0;
	unsigned long long p = 1;
	std::stringstream stream;
	std::fstream file;
	std::string line = ""; //since the string we're looking for is a word, and book is formatted so that words are never split between two lines, we can treat each line separately.
	// IF that was not the case, we could ensure the substring is not missed by accident because of this by saving the last part of each line and considering it together with the beginning of the next one

	file.open(fileName, std::ios::in);

	while (file.good()) // while we have not reached the end of the file 
	{
		lastcount = 0;
		
		std::getline(file, line); //get the next line of text
		stream << line;
		
		iterator++;

	}
	file.close();
	for (iterator;iterator>0;iterator--)
	{
		std::getline(stream,line);
		for (int i = 1; i <= subString.length(); i++)
		{
			p = (p * 53) % 7919;
			substring_hash = (substring_hash * p + (short)subString[i - 1]) % 7919;
			content_hash = (content_hash * p + (short)line[i - 1]) % 7919;
		}
		lastcount = FindInLine(substring_hash, content_hash, line, subString); //check how many times substring appears in it and increment the count by that amount 

	}
	
	count += lastcount;
	return count;
}



int main()
{
	//TODO: understand and implement the good suffix rule
	//TODO: find in the lectures all of the methods we're supposed to measure the performance of out programs and start to think about implementing them
	std::cout << "count of substrings found: " <<subStringCount("test.txt", "Raskolnikov") ;
	
	return 0;

}
/*
Raskolnikov


*/