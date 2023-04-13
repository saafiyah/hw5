#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
	set<string> retval; //set of strings with valid words 
	if(in.find('-') == string::npos) // if in contains no dashes 
	{
		if(dict.find(in) != dict.end()) // if in is in dicitionary
		{
			retval.insert(in); // add to string set
		}
		return retval; 
	}
	if(!floating.empty()) // if not empty 
	{
		int found = 0; 
		char hold = floating.front();
		while(in.find('-', found) != string::npos) // go through every dash in in
		{
			string tempIn = in; 
			tempIn.replace(tempIn.find('-', found), 1, 1, hold);
			found = in.find('-', found) + 1; 
			string tempFloat = floating;
			tempFloat.erase(0, 1); 
			set<string> result = wordle(tempIn, tempFloat, dict);
      retval.insert(result.begin(), result.end());
		}
	}
	else
	{
		for(int i = 0; i < 26; i++)
		{
			string tempIn = in; 
			char hold = 'a' + i; 
			tempIn.replace(tempIn.find('-'), 1, 1, hold);
			set<string> result = wordle(tempIn, floating, dict);
      retval.insert(result.begin(), result.end());
		}
	}
	return retval; 
}

// Define any helper functions here

