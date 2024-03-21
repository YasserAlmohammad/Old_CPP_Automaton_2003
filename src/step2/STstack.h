// STstack.h
// the syntax tree stack

#ifndef STSTACK_H
#define STSTACK_H

#include <iostream.h>
#include <assert.h>




struct stNode{
	char* name;
	int index; //for variables and integers
	stNode* firstPtr; //we'll use the same strucure for all kinds of instructions and variables
	stNode* secondPtr;//and acoorind to the name we'll know what we'll use
	stNode* thirdPtr;
	stNode* next;
};

void printTree(stNode*);



class STStack {
public:
   STStack();					 // default constructor
   void push(char*,int,stNode*,stNode*,stNode*);	  
   stNode* remove();					// remove item from stack and return it
   int isEmpty() const;		// is the stack empty?
   void print() const;		// output the stack
   stNode *topPtr;	// pointer to fist StackSNode
};



// Member function definitions for class Stack

STStack::STStack() { topPtr = 0; }




void STStack::push(char* n,int i,stNode* p1,stNode* p2,stNode* p3){
   stNode *newNode = new stNode;
   assert(newNode != 0);
   newNode->name=n;
   newNode->index=i;
   newNode->next=topPtr;
   newNode->firstPtr=p1;
   newNode->secondPtr=p2;
   newNode->thirdPtr=p3;
   
   topPtr = newNode;
}



stNode* STStack::remove(){
	if(!isEmpty()){
	   stNode *tempPtr = topPtr;
       topPtr = topPtr->next;
	   tempPtr->next=0;
	   return tempPtr;
 	}
	else
		return 0;
}



int STStack::isEmpty() const { return topPtr == 0; }


//to check to content
void printTree(stNode* node){
	if(node!=0){
		cout<<node->name<<"  ";
		printTree(node->firstPtr);
		printTree(node->secondPtr);
		printTree(node->thirdPtr);
	}
}


void STStack::print() const{
	stNode* tempPtr=topPtr;
	while(tempPtr!=0){
		printTree(tempPtr);
		tempPtr=tempPtr->next;
	}
}

#endif

