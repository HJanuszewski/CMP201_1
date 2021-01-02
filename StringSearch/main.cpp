#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <unordered_map>
#include <string>
#include <cmath>
#include <sstream>


unsigned long long p = 1/94; // a setup so we won't have to either hardcode the value of p that should be dependant on the lenght of the substring, or make another loop, that'd only serve to set p. Instead we start p at a value that appears weird, but will account for later loop making one to many p=p*53%1009 operations.


unsigned short rabinKarp(short sub_hash,short content_hash,std::string substring, std::string content)
{
	
	unsigned short count = 0;
	for (int i = 0; i < content.length() - substring.length(); i++)
	{
		//std::cout << sub_hash << " : " << content_hash << std::endl;
		if (sub_hash == content_hash) // the hashes match
		{
			
			int j = 0;// this variable is not defined in the loop, as we need to check it's value to determine if the loop broke or not
			for (; j < substring.length(); j++)
			{//	if the letters don't match - break out of this loop
				//std::cout << substring[j] << " : " << content[j + i] << std::endl;
				if (substring[j] != content[j + i])
				{
					//std::cout << "I'm outta here!" << std::endl;
					break;
				}
			}
		  //if the previous loop finished without breaking - increment count, else - keep going 
			if (j == substring.length() )
			{
				
				count++;
			}
			else continue;
		}
		else
		{
			content_hash = ((content_hash - ((short)content[i] * p)) * 94 + content[i + substring.length()]) % 1009;
			if (content_hash < 0) content_hash += 1009;
		}

	}


	return count;
}


unsigned short subStringCount(std::string fileName, std::string subString )
{
	
	int iterator = 0;
	unsigned short count = 0; // number of times the substring we're looking for has appeared in the text
	short substring_hash = 0;
	short content_hash = 0;
	
	std::stringstream stream; // a stringstream that will hold the entire text 
	std::fstream file; // file that the main text will be loaded from
	std::string line = ""; //since the string we're looking for is a word, and book is formatted so that words are never split between two lines, we can treat each line separately.
	// IF that was not the case, we could ensure the substring is not missed by accident because of this by saving the last part of each line and considering it together with the beginning of the next one

	file.open(fileName, std::ios::in);

	while (file.good()) // while we have not reached the end of the file 
	{

		std::getline(file, line); //get the next line of text
		stream << line; // hold it in a stringstream temporarily, so we can close the file and have entire content in memory already

	}
	file.close();

		
		for (int i = 1; i <= subString.length(); i++)
		{
			p = (p * 94) % 1009;
			substring_hash = (substring_hash * 94 + (short)subString[i - 1]) % 1009;
			content_hash = (content_hash * 94 + (short)stream.str()[i - 1]) % 1009;
			
		}
		count += rabinKarp(substring_hash,content_hash,subString,stream.str()); //find all occurences of the substring within the line
		
	
	return count;
}



int main()
{
	std::cout << "count of substrings found: " <<subStringCount("test.txt", "Raskolnikov") ;
	
	return 0;

}
/*
Raskolnikov


*/