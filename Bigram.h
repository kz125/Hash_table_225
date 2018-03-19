// Bigram.h

#include "Bigram_base.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
//
// Put any other standard includes or helper functions/classes you need ...
//


class Bigram : public Bigram_base
{
private:
    // NOTICE: Three vectors is used for containing
    // first, second strings and its value
    // Update 1: Should work for manual inputting values
    //           Need to work on putting in value for testing
    // Update 2: Fixed the random loop for inputs
    //           Fixed the conversion from string to ASCII to int
    //           Should work for any input values
    //           Need to fix remove(), update the biggest or smallest key when removed
    // Update 3: Used rehash() to update new biggest and smallest when removed key
    vector<Bigram_key> stringtable;
    vector<int> status;
    vector<int> value;
    // vector<Combine> Btable;
    // vector<Bigram_key> stringtablerecord;
    // vector<int> valuerecord;
    // vector<int> locationrecord;
    Bigram_key biggestkey;
    Bigram_key smallestkey;
    int tablesize;
    int totalelement;
public:
    // Implement all the non-implemented methods from Bigram_base here. Be
    // sure to include a default constructor that creates a new empty Bigram.

    // Constructor
    // The default table size will be 6
    // Resize the table and initialize
    // the total element
    Bigram()
    {
      int tablesize = 6;
      stringtable.resize(tablesize);
      status.resize(tablesize);
      value.resize(tablesize);
      totalelement = 0;
    }
    // Destructor
    ~Bigram()
    {}

    // The number of element that
    // the table currently have
    // a.k.a "n"
    int size() const
    {
      return totalelement;
    }
    // The maximum amount of element
    // The table currently have
    // a.k.a "N"
    int capacity() const
    {
      return stringtable.size();
    }
    // Resize the table given the new size
    void resize(int table_size)
    {
      stringtable.resize(table_size);
      status.resize(table_size);
      value.resize(table_size);
    }
    // Determine whether the key is already
    // in table or not
    bool contains(const Bigram_key& key) const
    {
      //Convert the key from string to integer
      Bigram_key a_key = key;
      int convert = 0;
      for (int i = 0; i < a_key.first.length(); i++)
      {
          char x = key.first.at(i);
          convert += int(x);
      }
      for (int j = 0; j < a_key.second.length(); j++)
      {
          char x = key.second.at(j);
          convert += int(x);
      }
      int table_size = capacity();
      //Find the position of key on the table
      //return true if key is in that position
      //else return false
      for (int i = 0; i < table_size; i++)
      {
        int location = (convert+i*i) % table_size;
        if ((stringtable[location].first.compare(a_key.first) == 0) && (stringtable[location].second.compare(a_key.second) == 0))
        {
          if (status[location] == 1)
          {
            return true;
          }
          break;
        }
      }
      return false;
    }
    // Returns the value of the key
    // ie. The value at the key location
    int value_of(const Bigram_key& key) const
    {
      Bigram_key a_key = key;
      int convert = 0;
      for (int i = 0; i < a_key.first.length(); i++)
      {
          char x = key.first.at(i);
          convert += int(x);
      }
      for (int j = 0; j < a_key.second.length(); j++)
      {
          char x = key.second.at(j);
          convert += int(x);
      }
      int table_size = capacity();
      int location;
      //Find the position of key on the table
      //return true if key is in that position
      //else return false
      for (int i = 0; i < capacity(); i++)
      {
        location = (convert+i*i) % table_size;
        if ((stringtable[location].first.compare(a_key.first) == 0) && (stringtable[location].second.compare(a_key.second) == 0))
        {
          break;
        }
      }
      return value[location];
    }
    // Translate string into ASCII decimal value
    // by going through each character and adding up
    // the integer value
    int translate(string given)
    {
      int val = 0;
      for (int i = 0; i < given.length(); i++)
      {
          char x = given.at(i);
          val += int(x);
      }
      return val;
    }
    // Insert a key and its value to the table
    // Rehash if load factor exceed 0.5
    void put(const Bigram_key& key, int val)
    {
      Bigram_key currkey = key;
      int convert = translate(key.first) + translate(key.second);
      // cout << "String: " << currkey.first << " and " << currkey.second << endl;
      // cout << "Int val: "<< translate(key.first) << " and " << translate(key.second) << endl;
      // cout << "Convert: " << convert << endl;
      int table_size = capacity();
      // cout << "Capacity: " << table_size << endl;
      // cout << "Mod: " << convert%table_size << endl << endl;
      // If there already exist a key at current location
      // Search for an empty space to put the new key in
      for (int i = 0; i < table_size; i++)
      {
        int location = (convert+i*i) % table_size;
        // If found the exact key with different value
        // replace the old value with new value
        if ((stringtable[location].first.compare(currkey.first) == 0) && (stringtable[location].second.compare(currkey.second) == 0))
        {
          value[location] = val;
          status[location] = 1;
          // if the replaced value was the biggest or smallest key
          // rehash to find new biggest or smallest key
          if (((stringtable[location].first.compare(biggestkey.first) == 0) && (stringtable[location].second.compare(biggestkey.second) == 0))
              || ((stringtable[location].first.compare(smallestkey.first) == 0) && (stringtable[location].second.compare(smallestkey.second) == 0)))
          {
            rehash();
            return;
          }
          break;
        }
        else
        {
          if (status[location] == 0)
          {
            stringtable[location] = currkey;
            value[location] = val;
            status[location] = 1;
            // stringtablerecord.push_back(currkey);
            // locationrecord.push_back();
            totalelement++;
            break;
          }
        }
      }
      // If there exist only 1 element in table
      // Make it as the biggest and smallest key
      // in the table
      if (totalelement == 1)
      {
        smallestkey = currkey;
        biggestkey = currkey;
      }
      // Else compare the current smallest and biggest
      // key to find the new smallest and biggest key
      else
      {
        // Make the new key the smallest key
        // if the value of current smallest key is greater
        // than the new key
        if (value_of(smallestkey) > val)
        {
          smallestkey = currkey;
        }
        else
        {
          // Check for the condition where
          // two keys have the same value
          if (value_of(smallestkey) == val)
          {
            // Choose the smallest key base on the
            // alphabetical order of the key
            if (smallestkey.first.compare(currkey.first) > 0)
            {
              smallestkey = currkey;
            }
            else
            {
              if (smallestkey.first.compare(currkey.first) == 0)
              {
                if (smallestkey.second.compare(currkey.second) > 0)
                {
                  smallestkey = currkey;
                }
              }
            }
          }
        }
        // Make the new key the biggest key
        // if the value of current biggest key is greater
        // than the new key
        if (value_of(biggestkey) < val)
        {
          biggestkey = currkey;
        }
        else
        {
          // Check for the condition where
          // two keys have the same value
          if (value_of(biggestkey) == val)
          {
            // Choose the biggest key base on the
            // alphabetical order of the key
            if (biggestkey.first.compare(currkey.first) < 0)
            {
              biggestkey = currkey;
            }
            else
            {
              if (biggestkey.first.compare(currkey.first) == 0)
              {
                if (biggestkey.second.compare(currkey.second) < 0)
                {
                  biggestkey = currkey;
                }
              }
            }
          }
        }
      }
      // Compute load factor
      // and rehash the table if load factor
      // is more than half full
      double loadfactor = load_factor();
      if (loadfactor > 0.5)
      {
        rehash();
      }
    }
    double load_factor() const {
      if (capacity() == 0)
      {
          return 0;
      }
      else
      {
          return double(size()) / capacity();
      }
    }
    // Resize the table and put keys from
    // old table to new table
    // reset the biggest and smallest key
    // if they were removed or overwritten
    void rehash()
    {
      int oldsize = capacity();
      int newsize = oldsize;
      if (load_factor() > 0.5)
      {
        newsize = newsize*2;
      }
      Bigram newtable;
      newtable.resize(newsize);
      for (int location = 0; location < oldsize; location++)
      {
        if (status[location] == 1)
        {
          newtable.put(stringtable[location],value[location]);
        }
      }
      stringtable.clear();
      value.clear();
      status.clear();
      stringtable.resize(newsize);
      value.resize(newsize);
      status.resize(newsize);
      biggestkey = newtable.biggestkey;
      smallestkey = newtable.smallestkey;
      newtable.stringtable.swap(stringtable);
      newtable.value.swap(value);
      newtable.status.swap(status);
      return;
    }

