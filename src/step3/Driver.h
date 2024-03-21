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
#include "STstack.h"

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
	Stack stack;     //stack for the parser
	RStack rStack;   //a stack for rules
	entry cell;
	STStack ststack; //the syntax tree stack

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
			
				stack.push(type,index);
				state=cell.val;
				stack.push(state);


				if(j==1){
					cout<<"error"<<endl;
					error=1;
				}
				if(s.getnext(type,index)==-1)
					++j;
				if((state==2)&&(type='i'))  //the b i i L h  case is special in the syntax tree
					ststack.push("i",index,0,0,0);
				if((state==3)&&(type=='i'))
					ststack.push("i",index,0,0,0);
			}
			else{
				if(cell.action=='R'){
					int ruleSize=2*rules[cell.val].length;
					for(i=0;i<ruleSize;i++)
						index=stack.pop();  //restore the index 	
					rStack.push(rules[cell.val].name,rules[cell.val].shape); //used for printing only
					//build the sytax tree
				
					if(rules[cell.val].name=='P'){ //p--->b i i L h
						stNode* list=ststack.remove(),* h=ststack.remove(),*w=ststack.remove();
						ststack.push("begin",-1,h,w,list); //removing order is important
					}
					if(rules[cell.val].name=='L'){
					    if(cell.val==3){ //L--->LS;
						stNode* s=ststack.remove(),* l=ststack.remove();
						ststack.push("seq",-1,l,s,0);
						}
					}
					if(rules[cell.val].name=='T')
						ststack.push("T",index,0,0,0);
					if(rules[cell.val].name=='D')
						ststack.push("D",-1,0,0,0);
					if(rules[cell.val].name=='S'){
						if(cell.val==4){  //s-->r v T T
							stNode* t2=ststack.remove(),* t1=ststack.remove(),* var=new stNode;
							var->firstPtr=var->secondPtr=var->thirdPtr=var->next=0;
							var->index=index;   var->name="var";
							ststack.push("robot",-1,var,t1,t2);
							cout<<ststack.topPtr->firstPtr->name;
						}
						else
							if(cell.val==5){ // o T T
								stNode* t2=ststack.remove(),* t1=ststack.remove();
								ststack.push("obst",-1,t1,t2,0);

							}
							else
								if(cell.val==6){ //m v D T
									stNode* t=ststack.remove(),* d=ststack.remove(),* var=new stNode;
									var->firstPtr=var->secondPtr=var->thirdPtr=var->next=0;
									var->index=index;   var->name="var";
									ststack.push("move",-1,var,d,t);
								}
								else
									if(cell.val==7){ //a T t v
										stNode* var=new stNode,* t=ststack.remove();
										var->firstPtr=var->secondPtr=var->thirdPtr=var->next=0;
										var->index=index;   var->name="var";
										ststack.push("add",-1,t,var,0);
									}
									else
										if(cell.val==8){ //v = T
											stNode* t=ststack.remove(),* var=new stNode;
											var->firstPtr=var->secondPtr=var->thirdPtr=var->next=0;
											var->index=index;   var->name="var";
											ststack.push("asign",-1,var,t,0);
										}
										else
											if(cell.val==9){ //d L u T>T
												stNode* t2=ststack.remove(),* t1=ststack.remove(),
													    *l=ststack.remove();
												ststack.push("do",-1,l,t1,t2);
											}
					}
					
					

					
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

	if((!error)&&(ok)&&(type='-')){
		rStack.print();
		ststack.print();
	
	
	}	
	else
		cout<<"error"<<endl;
	
}


#endif