#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <vector> 
using namespace std;
void print (string HS_table[])
{//print out all key in the hash table
	for(int i = 0 ; i < 26 ; i++)
	{
		if(HS_table[i] != "never used" && HS_table[i] != "tombstone")
		{
			cout << HS_table[i] << " ";
		}
	}

	cout << endl;
}

int searching (string HS_table[], string key)
{//search the key and return the Hash value for inserting or deleting key
	int len = key.length()-1;
	int HS_value = key[len] - 'a';

	int t = -1;
	for (int i = HS_value; i < 26; i++)
	{
		if(HS_table[i] == key)
		{//when deletion, we need to find the key in the table
			return i;
		}
		else if(HS_table[i] == "tombstone" && t == -1)
		{//if there is tombstone, we need to know min of tombstone for inserting new value
			t = i;
		}
		else if (HS_table[i] == "never used")
		{//search the key until meet never used.
			if (t != -1)
			{
				return t;//if there are tombstone, return it
			}
			return i;//if there are not tomebston, return never used 
		}
	}

	//when we meet the end of table length, restart from 0
	int j;
	for(j = 0 ; j < HS_value; j++)
	{
		if(HS_table[j] == key)
		{//when deletion, we need to find the key in the table
			return j;
		}
		else if(HS_table[j] == "tombstone" && t == -1)
		{//if there is tombstone, we need to know min of tombstone for inserting new value
			t = j;
		}
		else if (HS_table[j] == "never used")
		{//search the key until meet never used.
			if (t != -1)
			{
				return t;//if there are tombstone, return it
			}
			return j;//if there are not tomebston, return never used 
		}
	}

	return j;
}

int main()
{
	string input;

	getline(cin,input);

	vector<string> inputs;

	string s_input ="";

	int len = input.length();
	for (int i = 0 ; i < len; i++)
	{//separate inputs
		if (input[i] != ' ')
		{
			s_input += input[i];
		}

		if (input[i] == ' ' || i == len-1)
		{
			inputs.push_back(s_input);
			s_input = "";
		}
	}

	string HS_table[26];

	for (int i = 0 ; i < 26 ; i++)
	{//initialize the hash table
		HS_table[i] = "never used";
	}

	len = inputs.size();
	for (int i = 0; i < len; i++)
	{ //modification moves
		string temp = inputs[i];

		char moves = temp[0];
		string key = temp.substr(1,temp.length()-1);

		int HS_value = searching(HS_table,key); //searching the table and return the value for saving or deleting key
		//cout << key << endl;
		if(moves == 'A' && (HS_table[HS_value] == "never used" || HS_table[HS_value] == "tombstone"))
		{//insertion
			HS_table[HS_value] = key;
		}
		else if (moves == 'D' && HS_table[HS_value] == key)
		{//deletion
			HS_table[HS_value] = "tombstone";
		}
	}

	print(HS_table);//print

    return 0;
}