    // Remove the key from table
    void remove(const Bigram_key& key)
    {
      //Convert the key from string to integer
      int the_key = translate(key.first) + translate(key.second);
      int table_size = capacity();
      //Find the position of key on the table
      //if key found in that position, mark
      //status at that location to 0 to represent removed
      //and return
      for (int i = 0; i < table_size; i++)
      {
        int location = (the_key+i*i) % table_size;
        if ((stringtable[location].first.compare(key.first) == 0) && (stringtable[location].second.compare(key.second) == 0))
        {
          status[location] = 0;
          totalelement--;
          // Rehash if the biggest or smallest key was removed
          if (((stringtable[location].first.compare(biggestkey.first) == 0) && (stringtable[location].second.compare(biggestkey.second) == 0))
              || ((stringtable[location].first.compare(smallestkey.first) == 0) && (stringtable[location].second.compare(smallestkey.second) == 0)))
          {
            rehash();
          }
          return;
        }
      }
    }
    // Find the biggest value in table
    Bigram_key max() const
    {
      return biggestkey;
    }
    // Find the smallest value in table
    Bigram_key min() const
    {
      return smallestkey;
    }
    // Printing the table
    // Format: index. [first,second] value status
    void print_table()
    {
      int index = 0;
      for(int i = 0; i < capacity(); i++)
      {
        cout << index << ". [" << stringtable[i].first << "," << stringtable[i].second;
        cout << "] " << value[i] << " " << status[i]<< endl;
        index++;
      }
    }
}; // class Bigram
