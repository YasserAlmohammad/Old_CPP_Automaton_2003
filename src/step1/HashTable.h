/*HashTable.h
this is a general hash table that can be used with any class decendant
objects that defines the getHashCode() method so it takes the hashcode and use it 
in use it in the hashing function( hashcode differs from the index generated
by the hash function)
they must over load the ==,= operators and has a 
constructor with empty parameters
"the previous restrictions are neccessary and fare as an OOP model"
it uses the "open addressing" method
it encapsulates the add,delete and search methods 
also it uses the linear probing, in the future we will add the quadric and double test
it defines the rehashing method too.
this class is very elastic and can be used by any other program without
modifications

for preliminary type like int,float,double.. these types must be wrappered with
classes that defines the getHashCode() method

the default initial size of the table is 177, you can specify the size
by using the constructor HashTable<T>(int)

the hashTable rehashes it's content when the size is no longer enough
so the adding never fails

it can be modified in the future for more demands
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream.h>
#include <iomanip.h>

const int initialSize=177;

template <class T>
class HashTable{
	public:
		HashTable();  //hashtable with 177 elements as beginning
		HashTable(int); //user defines size for the hash table
		~HashTable(){delete [] table;}
		int add(const T&); //the element
		int search(const T&); //return -1 if not found else posiotion
		int deleteToken(T&);//returns -1 if notfound else posintion 
		int linearf(int hashcode,int i){return (hashcode+i)%size;}
		//the linear probing uses the hashcode in the function calculus
		void print();
		T& operator[](int index)const{return table[index];}
		//overloaded [] to get the element at the int index
		void rehash();

	private:
		T *table;
		int size;

};



//implementation for the hash table
//for now the implemenation will be in thee same place as the header
//of the template usage

template <class T> 

//defualt constructor with no arguments
HashTable<T>::HashTable(){ 
		size=initialSize; 
		T temp;//future enhancement: use the second
		table=new T[size];//constructor to build this one
		for(int i=0;i<size;i++)
			table[i]=temp;   
}

template <class T> 
//constructor with specified size for the hash table
HashTable<T>::HashTable(int s):size(s){
	table=new T[s];
	T temp;
	for(int i=0;i<s;i++)
		table[i]=temp;
}

template <class T> 
void HashTable<T>::print(){ //print elements
	for(int i=0;i<size;i++){
		cout<<"element "<<setw(4)<<i<<"= "<<table[i]<<endl;
	}
}

template<class T>
int HashTable<T>::add(const T& token){
	int i=0,pos,hashcode;
	T temp,t1=token;  //the last assignment is neccessary to avoid an
					  //error by a c++ compiler
	hashcode=t1.getHashCode();
	do{
		pos=linearf(hashcode,i);
		if(table[pos]==temp){ //this equals an empty index
			table[pos]=token;
			return pos;
		}		
		else
			if(table[pos]==token) //this makes sure one copy in saved
				return pos;
			else
				i=i+1;
	}while(i<size);
	rehash();
	add(token);//we rehash when the table is full then we add the same 
	           //token again so the adding never fails

}

template<class T>		
int HashTable<T>::search(const T& token ){
	int i=0,pos,hashcode;
	T t1=token;	hashcode=t1.getHashCode();
	do{
		pos=linearf(hashcode,i);
		if(table[pos]==token)
			return pos;
		else
			++i;
	}while(i<size);
	return -1;
}

//hint: for future updates you can use the hashcode member to store -2 indicating an
//element was deleted here in the hash table, this will enhance the
//search and add methods after one adjusting
template <class T>
int HashTable<T>::deleteToken(T& token){
	int i=0,pos,hashcode=token.getHashCode();
	T empty;  //naturally constructs initialized"emptied" object
	do{
		pos=linearf(hashcode,i);
		if(table[pos]==token){
			table[pos]=empty;
			return pos;
		}else
			++i;
	}while(i<size);
	return -1;  //token not found
}

template <class T>
void HashTable<T>::rehash(){
	int oldsize=size;
	size=size*2+1;  //multiple size
	T* newtable=new T[size];  //multiple table+1
	T temp;
	
	int i=0,pos,added=0;
	for(i;i<size;i++)
		newtable[i]=temp;  //initialize the new table

	//we must copy the old hashtable contents with the new hashing
	//parameters to the new table:this is the reahshing
	for(int j=0;j<oldsize;j++){  
		if(!(table[j]==temp)){
			i=0; added=0;
			do{
				//recalculate the index
				pos=linearf(table[j].getHashCode(),i); 
				if(newtable[pos]==temp){ //this equals an empty index
					newtable[pos]=table[j];
					added=1; //exit the do while loop
				}	
				else
					i=i+1;
			}while((i<oldsize)&&(!added));
		}

	}
	
	delete table; //free old memory
	table=newtable;
}	



#endif