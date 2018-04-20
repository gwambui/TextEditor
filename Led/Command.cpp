
#include <iostream>
#include <string>
#include <regex>

using std::cout;
using std::endl;
using std::string;
#include "Command.h"
using std::ostream;
using namespace std;

//CONSTRUCTORS
//Command::Command(const char* st) :Command(st, 1, 1){};
//default constructor
Command::Command() :Command("", 1, 1){};

//assignment
Command& Command::operator=(const Command& st){

	//check for self-assignment
	if (this == &st) return *this;
	valid = false;
	this->rawcommand = st.rawcommand;
	this->current = st.current;
	this->last = st.last;
	this->parse();
	return *this;

}
Command::Command(const std::string& st, int current, int last)//) conversion
{
	valid = false;
	this->rawcommand = st;
	this->current = current;
	this->last = last;
	parse();


}

ostream&::operator<<(ostream& output, const Command & st){

	output << st.rawcommand;
	return output;
}


//parse function returns command as array of ints and a string for the command
//sets dots in integer spaces in command to current line
//sets dollar signs to last line
//eliminates spaces and tabs
void Command::parse(){

	//remove space
	//remove_if(str.begin(), str.end(), isspace);
	rawcommand.erase(remove_if(rawcommand.begin(), rawcommand.end(), isspace), rawcommand.end());

	//remove tabs
	rawcommand.erase(remove(rawcommand.begin(), rawcommand.end(), '\t'), rawcommand.end());

	if (rawcommand == ""){
		rawcommand = "1d";
	}
	if (rawcommand == "="){
		rawcommand = ".,.q";
	}
	// Default the command directly.
	//change command caps to lower if exist

	std::transform(rawcommand.begin(), rawcommand.end(), rawcommand.begin(), ::tolower);

	//Regex filter
	//std::regex e("([[:d:]]*|\\$|\\.)([,]{0,1})([[:d:]]*|\\$|\\.)([=airpncudwqel]?)");

	//+++++++++++++Regex documentation++++++++++++++++++++++++++//
	/*(\\$|\\.|[[:d:]]*)-------Accepts '$' or a '.' or a 'series of digits' or an 'empty character'. this segment represent the first address of the command object

	([,]{0,1})-------Accepts a single comma or an empty space. this represents the second member of the command object which separates the first and second address

	(\\$|\\.|[[:d:]]*)-----similar to first addresss and represents the second address of the command object

	([airpncudwqe]?)----- represents the action part of the command. Each character signifies a specific action to be performed on the buffer

	match----- separates the raw command into an array of 5 objects

	match[0]----The complete raw command
	match[1]----Address 1 on buffer to be executed
	match[2]----comma object if it exists determines the address range...separates address 1 and 2 otherwise all the digits are considered to be address 1
	match[3]----Address 2 on buffer to be executed. sets upper limit of range
	match[4]----contains command to be executed*/


	std::regex e("(\\$|\\.|[[:d:]]*)([,]{0,1})([[:d:]]*|\\$|\\.)([airpncudwqehmv]?)");

	std::cmatch match;


	std::regex_match(this->rawcommand.c_str(), match, e);
	if (match.size() != 0 && rawcommand != ".")
	{
		
		

		if (match.str(1) == ".")
		{

			this->address1 = current;
		}
		else if (match.str(1) == "$")
		{

			this->address1 = last;
		}

		else if (match.str(1).empty()){

			if (match.str(4) == "d" | match.str(4) == "u" | match.str(4) == "c"){ this->address1 = 1; }
			else{ this->address1 = current; }
		}
		else{ 
			this->address1 = stoi(match.str(1)); 
		}


		if (match.str(3) == "."){

			this->address2 = current;
		}

		else if (match.str(3) == "$")
		{

			this->address2 = last;
		}

		else if (match.str(3).empty()){

			this->address2 = address1;

			if (match.str(4) == "c" && match.str(1).empty()) {
				this->address2 = this->last;
			}
			
		}
		else
		{

			this->address2 = stoi(match.str(3));
		}



		if (match.str(4).empty())
		{
			this->action = "p";
			//if (match.str(3).empty()){
			//	this->address2 = address1;
			//}
		}
		else
		{
			this->action = match.str(4);
		}

		valid = true;
		//for (auto x:match){
		//std::cout << "[" << x << "]" ;
		//}
		if (address1 > address2){ swap(address1, address2); }

		cout << endl;
		cout << " current: " << current << endl
			<< " address1: " << address1 << endl
			<< " address2: " << address2 << endl;

	}
	else{
		valid = false;
		//cout << "Input is invalid" << endl  ;
		return;
	}
	//return match.str();

}


string Command::getraw()
{
	return this->rawcommand;
}
void Command::setraw(string& st)
{
	this->rawcommand = st;
}
int Command::getaddress1() //returns second address on the command
{
	return this->address1;
}
void Command::setaddress1(int address1)
{
	this->address1 = address1;
}
int Command::getaddress2() //returns second address on the command
{
	return this->address2;
}
void Command::setaddress2(int address2)
{
	this->address2 = address2;
}
string Command::getaction()
{
	return this->action;
}
void Command::setaction(string& st)
{
	this->action = st;
}
int Command::getcurrent() //returns second address on the command
{
	return this->current;
}
void Command::setcurrent(int current)
{
	this->current = current;
}
int Command::getlast() //returns second address on the command
{
	return this->last;
}
void Command::setlast(int last)
{
	this->last = last;
}
bool Command::isvalid(){
	return this->valid;
}



