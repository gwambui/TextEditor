#include <fstream>
#include <iostream>
#include <string>
#include "Led.h"
#include "Command.h"
#include <list>
#include<algorithm>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::list;
using namespace std;

//Constructors
//Command::Command() :Command("", 1, 1)
//Led::Led() : Led(){};

Led::~Led(){
	this->buffer.clear();
}
Led& Led::operator=(const Led& led){

	if (this == &led) return *this;
	this->current = led.current;
	this->last = led.last;
	this->mode = led.mode;
	this->buffer = led.buffer;

	return *this;

}
Led::Led(const Led&){} //  copy


Led::Led(const std::string& file) // conversion, int current, int lastline
{
	this->filename = file;
	this->current = 0;
	this->last = 0;
	this->mode = 0; //Command mode
	this->buffer = std::list<string>();

	hello();// Prints an introduction message	
	fstream myfile;
	myfile.open(filename, ios::in | ios::out);
	string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			this->append(line);
			this->current++;

		}

		this->last = buffer.size();
		//this->current= buffer.size();
		myfile.close();
	}
	else{
		cout << "Unable to open file. Empty buffer created" << endl << ":";
		this->append("");
		this->last = buffer.size();
		this->current = 1;
		this->filename = "";
	}
	//run();


}

void Led::run()
{

	while (this->mode == 0){

		cout << "        Welcome to the  command line" << endl
			<< "Please enter a command or 'e' to exit 'h' for help" << endl << ":";
		std::string input;
		std::getline(cin, input);

		Command command(input, this->current, this->last);

		//Loops to eliminate invalid commands
		while (!command.isvalid()){
			cout << "    The command entered is invalid." << endl
				<< "Enter a new command 'e' to exit 'h' for help" << endl;
			std::string newcommand;
			std::getline(cin, newcommand);
			command.setraw(newcommand);
			command.parse();


		}
		//action = command.action
		int ad1 = command.getaddress1();
		int ad2 = command.getaddress2();
		//char const* comm = command.getaction().c_str();
		char comm = command.getaction()[0];

		switch (comm)
		{
		case 'a':
			a_append(ad1);


			break;
		case 'i':
			this->i_insert(ad1);

			break;
		case 'r':
			if (ad1 == ad2){
				this->pop_one(ad1);
			}
			else{ this->pop_range(ad1, ad2); }


			break;
		case 'p':
			this->printrange(ad1, ad2);// print a range of the buffer

			break;
		case 'n':
			this->printn(ad1, ad2); //print buffer with line numbers

			break;
		case 'c':
			this->change(ad1,ad2);//replace substrings in the buffer

			break;
		case 'u':
			this->up(ad1);//move current address ip by specified number or 1 if not specified and print new current

			break;
		case 'd':
			this->down(ad1);//move current address dowb by specified number or 1 if not specified and print new current

			break;
		case 'w':
			this->write(filename); //synchronize buffer with file or create new file and write buffer. close file

			break;
		case 'q':
			this->printadd();//print current address 

			break;
		case 'h':
			this->commandmenu();//print current address 

			break;
		case 'm':
			this->clear();
		case 'v':
			this->print();
			break;
		case 'e':
			cout << "Exit LED? Y or N" << endl;//write buffer to file and exit Led object 
			char ans;
			cin >> ans;
			ans = tolower(ans);
			if (ans == 'y'){
				this->mode = 1;
				//this->write(filename);
				exit(EXIT_SUCCESS);
				break;
			}
			else{ break; }
		default:
			cout << "You entered: " << command.getraw() << endl// Bad command. request new command
				<< "This command is invalid" << endl;
			run();


		}

	}
}
//Introduction
void Led::hello(){


	cout << R"( 
        ___  _____  __  __  ____  ___   __  ___   __           
       / __)(  _  )(  \/  )(  _ \| __) /. |(__ \ /  )          
      ( (__  )(_)(  )    (  )___/|__ \(_  _)/ _/  )(           
       \___)(_____)(_/\/\_)(__)  (___/  (_)(____)(__)          
 __    ____  _  _  ____    ____  ____  ____  ____  _____  ____ 
(  )  (_  _)( \( )( ___)  ( ___)(  _ \(_  _)(_  _)(  _  )(  _ \
 )(__  _)(_  )  (  )__)    )__)  )(_) )_)(_   )(   )(_)(  )   /
