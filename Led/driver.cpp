//Driver program to test the LED class implemented in assignment 2

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
#include "Led.h"

int main(int argc, char *argv[])
{
	string filename ; //an empty filename
	switch (argc){
	case 1: // no file name
	break;
	case 2: filename =  argv[1];//initialize filename from argument
	break;
	default: cout << ("Too many arguments - all discarded") << endl;
	break;
	}
	Led led(filename); //create an editor named led
	led.run(); //run our editor
	return 0; //done
}