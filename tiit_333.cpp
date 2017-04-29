#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

void subset_func(string** el_in_set, int count_el_in_set) {
	cout << "How many elements are going to be in subsets?  ";
	int k = 0;
	cin >> k;
	cout << endl;
	int* a = new int[k]; 
	for (int i = 0; i < k; i++) {
		a[i] = i;
	}
	int p = k - 1;
	while (p >= 0) {
		cout << "{ ";
		for (int i = 0; i < k; i++) {
			cout << *(el_in_set[a[i]]);
			if (i != k - 1) { cout << ","; }
		} cout << " } " << endl;

		if (a[k-1] == count_el_in_set - 1) {
			p = p - 1;
}
		else {
			p = k - 1;
		}

		if (p >= 0) {
			for (int i = k - 1; i >= p; i--) {
				a[i] = a[p] + i - p + 1;
			}
		}
	}

	delete[] a;
	cout << endl;
}

char* read(const char* path,int &num) {

	ifstream infile(path);
	if (!infile) {
		cout << "Reading error!" << endl;
		return NULL;
	}

	infile.seekg(0,ios::end);
	num = (int)infile.tellg() / sizeof(char);
	infile.seekg(0,ios::beg);
	char* buf = new char[num];
	while (!infile.eof()) {
		infile.getline(buf, num + 1);
	}
	cout << "Your set: ";;
	for(int i = 0 ;i < num; i++) {
		cout << buf[i];
	}
	cout << endl;

	return buf;

}

string** find_elements_of_set(char* buf, int num, int &count_el_in_set) {
	count_el_in_set = 0; static int k = 0;

	for (int i = 1; i < num; i++) {
		if (buf[i] == '{' || buf[i] == '<') {
			k++;
		}
		if (buf[i] == '}' || buf[i] == '>') {
			k--;
		}
		if (buf[i] == ',' && k == 0) {
			count_el_in_set++; 
		}
	}

	count_el_in_set++;							// last element

	int* index = new int[count_el_in_set]; count_el_in_set = 0; k = 0;

	for (int i = 1; i < num; i++) {
		if (buf[i] == '{' || buf[i] == '<') {
			k++;
		}
		if (buf[i] == '}' || buf[i] == '>') {
			k--;
		}
		if (buf[i] == ',' && k == 0) {
			index[count_el_in_set] = i; count_el_in_set++;
		}
	}	index[count_el_in_set] = num; count_el_in_set++;

	/*static int l = 1;
	for (int i = 0; i < count_el_in_set; i++) {
		for (l; l < index[i]; l++) {
			cout << buf[l];
		} l++;
		cout << " ";
	}
	for (l; l < num-1; l++) {
		cout << buf[l];
	}*/

	string buf1 = (const char*)buf; 
	
	string** el_in_set = new string*[count_el_in_set];
	static int pos1 = 1;
	for (int i = 0; i < count_el_in_set; i++) {
		el_in_set[i] = new string; int num2 = index[i] - pos1;
		*(el_in_set[i]) = buf1.substr(pos1,num2);
		pos1 = index[i] + 1;
		}
	
	delete[] index;
	return el_in_set;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int num = 0; char* buf = read("set1.txt", num);
	static int count_el_in_set = 0; string** el_in_set = find_elements_of_set(buf, num, count_el_in_set);
	subset_func(el_in_set, count_el_in_set);

	system("pause");
    return 0;
}