(____)(____)(_)\_)(____)  (____)(____/(____) (__) (_____)(_)\_)
)" << endl << endl;

	cout << "\t Prepared by: \t Kinyanjui, Wambui J" << endl
		<< "\t\t  ID: \t 24600878" << endl<< endl
		<< "\t\t CONCORDIA UNIVERSITY " << endl << endl;
}
//The command menu
void Led::commandmenu(){

	cout << "		HERE ARE THE COMMAND EXAMPLES" << endl << endl;

	cout << "A single address or adress range can be included with each command" << endl << endl;

	cout << "Command example single line:	1c" << endl;

	cout << "Command example current line:	.,.c" << endl;

	cout << "Command example for range:	2,4c " << endl;

	cout << "Command example full buffer:	1,$c" << endl << endl;

	cout << "		HERE ARE THE COMMAND OPTIONS" << endl << endl;

	cout << "a - Appends new line after requested address or by default at end of buffer " << endl << endl;

	cout << "i - Inserts new line before requested address or by default at top of buffer" << endl << endl;

	cout << "r - Removes specific line or line range" << endl << endl;

	cout << "p - Prints the current line or indicated range" << endl << endl;

	cout << "n - Prints the current line or indicated range with line numbers" << endl << endl;

	cout << "c - Replaces specific text in the buffer lines with supplied text" << endl << endl;

	cout << "u - Offsets current address up by given value and not above first line " << endl << endl;

	cout << "d - Offsets current address down by given value and not below last line " << endl << endl;

	cout << "w - Writes buffer to associated text file of creates a " 
		<< endl << "\t new text file and exports buffer to file" << endl << endl;

	cout << "= - Prints the address of the current line" << endl << endl;

	cout << "e - Exits Led" << endl << endl;

	cout << "h - The trusted help menu, you can return here as many times as you like!!" << endl << endl;

	cout << "Enter - Same as 1d. Moves current line down by one." << endl << endl;

	cout << "m - Clears the screen" << endl << endl;

	cout << "v - Preview items in the buffer" << endl << endl;

}

// Led manupulator functions

void  Led::a_append(int a1){
	//What it does:
	//Switches to input mode, 
	//read input lines, 
	//append lines to buffer after line y 
	//set current line to last line endtered

	this->mode = 1;
	cout << endl << "          You are in input mode" << endl
		<< "Enter a line to be added into buffer '.' to exit" << endl;
	std::string input;
	//cin.get();
	int newcur = a1;
	//int c = cin.peek();
	string exitInput = "Exiting input mode";

	if (a1 < last){
		std::getline(cin, input);
		while (input != "."){
			this->insert(input, a1);
			std::getline(cin, input);
			++newcur;
		}this->current = newcur;
	}
	else
	{
		std::getline(cin, input);
		while (input != "."){
			newcur = this->append(input);
			std::getline(cin, input);
			this->current = newcur;
		}
	}
	print();
	cout << endl << "\t" << exitInput << endl;
	//this->current = newcur;
	mode = 0;
	//cout << "Buffer size =:" << newsize << endl;
	return;
}

void Led::i_insert(int a1){
	//What it does: 
	//switches to input mode
	//reads inout lines
	//inserts lines before line y
	//set current line to last line endtered

	this->mode = 1;
	cout << endl << "             You are in input mode" << endl
		<< "Enter a line to be added into buffer"
		<< endl << " or '.' to exit" << endl;
	std::string input;
	int newcur;

	string exitInput = "Exiting input mode";

	if (a1 == 1){

		std::getline(cin, input);
		while (input != "."){

			if (!input.empty()){
				buffer.push_front(input);
			}
			std::getline(cin, input);

			this->last = this->size();
		}
		this->current = a1;
	}
	else
	{
		std::getline(cin, input);
		while (input != "."){

			newcur = this->insert(input, a1 - 1);
			std::getline(cin, input);
			this->current = newcur;
		}

	}
	print();
	cout << endl << "\t" << exitInput << endl;
	mode = 0;
	//cout << "Buffer size =:" << newsize << endl;
	return;
}

void Led::pop_one(int a1)
{
	//What it does
	//removes one line from buffer
	//current line is line after removed if it exists
	//otherwise current is line before removed line
	if (this->size() >= a1){

		std::list<string>::iterator it1 = buffer.begin();
		advance(it1, a1 - 1);
		it1 = buffer.erase(it1);
		this->last = buffer.size();

		cout << "The buffer after removed line: " << endl << endl;

		//printn(1, this->getlast());
		print();
		this->current = a1 - 1;
		if (it1 != buffer.end()){ this->current = current++; }
		cout << "current: " << current;
		return;
	}
	else
	{
		cout << "Buffer is empty or address out of bounds." << endl;
		return;
	}

}

