/*
 * Title: Project 1 (Cryptanalysis: decryption of substitution ciphers).
 * Purpose: This cryptanalysis project consists of a software implementation of an algorithm that tries to decrypt an L-symbol challenge 
 *          ciphertext using a plaintext dictionary and within a reasonable amount of time.
 * Author: Pooja Patil and Mayur Kale 
 * Date: 10/16/2014
 * Version: 1.0
 */

#include<stdio.h>
#include<conio.h>
#include<string>
#include<sstream>
#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<regex>
#include"stdafx.h"
#include"dict1.h"

using namespace std;

void mergesort(int *a, int low, int high);
void merge(int *a, int low, int high, int mid);
bool compare_arrays(int a[], int b[], int t);
int Exit();

// Main entry of this application.
int main()
{
	// Variables declaration and initialization
	int t = 0, difference;
	int temp, key[40], duplicate_key[40];
	int i = 0, j = 0, k = 0, x = 0, round = 1;
	int dict_length1, cipher_length;
	char ciphertext[50];
	bool compare_result = false;

	string input = "";
        
	cout << "************************************************************************\n"
		 <<	"* Title  : Project 1 (Cryptanalysis: decryption of substitution ciphers).\n"
		 <<	"* Author : Pooja Patil and Mayur Kale \n* Date   : 10/16/2014 \n* Version: 1.0\n"
	     << "************************************************************************\n\n";
    cout << "Enter the ciphertext: ";
	cin  >> ciphertext;

	while (true) {
		cout << "Enter the size of key (t): ";
		cin >> input;

		// This code converts from string to number safely.
		stringstream myStream(input);
		if (myStream >> t)
			break;
		cout << "Invalid number, please try again" << endl;
	}

	cout << "\nEntered ciphertext: " << ciphertext << " and size of key: " << t;

	clock_t begin = clock(); 

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
		cout << "\nNot in Dictionary 1";
	else
		cout << "\nFound in Dictionary 1";

	clock_t end = clock();

	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << "\n";
	for (j = 0; j<t; j++)
		cout << "\n" << j << "--" << key[j];

	cout << "\nPlain Text: ";
	for (j = 0; j < cipher_length; j++)
		cout << DICTIONARY1[j];

	cout << "\nTotal time taken: " << elapsed_secs;
	
	// Do you want to exit or repeat again?
	if(Exit() == 1)
      return 0;
	else
      main(); 
}

void mergesort(int *a, int low, int high)
{
	// Recursive sort
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		mergesort(a, low, mid);
		mergesort(a, mid + 1, high);
		merge(a, low, high, mid);
	}
	return;
}

void merge(int *a, int low, int high, int mid)
{
	// Variables declaration.
	int i, j, k, c[50];
	i = low;
	k = low;
	j = mid + 1;
	// Merges the two array's into c[] until the first one is finish
	while (i <= mid && j <= high)
	{
		if (a[i] < a[j])
		{
			c[k] = a[i];
			i++;
		}
		else
		{
			c[k] = a[j];
			j++;
		}
		k++;
	}
	// Completes the array filling in it the missing values
	while (i <= mid)
	{
		c[k] = a[i];
		k++;
		i++;
	}
	while (j <= high)
	{
		c[k] = a[j];
		k++;
		j++;
	}
	// Prints into the original array
	for (i = low; i < k; i++)
	{
		a[i] = c[i];
	}
}

//Compares array a[] against array b[] and returns the true or false value.
bool compare_arrays(int a[], int b[], int t)
{
	for (int i = 0; i < t; i++) {
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}

int Exit() {
    char exit;
    cout << "\n";
    exitloop:
    cout << "\nDo you want to quit the program? (y/n)";
    cin >> exit;
    
    switch (exit) {
           case 'y':
           case 'Y':
                return 1;
                break;
           case 'n':
           case 'N':
				system("cls");
                return 0;
                break;
           default:
                goto exitloop;
                break;                
    } 
}