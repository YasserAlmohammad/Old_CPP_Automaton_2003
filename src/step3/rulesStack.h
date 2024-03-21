// rulesStack.h

#ifndef RULESSTACK_H
#define RULESSTACK_H

#include <iostream.h>
#include <assert.h>


struct ruleNode{
	friend ostream& operator<<(ostream&,SNode);
	char name;
	char* rule;
	ruleNode* next;
};


class RStack {
public:
   RStack();					 // default constructor
   ~RStack();				 // destructor
   void push(char,char*);	  
   void pop();					// remove item from stack
   int isEmpty() const;		// is the stack empty?
   void print() const;		// output the stack
private:
   ruleNode *topPtr;	// pointer to fist StackSNode
};



// Member function definitions for class Stack

RStack::RStack() { topPtr = 0; }


RStack::~RStack(){
   ruleNode *tempPtr, *currentPtr = topPtr;

   while (currentPtr != 0) {
      tempPtr = currentPtr;
      currentPtr = currentPtr->next;
      delete tempPtr;
   }
}


void RStack::push(char n,char* shape){
   ruleNode *newNode = new ruleNode;
   newNode->name=n;
   newNode->rule=shape;
   newNode->next=topPtr; 	
   assert(newNode != 0);  // was memory allocated?
   topPtr = newNode;
}



void RStack::pop(){
	if(!isEmpty()){
	   ruleNode *tempPtr = topPtr;
       topPtr = topPtr->next;
	   delete tempPtr;
 	}
}



int RStack::isEmpty() const { return topPtr == 0; }


void RStack::print() const{
   ruleNode *currentPtr = topPtr;

   if (isEmpty())          // Stack is empty
      cout << "Stack is empty" << endl;
   else {                  // Stack is not empty
      cout << "The stack is:" << endl;

      while (currentPtr != 0){ 
         cout << currentPtr->name<<"-->"<<currentPtr->rule<<endl;
		 currentPtr=currentPtr->next;
	  }
      cout<<endl;
   }
}

#endif

