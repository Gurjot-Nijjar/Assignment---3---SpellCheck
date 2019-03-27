/*
Gurjot Singh Nijjar 
Computer Science 335 Assignment 3
Professor Stamos
our Spell check implementation file helps us to spell check any given 
document with an according dictionary document as another argument 
then modifies the mispelled word and prints out its 
possible corrections



*/

#include <iostream>
#include <fstream>
#include "stdlib.h"
#include "QuadraticProbing.h"
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

void StringModifier(string &doc_word)
{
  doc_word.erase(remove_if( doc_word.begin(), doc_word.end(), ::isdigit), doc_word.end());
  transform(doc_word.begin(), doc_word.end(), doc_word.begin(), ::tolower);
  if(doc_word.find('\'') == string::npos)
    doc_word.erase(remove_if( doc_word.begin(), doc_word.end(), ::ispunct), doc_word.end());
// This function is specifically made so we dont run into words with uppercase letters, any numbers, or any punctuation, and splits in the word.
}

int main(int argc, char **argv) {

  if (argc != 3) 
  {
    cout << "Usage: " << argv[0] << " <documentfile> <dictionaryfile>" << endl;
    return 0;
  }

  string document_filename(argv[1]);
  string dictionary_filename(argv[2]);
  cout << "This program will run the " << argv[0] << " with given parameters " << document_filename << ", " << dictionary_filename << endl;

  string document_word, dictionary_word;
  ifstream document_file(document_filename); 
  ifstream dictionary_file(dictionary_filename);
    //Fill hash table with dictionary file
  HashTable<string> quadratic_probing_table;
  vector<string> word; 

  while(dictionary_file >> dictionary_word)
  {
    quadratic_probing_table.Insert(dictionary_word);
  }

  while (document_file >> document_word)
  {
    stringstream Doc_Stream(document_word);
// We use stringstream in order to get each single word in the txtFile one by one 
    while (getline(Doc_Stream, document_word, '-')) 
    {
      StringModifier(document_word);
      // run string modifier and get line between hyphens
      if( document_word.end() == document_word.begin() )
        continue;
      // last position to the first position of our string is being checked. 


      if( !quadratic_probing_table.Contains(document_word) )
        {

          /*
          We have three for loops in order to modify each case which is Removing a Character
          Adding a Character, or even swap words within the document string. We modify
          using each case and eash possiblity  and check in each for loop if that possiblity
          is even considered in the dictionary word Hash Table. If the new modified
          document word is contained in the hash table then we can safely assume that our
          word is one of the possiblities and we push that possiblity in a vector of strings.
          And after the for loops have stressed each possibility then we can safely assume 
          that our misspelled word has all of its possibilities pushed in a vector and then
          we print out the mispelled word and all of its corrections out on the screen.
          We do this one by one until the end of the document.   
          */
          char abc[] = "abcdefghijklmnopqrstuvwxyz"; // alphabet in order to add a character
          string Case_Word = document_word;
          for( unsigned int j = 0; j < Case_Word.length(); j++)
          {
            for(int i = 0; i < 26; ++i)
            {
              string char_pos;
              char_pos = abc[i];
              Case_Word.insert(j,char_pos); 
              if(quadratic_probing_table.Contains(Case_Word))
              word.push_back(Case_Word);
              Case_Word.erase(j, 1);
            }
          }          
          for( unsigned int i = 0; i < Case_Word.length(); ++i)
          {
            string Case_b = Case_Word; // our Case_b to check 
            Case_b.erase(i,1);
            if(quadratic_probing_table.Contains(Case_b))
            word.push_back(Case_b);
          }
          for ( unsigned int i = 1; i < Case_Word.length(); ++i)
          {
            string Case_c = Case_Word;
            swap(Case_c[i], Case_c[i-1]); //
            if(quadratic_probing_table.Contains(Case_c))
            word.push_back(Case_c);
          } 

          // our print function for the original mispelled word onto the screen with the vector of corrections
          if(!word.empty())
          {
          cout << document_word << " ----> "; 
          for (unsigned int q = 0; q < word.size(); q++) 
          {
            cout <<  word[q] << ", ";
          }
          cout << endl;
          }
          while (!word.empty())
          {
            word.pop_back();
          }
        }
      }
    }

  return 0;
}
