#include "Stiva.h"


Stiva::Stiva() {
	this->numere = nullptr;
	this->nr_numere = 0;
}

Stiva::Stiva(double* numere, int nr_numere) {
	if (numere != nullptr) {
		if (nr_numere >= 1) {
			this->nr_numere = nr_numere;
			this->numere = new double[nr_numere];
			for (int i = 0; i < nr_numere; i++)
				this->numere[i] = numere[i];
		}
		else {
			cout << "Numarul de numere < = 0" << endl;
			this->numere = nullptr;
			this->nr_numere = 0;
		}
	}
	else
	{
		cout << "Numere este nullptr" << endl;
		this->numere = nullptr;
		this->nr_numere = 0;
	}
}


Stiva::Stiva(const Stiva& st) {
	
	if (st.numere != nullptr&&st.nr_numere>0) {
		if (this->numere!=nullptr) 
			delete[] this->numere; 
		this->nr_numere = st.nr_numere;
		this->numere = new double[st.nr_numere];
		for (int i = 0; i < st.nr_numere; i++)
			this->numere[i] = st.numere[i];
	}
	else
	{
		
		this->numere = nullptr;
		this->nr_numere = 0;
	}
}

Stiva& Stiva::operator=(const Stiva& st) {
	if (this != &st) {
		if (st.numere != nullptr && st.nr_numere > 0) {
			if (this->numere != nullptr)
				delete[] this->numere;
			this->nr_numere = st.nr_numere;
			this->numere = new double[st.nr_numere];
			for (int i = 0; i < st.nr_numere; i++)
				this->numere[i] = st.numere[i];
		}
	}
	return *this;
}



Stiva::~Stiva() {
	if (this->numere != nullptr) {
		delete[] this->numere;
	}
}



double Stiva::pop_back() {
	if (this->numere != nullptr) {
		double valoare = this->numere[this->nr_numere - 1];
		double* aux = new double[--this->nr_numere];
		for (int i = 0; i < this->nr_numere; i++)
			aux[i] = numere[i];
		delete[] this->numere;
		this->numere = aux;
		return valoare;
	}
	else {
		cerr<<"Nu avem la ce sa dam popback";
	}
}

void Stiva::push_back(double val) {
	if (this->numere != nullptr) {
		double* aux = new double[this->nr_numere + 1];
		int i;
		for (i = 0; i < this->nr_numere; i++)
			aux[i] = numere[i];
		this->nr_numere++;
		aux[i] = val;
		delete[] this->numere;
		this->numere = aux;
	}
	else {
		this->numere = new double[1];
		this->nr_numere = 1;
		this->numere[0] = val;
	}
}

void Stiva::set_stiva(double* numere, int nr_numere) {
	if (numere != nullptr && nr_numere > 0) {
		if (this->numere == nullptr)
			delete[] this->numere;
		this->nr_numere = nr_numere;
		this->numere = new double[nr_numere];
		for (int i = 0; i < nr_numere; i++)
			this->numere[i] = numere[i];
	}
	else {
		this->numere = nullptr;
		this->nr_numere = 0;
	}
}

double* Stiva::get_numere() {
	return this->numere;
}

int Stiva::get_nr_numere() {
	return this->nr_numere;
}




ostream& operator<<(ostream& out, const Stiva& st) {
	out << "Stiva curenta contine: " << st.nr_numere << " numere:" << endl;
	for (int i = 0; i < st.nr_numere; i++) {
		cout << "stiva[" << i << "] = " << st.numere[i] << ' ';
	}
	cout << endl;
	return out;
}

istream& operator>>(istream& in, Stiva& st) {
	if (st.numere != nullptr)
		delete[] st.numere;
	cout << "Numar numere = ";
	in >> st.nr_numere;
	st.numere = new double[st.nr_numere];
	for (int i = 0; i < st.nr_numere; i++) {
		cout << "stiva[" << i << "] = ";
		in >> st.numere[i];
	}
	return in;
}


double& Stiva::operator[](int index) {
	if (index >= 0 && index <= nr_numere) {
		return this->numere[index];
	}
	else {
		throw new exception("Eroare op. []: index<0 sau index> numarul de numere de pe stiva");
	}
}

Stiva& Stiva::operator+(double i) {
	this->push_back(i);
	return *this;
}