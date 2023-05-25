#pragma once
#pragma warning(disable:4996)
#include "Stiva.h"
#include "StringParser.h"


class Calculator
{
private:
	Stiva st;
	StringParser sp;
	const int nrEcuatii;
public:
	static int nrEcuastiiCitite;

	Calculator();

	Calculator(const char* expresie);

	Calculator(const Calculator& ca);

	Calculator& operator=(const Calculator& ca);

	void set_stiva(double* numere, int numar_numere);

	void set_Parser(const char* expresie);

	Stiva get_stiva();

	StringParser get_Parser();

	double EvalueazaExpresia(); 

	friend ostream& operator<<(ostream& out, const Calculator& ca);

	friend istream& operator>>(istream& in, Calculator& ca);


};