void  Led::pop_range(int a1, int a2){
	//What it does
	//Removes line range x to y
	//current line is line after removed range if exists
	//otherwise current is before removed range
	if (this->size() >= a2){


		std::list<string>::iterator it1 = buffer.begin();
		std::list<string>::iterator it2 = buffer.begin();
		advance(it1, a1 - 1);
		advance(it2, a2);
		it1 = buffer.erase(it1, it2);


		cout << "The buffer after removed lines: " << endl << endl;
		this->last = buffer.size();

		print();

		this->current = a1 - 1;
		if (it1 != buffer.end()){ this->current = current++; }

		//buffer items exist after removed range
		//otherwise removed range runs to the end of the buffer, current remains a1-1

		cout << "current:" << current << endl << endl;
	}
	else
	{
		cout << "Buffer is empty or address out of bounds." << endl;
	}
}

void  Led::printrange(int ad1, int ad2){
	//What it does
	//prints the line range x to y
	//current is set to last printed line
	if (this->size() < 1){
		cout << "Cannot print current line" << endl
			<< "The buffer is empty" << endl;
		return;
	}
	else{
		std::list<string>::iterator it1 = buffer.begin();

		for (int i = ad1 - 1; i <= ad2 - 1; ++i)
		{
			advance(it1, i);
			//string * k = &(*it);
			std::cout << " " << *it1 << endl;
			it1 = buffer.begin();
		}
		current = ad2;
		return;
	}
}
void  Led::printn(int ad1, int ad2){
	//What it does
	//Prints the line range x to y 
	//Adds line numbers and tab character to each line
	//current is set to last printed line
	std::list<string>::iterator it1 = buffer.begin();

	for (int i = ad1 - 1; i <= ad2 - 1; ++i)
	{
		advance(it1, i);
		//string * k = &(*it);
		std::cout << i + 1 << " \t -" << *it1 << endl;
		it1 = buffer.begin();
	}
	current = ad2;
	return;

}
void  Led::change(int ad1, int ad2){
	//What it does
	//Prompts for and reads the text to be changed
	//prompts for and reads replacement text
	//searches each addressed line for target string
	//changes all matched strings to replacement text
	if (buffer.empty()){
		cout << endl << "The buffer is currently empty"
			<< endl << "How about adding some lines first" << endl;
		return;
	}
	this->mode = 1;
	cout << "\t You are in input mode"<<endl
		<<"Enter text you wish to replace on the buffer" << endl
		<<"'.' to abort"<<endl;

	std::string oldtext;
	std::getline(cin, oldtext);
	cout << "Enter text to replace it with on the buffer" << endl
		<< "'.' to abort" << endl;

	std::string newtext;
	std::getline(cin, newtext);
	

	while (oldtext != "." && newtext != "."){

	
		if(!oldtext.empty() && !newtext.empty()){
			
			replace(oldtext, newtext,ad1,ad2);
			this->mode = 0;
			return;
		
			}
		else{
			cin.clear();
			cout << endl << "Text cannot be empty" << endl
				<< "Enter target text '.' to abort";
			std::getline(cin, oldtext);
			cout << endl << "Text cannot be empty" << endl
				<< "Enter new text '.' to abort";
			std::getline(cin, newtext);
		}
	

	}cout << "Replacement terminated" << endl;
	this->mode = 0;
	return;

}
void Led::replace(const string& oldtext, const string& newtext, int x, int y){

	std::list<string>::iterator it;
	it = this->buffer.begin();
	std::string search;
	std::size_t found;
	int count=0;

	//for (int i = 0; i < this->size(); ++i){
	for (int i = x - 1; i < y; ++i){

		string search = *it;
		found = search.find(oldtext);
		while (found != std::string::npos)
		{
			search.replace(found, oldtext.length(), newtext);
			found = search.find(oldtext, found + 1);
			count++;

		}
		*it = search;
		it = next(it);

	}cout << count << " Instances of " << oldtext << " have been replaced " << endl;
	return;
}
void  Led::up(int y){
	//What it does
	//Moves the current line up by y lines
	//but never beyond first line
	//prints new current line
	
	this->current = std::max(1, (this->current - y));
	std::list<string>::iterator it1 = buffer.begin();
	advance(it1, this->current);

	cout << this->current << "-" << *--it1 << endl;

}
void  Led::down(int y){
	//What it does
	//Moves the current line down by y lines
	//But never beyond the last line
	//Prints new current line

	this->current = std::min(this->size(), (this->current + y));
	std::list<string>::iterator it1 = buffer.begin();
	advance(it1, this->current);

	cout << this->current <<"-"<< *--it1 << endl;


}
void  Led::write(const string& file){
	//What it does
	//Writes out entire buffer to its associated file
	//if no file exists, it prompts for and reads the name of associated file to write

	//myfile.open(file);
	if (!file.empty())//Buffer already linked to a file

	{
		this->sync(file);


	}
	else{	//buffer not linked to a file
		if (this->isempty()){// no items added to buffer
			cout << endl << " Buffer is empty" << endl; return;
		}
		else
		{		// Items in buffer. Need to create new text f
			cout << endl << "The buffer is not linked to any file." << endl
				<< "Please provide a new file name as 'name.txt'" << endl << ":";

			bool validname = false;

			string newfile;
			std::getline(cin, newfile);
			if (newfile.length()>4 && newfile.substr(newfile.length() - 4, 4) == ".txt")
			{
				this->filename = newfile;
				validname = true;
				//this->sync(newfile);
			}
			cin.clear();
			//cin.ignore(10000, '\n');
			while (!validname)
			{
				cout << endl << "Please provide a valid file name as 'name.txt'" << endl << ":";
				std::getline(cin, newfile);
				//!newfile.empty()
				if (newfile.length() > 4 && newfile.substr(newfile.length() - 4, 4) == ".txt")
				{
					this->filename = newfile;
					validname = true;
					//this->sync(newfile);
				}
				cin.clear();
				//cin.ignore(10000, '\n');
			}
			this->sync(newfile);
		}
	}
}
void  Led::sync(const string& file){

	ofstream myfile(file);
	if (myfile.is_open()){
		std::list<string>::iterator it = buffer.begin();

		for (int i = 0; i < this->size(); ++i)
		{


			myfile << *it << endl;
			myfile.flush();
			it = next(it);
		}

		myfile.close();
		cout << endl << " File written and closed " << endl;

	}
	else{
		cout << endl << "Can't save on file " << file << endl;
	}


}


