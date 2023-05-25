#pragma once
#include <iostream>
#include <string>
using namespace std;

class Stiva {
private:
	double* numere;
	int nr_numere;
public:
	Stiva();

	Stiva(double* numere, int nr_numere);

	Stiva(const Stiva& st);

	Stiva& operator=(const Stiva& st);

	~Stiva();

	double pop_back(); 

	void push_back(double val); 

	void set_stiva(double* numere, int nr_numere);

	double* get_numere();

	int get_nr_numere();

	friend ostream& operator<<(ostream& out, const Stiva& st);

	friend istream& operator>>(istream& in, Stiva& st);

	double& operator[](int index);

	Stiva& operator+(double i);
};
