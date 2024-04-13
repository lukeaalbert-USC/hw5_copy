#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <regex>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(std::string partial,
    std::string floating,
    const std::set<std::string>& dict,
    std::set<std::string>& result,
    unsigned int curr);

int countUnderscores(const std::string& str);

// bool contains(std::string partial, const std::string& floating, unsigned int index);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> result;
    std::string partial = in;

    std::string floatingCopy = floating;

    wordleHelper(partial, floatingCopy, dict, result, 0);
    return result;
}


// Define any helper functions here
void wordleHelper(std::string partial,
    std::string floating,
    const std::set<std::string>& dict,
    std::set<std::string>& result,
    unsigned int curr)
{
    if (curr == partial.size())
    { 
      if (dict.find(partial) != dict.end() && floating.length() == 0) {
            result.insert(partial);
      }
      return;
    }

    if (partial[curr] != '-')
    {
      wordleHelper(partial, floating, dict, result, curr + 1);
    }

    else
    {
      // Add a floating letter
      for (int j = 0; j < floating.length(); j++) {
        partial[curr] = floating[j];
        std::string substr = floating.substr(0,j) + floating.substr(j+1); // get the substring without letter j
        // put letter j in the partial
        wordleHelper(partial, substr, dict, result, curr + 1);
      }
      if (countUnderscores(partial) >= floating.length()) // number of blanks > the number of floating letters
      {
        for (int i = (int) 'a'; i <= (int) 'z'; i++) //for all letters
        {
          partial[curr] = char(i);
          wordleHelper(partial, floating, dict, result, curr + 1);
        }
      }
    }
}


int countUnderscores(const std::string& str) {
  int count = 0;
  for (int k = 0; k < str.length(); k++) {
    count += (int) (str[k] == '-');
  }
  return count;
}