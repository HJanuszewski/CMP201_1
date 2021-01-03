#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

using the_clock = std::chrono::steady_clock;

unsigned int result[100];
int a = 0;

int pown = 1/97; // a setup so we won't have to either hardcode the value of p that should be dependant on the lenght of the substring, or make another loop, that'd only serve to set p. Instead we start p at a value that appears weird, but will account for later loop making one to many p=p*53%1009 operations.
//since calculations are done wiht modulo, there is no risk of overflowing int when multiplying by 97 many times

unsigned int rabinKarp(int &sub_hash,int &content_hash,std::string &substring, std::string content)
{

	
	unsigned int count = 0;
	for (int i = 0; i <= content.length() - substring.length(); i++)
	{
		
		if (sub_hash == content_hash) // the hashes match
		{
			
			int j = 0;// this variable is not defined in the loop, as we need to check it's value to determine if the loop broke or not
			for (; j <substring.length(); j++)
			{//	if the letters don't match - break out of this loop
				//std::cout << substring[j] << " : " << content[j + i] << std::endl;
				if (substring[j] != content[i+j])
				{
					
					break;
				}
			}
		  //if the previous loop finished without breaking - increment count, else - keep going 
			if (j == substring.length() )
			{
				//we have found a match, increment count
				count++;
			}
			else continue;
		}
		else
		{// hash		=  ((hash - (value of leftmost letter* pown)) * 97 + value of next letter from the right) % 1009
			content_hash = ((content_hash - ((int)content[i] * pown)) * 97 + content[i + substring.length()]) % 1009;
			if (content_hash < 0) content_hash += 1009;// in case we get to negatives, we add the prime number to be back in the positives, with the same modulo value 
		}

	}


	return count;
}


unsigned int subStringCount(std::string fileName, std::string subString )
{
	

	unsigned int count = 0; // number of times the substring we're looking for has appeared in the text. can't possibly need to be a negative value
	int substring_hash = 0;
	int content_hash   = 0;
	
	std::stringstream stream; // a stringstream that will hold the entire text 
	std::fstream file; // file that the main text will be loaded from
	std::string line = ""; 

	file.open(fileName, std::ios::in);

	while (file.good()) // while we have not reached the end of the file 
	{

		std::getline(file, line); //get the next line of text
		
		stream << line << std::endl; // hold it in a stringstream temporarily, so we can close the file and have entire content in memory already

	}
	file.close();
	
	line = stream.str();
		the_clock::time_point pointA = the_clock::now();
		for (int i = 1; i <= subString.length(); i++)
		{
			pown = (pown * 97) % 1009;
			substring_hash = (substring_hash * 97 + (int)subString[i - 1]) % 1009;
			content_hash = (content_hash * 97 + (int)line[i - 1]) % 1009;
			
		}
		count += rabinKarp(substring_hash,content_hash,subString,line); //find all occurences of the substring within the line
		
		the_clock::time_point pointB = the_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(pointB - pointA).count();
		result[a] = duration;  a++;
		//std::cout << "It took: " <<duration << " microseconds." << std::endl;
	return count;
}



int main()
{
	int results[100];
	for (int i = 0; i < 100; i++)
	{
		results[i] = subStringCount("full.txt", "Raskolnikov");
	}
	for (int i = 0; i < 100; i++)
	{
		std::cout << "took: " <<result[i] <<" milliseconds" << std::endl;
	}return 0;

}
