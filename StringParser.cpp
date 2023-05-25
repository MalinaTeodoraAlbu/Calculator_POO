#include "StringParser.h"

StringParser::StringParser() {
	this->sir = nullptr;
}


StringParser::StringParser(const char* sir) {
	if (sir != nullptr) {
		this->sir = new char[strlen(sir) + 1];
		strcpy_s(this->sir, strlen(sir) + 1, sir);
	}
	else
		this->sir = nullptr;
}


StringParser::StringParser(const StringParser& sp) { 

	if (sp.sir != nullptr) {
		this->sir = new char[strlen(sp.sir) + 1];
		strcpy_s(this->sir, strlen(sp.sir) + 1, sp.sir);
	}
	else
		this->sir = nullptr;

}


StringParser& StringParser::operator=(const StringParser& sp) {
	if (this != &sp) {

		if (this->sir != nullptr)
			delete[] this->sir;

		if (sp.sir != nullptr) {
			this->sir = new char[strlen(sp.sir) + 1];
			strcpy_s(this->sir, strlen(sp.sir) + 1, sp.sir);
		}
		else
			this->sir = nullptr;

	}
	return *this;
}

StringParser::~StringParser() {
	if (this->sir != nullptr)
		delete[] this->sir;
}

char* StringParser::getSir() {
	return this->sir;
}

void StringParser::setSir(const char* sir) {
	if (sir != nullptr)
	{
		if (this->sir != nullptr)
			delete[] this->sir;
		this->sir = new char[strlen(sir) + 1];
		strcpy_s(this->sir, strlen(sir) + 1, sir);
	}
	else {
		this->sir = nullptr;
	}
}

ostream& operator<<(ostream& out, const StringParser& sp) {
	if (sp.sir != nullptr)
		out << "Sir Parser: " << sp.sir << endl;
	return out;
}

istream& operator>>(istream& in, StringParser& sp) {
	cout << "Sir Parser: ";
	char aux[100];
	in.getline(aux, 100);
	if (sp.sir != nullptr)
		delete[] sp.sir;
	sp.sir = new char[strlen(aux) + 1];
	strcpy_s(sp.sir, strlen(aux) + 1, aux);
	return in;
}


int StringParser::getPrecedenta(char op) {
	switch (op) {
	case '#':
		return 4;
	case '^':
		return 4;
	case '*':
		return 3;
	case '/':
		return 3;
	case '+':
		return 2;
	case '-':
		return 2;

	}
}

string StringParser::getAsociativitate(char op) {
	switch (op) {
	case '#':
		return "right";
	case '^':
		return "right";
	default:
		return "left";
	}
}

