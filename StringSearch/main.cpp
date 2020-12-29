#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <unordered_map>
#include <string>
#include <cmath>


unsigned short FindInLine(unsigned int hash_substring, std::string content, std::string substring)
{

	if (content.length() < substring.length())
	{
		return 0;
	}

	// hash = (ascii value)* (94)^(.length() - 1 ) + (next ascii value) * (94)^(.length() -2 ) + ...
	// ascii value of the character we're supposed to hash
	// 94 because there's that many printable ascii characters that can appear
	unsigned int hash_checked = 0;
	
	unsigned short count = 0;


	
	
	for (short i = 0; i < substring.length(); i++)//first hash i guess?
	{
		hash_checked += (content[i] * (94 ^ (substring.length() - i)) % 1009);
	}
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
			hash_checked = (hash_checked - (content[i] * (94 ^ (substring.length() - i)))) * 94 + content[i + substring.length()] % 1009;
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
	unsigned int hash = 0;
	std::fstream file;
	std::string line = ""; //since the string we're looking for is a word, and book is formatted so that words are never split between two lines, we can treat each line separately.
	// IF that was not the case, we could ensure the substring is not missed by accident because of this by saving the last part of each line and considering it together with the beginning of the next one

	for (int i = subString.length() - 1; i >= 0; i--)
	{
		hash += (subString[i] * (94 ^ subString.length() - i) % 1009);
	}

	file.open(fileName, std::ios::in);

	while (file.good()) // while we have not reached the end of the file 
	{
		lastcount = 0;
		
		std::getline(file, line); //get the next line of text
		
		lastcount=FindInLine(hash,line, subString); //check how many times substring appears in it and increment the count by that amount 
		
		count += lastcount;
		
	}

	file.close();
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