#include <iostream>
#include <string>
#include "StringParser.h"
#include "Stiva.h"
#include "Calculator.h"
using namespace std;

//https://en.wikipedia.org/wiki/Shunting-yard_algorithm 

int Calculator::nrEcuastiiCitite = 0;

int main() {
	Calculator c;
	Calculator t;
	cin >> c;
	double rezultat;
	StringParser sp;

	sp = c.get_Parser();
	while (strcmp(sp.getSir(), "exit") != 0) {
		t = c;
		cout << t;
		rezultat = c.EvalueazaExpresia();
		if (!isnan(rezultat))
			cout << rezultat << endl; //evaluam si afisam rezultatul
		cin >> c;
		sp = c.get_Parser();
	}
	
	
	Stiva s1;
	cout << s1+2.3;
	
}