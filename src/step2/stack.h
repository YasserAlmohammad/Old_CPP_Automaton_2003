// STACK.H
// Definition of class Stack for the parser section
#ifndef STACK_H
#define STACK_H

#include <iostream.h>
#include <assert.h>


class SNode{
public:
	SNode();
	SNode(char,int);
	friend ostream& operator<<(ostream&,SNode);
	char symbol;
	int state;
	SNode* next;
};


SNode::SNode(){ symbol='Z';  state=-2; next=0;}

SNode::SNode(char sym,int st){
	symbol=sym;    
	state=st;
	next=0;

}

ostream& operator<<(ostream& out,SNode* n){
	if(n->symbol!='Z')
		out<<n->symbol;
	else
		if(n->state!=-2)
			out<<n->state;
		else
			out<<n->symbol;
	return out;
}

class Stack {
public:
   Stack();					 // default constructor
   ~Stack();				 // destructor
   void push(int);			 // insert state in stack
   void push(char);			 // insert symbol
   void pop();					// remove item from stack
   int isEmpty() const;		// is the stack empty?
   void print() const;		// output the stack
   SNode gettop();
private:
   SNode *topPtr;	// pointer to fist StackSNode
};



// Member function definitions for class Stack

Stack::Stack() { topPtr = 0; }


Stack::~Stack(){
   SNode *tempPtr, *currentPtr = topPtr;

   while (currentPtr != 0) {
      tempPtr = currentPtr;
      currentPtr = currentPtr->next;
      delete tempPtr;
   }
}


void Stack::push(int st){
   SNode *newSNode = new SNode('Z',st);
   newSNode->next=topPtr; 	
   assert(newSNode != 0);  // was memory allocated?
   topPtr = newSNode;
}


void Stack::push(char sym){
   SNode *newSNode = new SNode(sym,-2);
   newSNode->next=topPtr; 	
   assert(newSNode!= 0);  // was memory allocated?
   topPtr = newSNode;
}


void Stack::pop(){
	if(!isEmpty()){
	   SNode *tempPtr = topPtr;
       topPtr = topPtr->next;
	   delete tempPtr;
 	}
}


SNode Stack::gettop(){
	SNode r(topPtr->symbol,topPtr->state);
	return r;
}


int Stack::isEmpty() const { return topPtr == 0; }


void Stack::print() const{
   SNode *currentPtr = topPtr;

   if (isEmpty())          // Stack is empty
      cout << "Stack is empty" << endl;
   else {                  // Stack is not empty
      cout << "The stack is:" << endl;

      while (currentPtr != 0){ 
         cout << currentPtr<<"   ";
		 currentPtr=currentPtr->next;
	  }
      cout<<endl;
   }
}

#endif

