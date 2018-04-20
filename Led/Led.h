
#ifndef LED_H
#define LED_H


#include <iostream>
#include <string>
#include <list>
using std::cout;
using std::endl;
using std::string;

class Led{
private:
	int current;
	int last;
	std::list<string> buffer;
	int mode; //	1= input, 0  = command mode
	std::string filename;



public:
	//LED constructors

	Led(); //default constructor
	Led& operator=(const Led&); //Assignment
	Led(const string&);//, int current, int lastline conversion
	Led(const Led&); //  copy
	~Led(); //Destructor

	void hello();
	//Runner

	void run(); //runs the text editor


	//LED functions-list manipulators
	void a_append(int);
	void i_insert(int);
	void pop_range(int, int);
	void pop_one(int);
	void printrange(int, int);
	void printn(int, int);
	void change(int ad1, int ad2);
	void up(int);
	void down(int);
	void write(const string&);
	void printadd();
	void sync(const string&);//synch
	void replace(const string&, const string&, int, int);



	int append(string);// append new line to end of buffer; 
	//calls insert method giving line number as end of buffer 
	int insert(string, int);// insert new line at given line number.s
	void print();
	int getcurent(); //returns current position on the buffer-LED menthod
	int getlast(); //returns last position on the buffer
	void commandmenu();
	int size();
	void clear();
	bool isempty();
};
#endif // !LED_H
