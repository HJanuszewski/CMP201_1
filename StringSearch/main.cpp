#include <iostream>
#include <fstream>




unsigned short BMFindInLine(std::string content, std::string subString)
{
	unsigned short clength = content.length(); // lengths of boch content and substring will never be negative; it is highly unlikely that a single line in a book will have more letters than unsigned short can hold
	unsigned short slength = subString.length();
	unsigned short count;
	unsigned short a = 1; // while usually those should be named i and j, I've changed them to a and b for my own convenience, since with traditional naming, I sometimes forgot that they were not local to the loops they control
	unsigned short b = 0;
	//TODO: search throught the lectures and implement a map for letters that are present in the substring that can be compared when a miss is detected

	for (a = 0; a < content.size() - subString.size(); a++)
	{
		for ( b = 0; b < subString.size(); b++)
		{
			if (subString[subString.size() - 1 - b + a] != content[subString.size() - b + a - 1])
			{
				break;
			}
		}
		if (j != subString.size() - 1) // if the previous loop had a break happen (if there was a character that was not matching with the substring)
		{
			// we should do a fancy jump to a later part of the string using the variable a 

		}


	}
	// last letter of content is    content[content.size()-1]
	return 1;
}


unsigned short subStringCountBM(std::string fileName, std::string subString )
{
	unsigned short count = 0; // number of times the substring we're looking for has appeared in the text
	std::fstream file;
	std::string line = ""; //since the string we're looking for is a word, and book is formatted so that words are never split between two lines, we can treat each line separately.
	// IF that was not the case, we could ensure the substring is not missed by accident because of this by saving the last part of each line and considering it together with the beginning of the next one

	file.open(fileName, std::ios::in);

	while (file.good()) // while we have not reached the end of the file 
	{
		file >> line; //get the next line of text
		
		count+=BMFindInLine(line, subString); //check how many times substring appears in it and increment the count by that amount 
		
	}

	file.close();
	return count;
}



int main()
{
	subStringCountBM("test.txt", "asd");
	return 0;

}
