#include <iostream>
#include "Bigram.h"
#include <random>
#include <stdlib.h>
#include <ctime>
#include <cstring>
using namespace std;

// int conversion (string give)
// {
//   char *convert = new char [give.length() + 1];
//   strcpy(convert, give.c_str());
//   int val;
//   int total;
//   int length = give.length();
//   int i = 0;
//   string a_string = give;
//   while(i < length)
//   {
//     val = atoi();
//     move = move+1;
//     total += val;
//     i++;
//     cout << val << endl;
//   }
//   cout << "Done" << endl;
//   return total;
// }

int main()
{
  Bigram hash;
  cout << "Making grid" << endl;
  Bigram_key input;
  cout << "Making key" << endl;
  int hashval;
  int first;
  int second;
  int third;
  first = 1231;
  input.first = to_string(first);
  second = 999;
  input.second = to_string(second);
  third = 66;
  hashval = third;
  hash.put(input,hashval);
  input.first = "AB";
  input.second = "B";
  third = 12000000;
  hashval = third;
  hash.put(input,hashval);
  // string str_dec = "A Space Odyssey";
  // int convert = conversion(str_dec);
  // cout << str_dec << " " << convert << endl;
  srand(time(NULL));
  vector<int> thefirst;
  vector<int> thesecond;
  vector<int> thethird;
  int numberofelements = 10000;
  for (int j = 0; j < numberofelements; j++)
  {
    first = (rand()%1000000);
    second = (rand()%1000000);
    third = (rand()%1000000);
    thefirst.push_back(first);
    thesecond.push_back(second);
    thethird.push_back(third);
    // cout << first << "   " << second << "   " << third << endl;
  }
  cout << "Done generating data" << endl;
  // cout << endl;
  // for (int k = 0; k < numberofelements; k++)
  // {
  //   cout << thefirst[k] << "   " << thesecond[k] << "   " << thethird[k] << endl;
  // }
  for (int i = 0; i < numberofelements; i++)
  {
    first = thefirst[i];
    input.first = to_string(first);
    second = thesecond[i];
    input.second = to_string(second);
    third = thethird[i];
    hashval = third;
    hash.put(input,hashval);
  }
  cout << "Load factor: " << hash.load_factor() << endl;
  cout << "Number of elements: " << hash.size() << endl;
  cout << "Capacity of table: " << hash.capacity() << endl;
  cout << "Done inputting data" << endl;
  cout << endl;
  //hash.print_table();
  ///////////////////////
  first = 1231;
  input.first = to_string(first);
  second = 999;
  input.second = to_string(second);
  third = 66;
  hashval = third;

  if (hash.contains(input) == true) {
    cout << "Found [" << input.first << "," << input.second << "]" << endl;
  }
  else
  {
    cout << "Not found [" << input.first << "," << input.second << "]" << endl;
  }
  cout << "Value of [" << input.first << "," << input.second << "]: " << hash.value_of(input) << endl;
  cout << endl;

  Bigram_key biggest = hash.max();
  Bigram_key smallest = hash.min();
  cout << "Biggest Key: [" << biggest.first << "," << biggest.second <<"]" << endl;
  cout << "Smallest Key: [" << smallest.first << "," << smallest.second <<"]" << endl;

  cout << "Removing [" << input.first << "," << input.second << "]" << endl;
  hash.remove(input);
  if (hash.contains(input) == true) {
    cout << "Found [" << input.first << "," << input.second << "]" << endl;
  }
  else
  {
    cout << "Not found [" << input.first << "," << input.second << "]" << endl;
  }
  cout << endl;

  input.first = "AB";
  input.second = "B";
  third = 15456;
  hashval = third;
  hash.put(input,hashval);
  //hash.print_table();
  biggest = hash.max();
  smallest = hash.min();
  cout << "Biggest Key: [" << biggest.first << "," << biggest.second <<"]" << endl;
  cout << "Smallest Key: [" << smallest.first << "," << smallest.second <<"]" << endl;
  cout << endl;

  input.first = "BA";
  input.second = "B";
  third = 5500;
  hashval = third;
  if (hash.contains(input) == true) {
    cout << "Found [" << input.first << "," << input.second << "]" << endl;
  }
  else
  {
    cout << "Not found [" << input.first << "," << input.second << "]" << endl;
  }
  hash.put(input,hashval);
  if (hash.contains(input) == true) {
    cout << "Found [" << input.first << "," << input.second << "]" << endl;
  }
  else
  {
    cout << "Not found [" << input.first << "," << input.second << "]" << endl;
  }
  cout << endl;

  hash.remove(hash.max());
  hash.remove(hash.min());
  cout << "Removing max and min" << endl;
  biggest = hash.max();
  smallest = hash.min();
  cout << "Biggest Key: [" << biggest.first << "," << biggest.second <<"]" << endl;
  cout << "Smallest Key: [" << smallest.first << "," << smallest.second <<"]" << endl;
  cout << "Load factor: " << hash.load_factor() << endl;
  cout << "Number of elements: " << hash.size() << endl;
  cout << "Capacity of table: " << hash.capacity() << endl;
  return 0;
}
