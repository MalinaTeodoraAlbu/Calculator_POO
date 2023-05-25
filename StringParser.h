#pragma once
#include <iostream>
#include <string>
using namespace std;

class StringParser
{
private:
	char* sir;
public:
	StringParser();

	StringParser(const char* sir);

	StringParser(const StringParser& sp);

	StringParser& operator=(const StringParser& sp);

	~StringParser();

	char* getSir();

	void setSir(const char* sir);

	friend ostream& operator<<(ostream& out, const StringParser& sp);

	friend istream& operator>>(istream& in, StringParser& sp);

	static int getPrecedenta(char op); 

	string getAsociativitate(char op); 

	char* getSirRPN(); //reversed polish notation 

	bool operator==(StringParser& sp);

	operator string();
};

