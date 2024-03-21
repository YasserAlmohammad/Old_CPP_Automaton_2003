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
#include "parseTable.h"
#include "rulesTable.h"
#include "stack.h"
#include "rulesStack.h"

class Driver{
public:  
	Driver(){};//empty parameters, can be modified in future updates
	void scan(Scanner&,HashTable<Token>*);  //scan the scanner and show the results, temporaly 
};

// neither the scanner nor the symbols table are members here
//this gives this class limited options for now


void Driver::scan(Scanner& s,HashTable<Token>* symbolTable){
	
	int index,state,i,error,ok,k,j;
	char type=' ';
	RulesTab rules;
	Stack stack;
	RStack rStack;
	entry cell;

	ParseTab parseTab;
	 
	ok=error=index=state=i=k=j=0;
	stack.push('Z'); 
	stack.push(state);      //push 0
	s.getnext(type,index);  //get the first symbol
	
	while((!error)&&(!ok)){
		k++;
		stack.print();
	
		if(type!='0'){ //not an error
		   
			cell=parseTab.getEntry(state,type);
			cout<<"the read symbol: "<<type<<endl; 
			if(cell.action=='S'){
			
				stack.push(type);
				state=cell.val;
				stack.push(state);
				if(j==1){
					cout<<"error"<<endl;
					error=1;
				}
				if(s.getnext(type,index)==-1)
					++j;
			}
			else{
				if(cell.action=='R'){
					int ruleSize=2*rules[cell.val].length;
					for(i=0;i<ruleSize;i++)
						stack.pop();
					rStack.push(rules[cell.val].name,rules[cell.val].shape);
					state=stack.gettop().state;
					stack.push(rules[cell.val].name);
					state=parseTab.getEntry(state,rules[cell.val].name).val;
					stack.push(state);
				}
				else{
					if(cell.action=='A'){
						cout<<"accepted"<<endl;
						ok=1;
					}
					else{
						cout<<"error"<<endl;
						error=1;
					}
				}
			}
			
		}
		else
			s.getnext(type,index);
	
			
	
	
	}

	if((!error)&&(ok)&&(type='-'))
		rStack.print();
	else
		cout<<"error"<<endl;
	
}


#endif