/*Token.h
this is one token, we made it as a class to make sure it defines
the getHashCode() method so it can be used by the hash table
it's data members are public to ease other operations and to 
decrease it's complexity to the menimum
*/

#ifndef TOKEN_H
#define TOKEN_H

#include <iostream.h>
#include <string.h>
#include <iomanip.h>

class Token{
public:
	Token(); //constructs empty object
	Token(char,const char*,int);  //type, name, value
	//overloaded operators for flexibility and for the hashtable
	friend ostream& operator<<(ostream&,Token);
	void operator=(const Token&); 
	int operator==(const Token&);
	void calculateHC();
	char getType(){return type;}; //extra code could be eliminated 
	char type; //the kind of the token can be a string in a future demands
	char* chvalue;
	int intvalue;
	int hashCode; //better to be saved for repeatitive calls
	void setchval(const char*);
	int getHashCode(){return hashCode;}

};

Token::Token(){
	type=' ';
	setchval("");
	intvalue=0;
	hashCode=-1;
	}

Token::Token(char t,const char* chval,int intval){  
	type=t;
	setchval(chval);
	intvalue=intval;
	calculateHC();
}

void Token::calculateHC(){ //after longtime test this function improved
	int h=0,i=1;	// a good randomization
	if(chvalue!=0){  
		int keylength=strlen(chvalue);
		h=128*(int)chvalue[0];
		while(i<keylength+1){ //i starts from 1
			h+=(int)chvalue[i];
			++i;
		} //hashcode=(128*first char)+ord(i): i=1..keylenght
	}
	hashCode=h;   
}

void Token::setchval(const char* v){
	if(v!=0){
		chvalue=new char[strlen(v)+1];
		strcpy(chvalue,v);
	}
}

//this is a friend function so the tokens can be printed using cout<<
ostream& operator<<(ostream& output,Token token){
	output<<setw(4)<<(char)token.type<<" "<<setw(8)<<token.chvalue<<" "<<setw(8)<<token.intvalue;
	return output;
}

//the assignment operator
void Token::operator=(const Token&const rside){
	hashCode=rside.hashCode;
	intvalue=rside.intvalue;
	setchval(rside.chvalue);
	type=rside.type;

}

//the equation test is neccessary for comparisions in the hash table
//methods like add,delete,search
int Token::operator ==(const Token& rside){
		if(strcmp(chvalue,rside.chvalue)==0)//if string equal then esle is too
			return 1;
		return 0;
}

#endif