char* StringParser::getSirRPN() { //algoritmul Shunting Yard by Dijkstra
	string output;
	string opstack;
	string operatori = "+*/^#";
	int i;
	int io;
	i = 0;
	int numar_numere = 0;
	int numar_operatori = 0;
	int numar_pct = 0;
	if (sir != nullptr) {
		while (i < strlen(sir)) {
			if (sir[i] == '-') {
				if (i == 0 && isdigit(sir[i + 1])) {
					output.push_back(sir[i]);
				}
				else if (sir[i - 1] == '[' || sir[i - 1] == '(') {
					if (isdigit(sir[i + 1])) {
						output.push_back(sir[i]);
					}
					else {
						cerr << "Scriere gresita." << endl;
						return nullptr;
					}
				}
				else {
					io = opstack.length() - 1; //top of the stack
					while (io >= 0) {
						if (!(opstack[io] != '(' && opstack[io] != '[' &&
							(getPrecedenta(opstack[io]) > getPrecedenta(sir[i]) ||
								(getPrecedenta(opstack[io]) == getPrecedenta(sir[i]) &&
									getAsociativitate(sir[i]) == "left")))
							) break;
						output.push_back(opstack[io]);
						output.push_back(' ');
						opstack.pop_back();
						io--;
					}
					opstack.push_back(sir[i]);
					numar_operatori++;
				}
			}
			else if (isdigit(sir[i])) {
				numar_pct = 0;
				while (isdigit(sir[i]) || sir[i] == '.') {
					output.push_back(sir[i]);
					if (sir[i] == '.')
						numar_pct++;
					i++;
				}
				if (numar_pct > 1)
				{
					cerr << "Expresie infix invalida(numar de virgule mult prea mare)." << endl;
					return nullptr;
				}
				i--;
				output.push_back(' ');
				numar_numere++;
			}
			else if (operatori.find(sir[i]) != -1) // => found it
			{
				io = opstack.length() - 1; //top of the stack
				while (io >= 0) {
					if (!(opstack[io] != '(' && opstack[io] != '[' &&
						(getPrecedenta(opstack[io]) > getPrecedenta(sir[i]) ||
							(getPrecedenta(opstack[io]) == getPrecedenta(sir[i]) &&
								getAsociativitate(sir[i]) == "left")))
						) break;
					output.push_back(opstack[io]);
					output.push_back(' ');
					opstack.pop_back();
					io--;
				}

				opstack.push_back(sir[i]);
				numar_operatori++;
			}
			else if (sir[i] == '(') {
				if (opstack.find('(') != -1)
				{
					cerr << "Paranteze invalide!" << endl;
					return nullptr;
				}
				opstack.push_back(sir[i]);

			}
			else if (sir[i] == '[') {
				if (opstack.find('(') != -1 || opstack.find('[') != -1)
				{
					cerr << "Paranteze invalide!" << endl;
					return nullptr;
				}
				opstack.push_back(sir[i]);
			}
			else if (sir[i] == ')') {

				io = opstack.length() - 1;
				while (io >= 0) {
					if (opstack[io] == '(') //conditie spargere bucla
						break;
					if (opstack[io] != '[') {
						output.push_back(opstack[io]);
						output.push_back(' ');
						opstack.erase(io, 1);
					}
					io--;
				}
				if (io < 0)
				{
					cerr << "Eroare parantezele rotunde nu se potrivesc" << endl;
					return nullptr;
				}
				opstack.erase(io, 1);
			}
			else if (sir[i] == ']') {

				io = opstack.length() - 1;
				while (io >= 0) {
					if (opstack[io] == '[') //conditie spargere bucla
						break;

					if (opstack[io] != '(') {
						output.push_back(opstack[io]);
						output.push_back(' ');
						opstack.erase(io, 1);
					}
					io--;
				}
				if (io < 0)
				{
					cerr << "Eroare parantezele patrate nu se potrivesc" << endl;
					return nullptr;
				}
				opstack.pop_back();
			}
			else {
				if (sir[i] != ' ')
				{
					cerr << "Caractere eronate sau pozitionare gresita a '.'" << endl;
					return nullptr;
				}
			}
			i++;

		}
		if (!opstack.empty()) {
			io = opstack.length() - 1;
			while (io >= 0) {
				if (opstack[io] != '(' && opstack[io] != '[') {
					output.push_back(opstack[io]);
					output.push_back(' ');
					opstack.pop_back();
				}
				else {
					cerr << "Eroare parantezele nu se potrivesc" << endl;
					return nullptr;
				}

				io--;
			}
		}

	}
	else {
		cerr << "Parser-ul nu contine nimic momentan" << endl;
		return nullptr;
	}
	if (numar_numere == numar_operatori + 1)
	{
		char* result = new char[output.length()];
		for (i = 0; i < output.length(); i++)
			result[i] = output[i];
		result[i] = '\0';
		return result;
	}
	else {
		cerr << "Expresie infix invalida" << endl;
		return nullptr;
	}

}

StringParser::operator string() {
	string aux(this->sir);
	return aux;
}

bool StringParser::operator==(StringParser& sp) {
	if (this == &sp) {
		return true;
	}
	return strcmp(this->sir, sp.sir) == 0;
}