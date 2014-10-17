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
#include<iostream>
#include<stdlib.h>
#include"stdafx.h"
#include"dict1.h"

using namespace std;

void mergesort(int *a, int low, int high);
void merge(int *a, int low, int high, int mid);
bool compare_arrays(int a[], int b[], int t);

// Main entry of this application.
void main()
{
	// Varibles decalaration and initialization
	int t, difference;
	int temp, key[40], duplicate_key[40];
	int i = 0, j = 0, k = 0, x = 0, round = 1;
	int dict_length1, cipher_length;
	char ciphertext[50];
	bool compare_result = false;
        
	cout << "************************************************************************\n"
		 <<	"* Title  : Project 1 (Cryptanalysis: decryption of substitution ciphers).\n"
		 <<	"* Author : Pooja Patil and Mayur Kale \n* Date   : 10/16/2014 \n* Version: 1.0\n"
	     << "************************************************************************\n\n";
    cout << "Enter the ciphertext: ";
	cin  >> ciphertext;
	cout << "Enter the size of key (t): ";
	cin  >> t;


	cout << "\nEntered ciphertext: " << ciphertext << " and size of key: " << t;

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

	cout << "\n";
	for (j = 0; j<t; j++)
		cout << "\n" << j << "--" << key[j];

	cout << "\nPlain Text: ";
	for (j = 0; j < cipher_length; j++)
		cout << DICTIONARY1[j]; 
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
