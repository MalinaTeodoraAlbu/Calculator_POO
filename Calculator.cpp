#pragma warning(disable:4996)
#include "Calculator.h"


Calculator::Calculator():nrEcuatii(nrEcuastiiCitite+1)
{
	this->st.set_stiva(nullptr, 0);
	this->sp.setSir(nullptr);
}

Calculator::Calculator(const char* expresie):nrEcuatii(++nrEcuastiiCitite)
{
	if (expresie != nullptr) {
		sp.setSir(expresie);
	}
	else {
		sp.setSir(nullptr);
	}
	this->st.set_stiva(nullptr, 0); //initial stiva este goala
}

Calculator::Calculator(const Calculator& ca):nrEcuatii(++nrEcuastiiCitite) {
	this->sp = ca.sp;
	this->st = ca.st;
}

Calculator& Calculator::operator=(const Calculator& ca) {
	if (this != &ca) {
		this->sp = ca.sp;
		this->st = ca.st;
	}
	return *this;
}


void Calculator::set_stiva(double* numere, int numar_numere) {
	st.set_stiva(numere, numar_numere);
}

void Calculator::set_Parser(const char* expresie) {
	sp.setSir(expresie);
}

Stiva Calculator::get_stiva() {
	Stiva aux(this->st);
	return aux;
}

StringParser Calculator::get_Parser() {
	StringParser aux(this->sp);
	return aux;
}


double Calculator::EvalueazaExpresia() {
	string cifre = "0123456789";
	if (sp.getSir() != nullptr) {
		char* aux = sp.getSirRPN();
		if (aux != nullptr) {
			cout <<"Reversed Polish Notation: "<< aux << endl;
			char* pch;
			pch = strtok(aux, " ");
			while (pch) {
				if (strlen(pch) > 1 || (strlen(pch) == 1 && cifre.find(pch) != string::npos)) {//avem numar mai multe cifre sau 1
					st.push_back(atof(pch));
				}
				else {
					//avem operator
					if (st.get_nr_numere() < 2) {
						cerr << "Operatie invalida"<<endl;
						return NAN;
					}
					else { //avem cel putin 2 numere in stiva
						//facem pop la 2 pentru operator
						double x, y;
						y = st.pop_back();
						x = st.pop_back();
						if (strcmp(pch, "#") == 0) {
							st.push_back(pow(x, 1 / y));
						}
						else if (strcmp(pch, "^") == 0) {
							st.push_back(pow(x, y));
						}
						else if (strcmp(pch, "*") == 0) {
							st.push_back(x * y);
						}
						else if (strcmp(pch, "/") == 0) {
							if (y == 0) {
								cerr << "Eroare impartire la 0" << endl;
								return NAN;
							}
							else
								st.push_back(x / y);
						}
						else if (strcmp(pch, "+") == 0) {
							double val = x + y;
							st.push_back(x + y);
						}
						else if (strcmp(pch, "-") == 0) {
							st.push_back(x - y);
						}
						else {
							cerr<<"Operatie invalida"<<endl;
							return NAN;
						}
					}

				}
				pch = strtok(NULL, " ");
			}
			if (st.get_nr_numere() == 1) {
				return st[0];
			}
			else {
				cerr<<"Operatie invalida"<<endl;
				return NAN;
			}
		}
		else {
			cerr << "Operatie invalida"<<endl;
			return NAN;
		}
	}
	else {
		cerr << "Calculatorul nu contine nicio expresie momentan"<<endl;
		return NAN;
	}	
}



ostream& operator<<(ostream& out, const Calculator& ca) {
	out << "Ecuatia " << ca.nrEcuatii << " , citite " << ca.nrEcuastiiCitite << endl;
	out << ca.sp;
	out << ca.st; //rezultatul aici
	return out;
}

istream& operator>>(istream& in, Calculator& ca) {
	cout << "Introduceti expresia: ";
	char aux[100];
	in.getline(aux, 100);
	ca.set_Parser(aux);
	ca.set_stiva(nullptr, 0);
	ca.nrEcuastiiCitite++;
	return in;
}