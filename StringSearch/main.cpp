#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>
#include <chrono>

using the_clock = std::chrono::steady_clock;


unsigned short BMFindInLine(std::string content, std::string subString)
{
	int scount = 0; // the count of the substring appearances
	int b = 0; // a loop iterator that needs to be checked in a broader scope 
	int bad_char_a = 0;
	 
	

	//Raskolnikov - this problem's target substgring is  composed from letters R a s k o l n i v - letters are case sensitive, but since it's a name we shouldn't expect any weird capitalizations of the word.
	std::set<char> letters; // this set will be used to check if a letter is present in the substring
	for (int i = 0; i < subString.length(); i++)
	{
		letters.insert(subString[i]);
	}


	std::unordered_map<char,int> map;// a pseudo-hashtable, uses ascii value of a letter mapped to amount of letters the algorithm can jump when it is found (and is not matching) during the check) 
	// a substring-specific map would be easy to set by initialising fields for all letters to skip the length of the substring and overwrite letters of interest. However, even though more complex, the implementation below is generic and should work on anysubstring provided
	for (int i = 32; i < 126; i++) //all standard printable ASCII codes, that we'd expect to appear in the text
	{	
		if (letters.count((char)i)) //if the letter we're currently assigning is persent in the substring
		{
			int distance = 1;
			for (int j = subString.length()-1; j >0; j--)
			{
				if (subString[j] == (char)i)
				{
					break;
				}
				else distance++;
			}
			map[(char)i] = distance;
		}
		else map[i] = subString.length() ; // if it's not, we should skip to the end, since there's no ppossibility of the substring appearing there
	}


	
	
	if (content.length() < subString.length()) return 0; // the word can not be present in a line, that is shorter than the word itself

	
	for (int i = 0; i <= content.size() - subString.size() -1; i++) // in regular circumstances, nested for loops would make the efficiency a lot worse than what this algorithm can achieve, however, when running those loops, we will be modifying values of the iterators, jumping forward whenever we can.
	{	
		bad_char_a = i;

		
		for ( b = 0; b < subString.size() -1 ; b++)
		{
			
			
			
			if (subString[subString.size() - 1 - b ] != content[subString.size() - b + i - 1])
			{
				if (content.length() == subString.length()) return scount; //if the first letter is not matching AND the text we're looking for the substring in is the same length as the substring return from the function, there's no skipping to be done in this line

				else break; // else, break out of this loop, preserving the value of b that can be uesd to calculate the offset we'll need
			}
		}
		if (b != subString.size() - 1) // if the previous loop had a break happen (if there was a character that was not matching with the substring)
		{
		

			if (letters.count(content[subString.size() - b + i - 1]) == 0 ) // when the letter that is not matching with the substring is not present in the substring at all
			{

				if ((i + subString.size() - 2) <= content.size() - subString.size()) // ensuring that we will not go out of bounds
					bad_char_a += subString.size() - 2;
				else
					bad_char_a = content.size() - subString.size(); // if we were to go out of bonds, we should stop at the last possible check instead
			}
			else
			{
				
				bad_char_a += map[(int)content[subString.size() - b + i]] - 1;
				
			}
			
			
			continue;
		}
		else // getting to this section means that the loop has finished without breaking. This should indicate that all letters from the pattern matched, meaning that the substring was found
		{
			scount++;
			
			
		}

	} 	
	
	return scount;
}


unsigned short subStringCount(std::string fileName, std::string subString )
{
	
	std::fstream file;
	std::string line = ""; 
	std::stringstream temp;
	int count = 0;
	file.open(fileName, std::ios::in);

	while (file.good()) // while we have not reached the end of the file 
	{
		
		
		std::getline(file, line); //get the next line of text
		temp << line;
		
	}
	file.close();
	line = temp.str();
	the_clock::time_point pointA = the_clock::now();
	 count = BMFindInLine(line, subString); //check how many times substring appears in it and increment the count by that amount 
	 the_clock::time_point pointB = the_clock::now();
	 auto duration = std::chrono::duration_cast<std::chrono::microseconds>(pointB - pointA).count();
	 std::cout << "It took: " << 0.000001 * duration << " seconds"<< std::endl;
	 return count;
}



int main()
{
	std::cout << "count of substrings found: " <<subStringCount("Full.txt", "Raskolnikov");
	
	return 0;

}
