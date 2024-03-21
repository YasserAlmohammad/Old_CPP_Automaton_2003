/*Driver.h
this is the driver headerd file, it includes the implementation too
the driver calls the scanner for the next token and recieves the
token type and it's index in the hashTable, if the index=-1 this 
means the token won't be saved in the symols table
it stops the call as the scann returns -1
*/

#ifndef DRIVER_H
#define DRIVER_H

#include <iostream.h>
#include <iomanip.h>
#include "Token.h"
#include "HashTable.h"
#include "TScanner.h"

class Driver{
public:  
	Driver(){};//empty parameters, can be modified in future updates
	void scan(Scanner&,HashTable<Token>*);  //scan the scanner and show the results, temporaly 
};

// neither the scanner nor the symbols table are members here
//this gives this class limited options for now


void Driver::scan(Scanner& s,HashTable<Token>* symbolTable){
	ofstream output("output.txt",ios::out);
	int index=0;
	char type=' ';
	 
	cout<<" _______________________________"<<endl;
	cout<<"|    type | "<<" chValue |"<<" intValue |"<<endl;
	cout<<" -------------------------------"<<endl;
	
	output<<" ________________________________"<<endl;
	output<<"|    type | "<<" chValue |"<<" intValue |"<<endl;
	output<<" -------------------------------"<<endl;
	//output to te screen and another output to a file output.txt
	//this is better to save the output too
	
	while(s.getnext(type,index)==1){
		//index=-1 means the token was not added to //symbol table
		if(type!='0') //not an error
			if(index==-1){ //the token is not saved
				cout<<"|"<<setw(7)<<type<<"  |          |          |"<<endl;
				output<<"|"<<setw(7)<<type<<"  |          |          |"<<endl;
			}
			else{ //the token is a variable or number,it's saved
				cout<<"|"<<setw(8)<<type<<" ";
				cout<<"| "<<setw(8)<<(*symbolTable)[index].chvalue<<" ";
				cout<<"|"<<setw(8)<<(*symbolTable)[index].intvalue<<"  |"<<endl;
				
				output<<"|"<<setw(8)<<type<<" ";
				output<<"| "<<setw(8)<<(*symbolTable)[index].chvalue<<" ";
				output<<"|"<<setw(8)<<(*symbolTable)[index].intvalue<<"  |"<<endl;
				
			}
	}
	cout<<"|_________|__________|__________|\n"<<endl;
	output<<"|_________|__________|__________|\n"<<endl;
	
	output.close();
}


#endif