#include"stdafx.h"
#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<string>
#include<stdlib.h>

#include "dict1.h"

using namespace std;

void main()
{
	int t, difference;
	int temp, key[40], duplicate_key[40];
	int i = 0, j = 0, k = 0, x = 0, round = 1;
	int dict_length1, cipher_length;
	char ciphertext[50];
	bool compare_result = false;
        
        cout << "Enter the ciphertext";
	cin >> ciphertext;
	cout << "Enter the size of key (t)";
	cin >> t;


	cout << "\n" << ciphertext << "\n" << t;

	dict_length1 = strlen(DICTIONARY1);
	cipher_length = strlen(ciphertext);

	while (i < dict_length1)
	{
		for (j = 0; j < cipher_length;)
		{
			for (k = 0; k < t; k++)
			{
				difference = ciphertext[j] - DICTIONARY1[i + j];
				if (difference < 0)
					difference = difference + 26;
				if (round == 1)
					key[x] = difference;
				else
					duplicate_key[x] = difference;
				x++;	j++;

				if (k == 0 && j == 0)
					temp = i;

				if (j == cipher_length)
					break;
			}
			if (round == 1)
			{
				mergesort(key, 0, t - 1);
				round = 2;
				x = 0;
			}
			else if ((round != 1) && ((x == t) || (j == cipher_length)))
			{
				mergesort(duplicate_key, 0, x - 1);
				compare_result = compare_arrays(key, duplicate_key, x);
				x = 0;
				if (!compare_result)
				{
					i++;	round = 1;	break;
				}				
			}			
		}	
		
		if (j == cipher_length)
			break;
	}

	if (j < cipher_length)
		cout << "\n Not in Dictionary 1";
	else
		cout << "\n Found in Dictionary 1";

	cout << "\n";
	for (j = 0; j<t; j++)
		cout << "\n" << j << "--" << key[j];

	for (j = 0; j < cipher_length; j++)
		cout << DICTIONARY1[j];

	cin >> j;

}