void  Led::printadd(){
	//What it does// this is response to command "="
	//Prints the address of the current line

	//if you want to print the pointer address
	/*std::list<string>::iterator it;
	it = buffer.begin();
	*it += this->getcurent();
	string * k = &(*it);
	//cout << k<<endl;*/


	if (this->size() < 1){
		cout << endl << "Cannot print current line" << endl
			<< "The buffer is empty" << endl;
		return;
	}
	else{
		std::cout << endl << "Current Address is: " << this->getcurent() << endl
			<< endl << "\t Resuming command mode" << endl<< endl;

		return;
	}
}

//Common functions//
int Led::append(string line)// append new line to end of buffer; calls insert method giving line number as end of buffer 
{
	//What it does
	//Appends new line to the end of buffer
	//current line is the new inserted line
	if (!line.empty()){
		buffer.push_back(line);
		this->last = buffer.size();

	}
	else{ return buffer.size(); }
	return buffer.size();

}
int Led::insert(string st, int n)// insert new line at given line number. sets current line to most recently affected line
{
	if (!st.empty()){
		std::list<string>::iterator it;
		it = buffer.begin();	// buffer input point;
		advance(it, n);

		buffer.insert(it, st);

		//print(buffer);
		this->last = this->size();
		return n;

	}
	else{ return n; }

}
void Led::print()
{
	std::list<string>::iterator it = buffer.begin();
	//for (it = buffer.begin(); it != buffer.end(); ++it)
	for (int i = 0; i < this->size(); ++i)
	{

		//string * k = &(*it);
		std::cout << i + 1 << " - " << *it << endl;
		it = next(it);
	}
	return;
}

//Getters and setters
int Led::getcurent() //returns current position-LED menthod
{
	return this->current;
}
int Led::getlast() //returns current position-LED menthod
{
	return this->last;
}
int Led::size()
{
	return buffer.size();
}
//e_command: erase/clear the screen
void Led::clear()
{
	cout << string(100, '\n');
}
bool Led::isempty()
{
	return this->buffer.empty();
}