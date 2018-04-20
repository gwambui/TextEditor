#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>
using std::ostream;



class Command{



private:

	int address1;
	int address2;
	std::string action;
	std::string rawcommand;
	int position;
	std::string message;
	bool valid;
	int current;
	int last;
	int increment;

public: //CONSTRUCTORS
	//Command(const char*);
	Command(); //default constructor
	Command& operator=(const Command&); //Assignment
	Command(const std::string& st, int current, int lastline);//); conversion
	//Command(const Command&); //  copy
	friend ostream& operator<<(ostream& output, const Command& st);
	//getters and setters
	void parse(); //parse function returns command as string
	int getaddress1(); //returns first adress on the command
	int getaddress2(); //returns second address on the command
	string getaction();//returns command portion of raw command
	int getcurrent(); //returns current address on the buffer
	int getlast(); //returns last address on the buffer
	string getraw(); //returns raw command
	void setraw(string&);
	void setaddress1(int);
	void setaddress2(int);
	void setaction(string&);
	void setcurrent(int);
	void setlast(int);
	bool isvalid();


};












#endif // !COMMAND_H