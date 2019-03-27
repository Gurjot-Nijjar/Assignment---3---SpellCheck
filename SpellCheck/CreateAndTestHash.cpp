/*
Gurjot Singh Nijjar 
Computer Science 335 Assignment 3
Professor Stamos
our Test Hash Functions tests three possible hash tables using linear probing
quadratic probing and double hashing. Runs a set of functions such as contains
and then checks size of elements, table size, and collisions with load factor and etx.


*/

#include "QuadraticProbing.h"
#include "LinearProbing.h"
#include "DoubleHashing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;



template <typename HashTableType>
void
TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();  
  //..Insert your own code
  ifstream WordsFile;
  WordsFile.open(words_filename);
  ifstream QueryFile;
  QueryFile.open(query_filename);
  string word_line, query_line;
  while (getline(WordsFile, word_line))
  {
    hash_table.Insert(word_line);
  }
  while (getline(QueryFile,query_line))
  {
    if (hash_table.Contains(query_line))
        cout << query_line << " is found in the table." << endl; 
    else 
        cout << query_line << " is not found in the table. " << endl;
  }
 
  double elem = hash_table.NumberOfElements();
  double table = hash_table.SizeOfTable(); 
  int  collisions = hash_table.NumberOfCollisions();
  cout << "Collisions: " << collisions << endl;
  cout << "Number of items: " << elem << endl;
  cout << "Size of hash table: " << table <<  endl;
  cout << "Load factor: " << static_cast<double> (elem / table) <<  endl;
  cout << "Avg. number of collisions: " << static_cast<double> (collisions / elem) <<  endl;
}

// Sample main for program CreateAndTestHash
int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }
  
  const string words_filename(argv[1]);
  const string query_filename(argv[2]);
  const string param_flag(argv[3]);

  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);    
  } else if (param_flag == "quadratic") {
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);    
  } else if (param_flag == "double") {
     HashTableDouble<string> double_probing_table;
     TestFunctionForHashTable(double_probing_table, words_filename, query_filename);    
  } else {
    cout << "Uknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}
