/*TScanner.h
  this is the scanner  class header, it's responsible for all input operations
  also it's responsible for input error handling
  it takes a file holds the program syntax for one cycle it returns the token type and
  it's index in the symbol table if it's a variable or number or returns
  -1 to indicate the token was not saved ..

  one major method is the getnext it reads from a file to a buffer then 
  it reads one token from the buffer and anayze it using the analyzeToken method
  when errors happen the later calls the analyze error.
  so these three methods are the hardcore

  there is an optional automatic error correction witch can be fired by the 
  user, by switching the checkErr value to 1

  errors will be saved to error.log file

*/

#ifndef TSCANNER_H
#define TSCANNER_H

#include <iostream.h>
#include <iomanip.h>
#include <string.h>
#include <fstream.h>
#include <ctype.h>
#include "Token.h"
#include "HashTable.h"

const int RWTsize=43; //reserved words hash table size
const int bufferSize=80;

class Scanner{
public:	
	Scanner(HashTable<Token>*);
	~Scanner();
	void startScanning(const char*);//initialize the file to begin scaning
	int getnext(char&,int&); //returns -1 if file ended
	//the parameters up will be changed inside the method
	void buildReservedWT();//long name but will be called once
	void addReservedW(char,const char*);//add one reserved word,type
	void printRWT();//print the reserved word table for test 
	void printST(){symbolsTab->print();} //print the symbols table for test
	HashTable<Token>* symbolsTab;//this was done just to make the 
	//scanner access the symbols Table without copying it or making
	//it private, this mean it can be used anywhere
	int strtoint(char*); //helper functions will be defined
	char* toLowerStrncpy(char*,int);
	void analyzeToken(char*,int,char&,int&); //see the implementation
	void analyzeErr(char* tokenbuf,int tbufsize,char& type,int& index); 
	int what(char); //the kind of character 
	void switchErrCheck(){checkErr=!checkErr;}//automatic error correction
	int fileOK; //the file status: 1 when the file is safely opened esle 0
	void viewErrLog(); //views the error.log file content

private:
	HashTable<Token>* reservedWT;
	/*the reserved words must
	  be stored in a hash table - for speed -to know if the token we have is 
   	  a reserved word or not so searching will be called freqently.
	  the Token class is suitable for saving a reserved  word as it
	  provides the getHashcode() method, this is better than making
	  new struct and recalculate the hashing code...
	*/
	ifstream file; //it's a text file contains the robogo program
	ofstream errLog; //the error.log file mentioned before
	char* buffer; //one line 
	int cursor; //0..80, when cursor==80 scanning moves to next line
	            //and it reinitialize again to 0 
				//so it begins with 80 to read a line for the first time
	int linelength;//the real space the holds text in the buffer
				   //it's frequently called so it's better to be saved
	int lineNum; //for error reports to provide the colomn and line
	             //where the error happened
	int checkErr; //0 don't repair, 1 repair recovable errors
};

Scanner::Scanner(HashTable<Token>* ST){ //initializations for members
	symbolsTab=ST;
	reservedWT=new HashTable<Token>(RWTsize);
	buffer=new char[bufferSize];
	cursor=80;
	linelength=0;
	lineNum=0;
	buildReservedWT();
}

Scanner::~Scanner(){
	delete reservedWT;
	delete [] buffer;
}

//add one reserved word to the reserved words table
void Scanner::addReservedW(char type,const char* chvalue){
	Token temp(type,chvalue,0);
	reservedWT->add(temp);
}

void Scanner::buildReservedWT(){ //we add the reserved words manually
	
	addReservedW('b',"begin");
	addReservedW('h',"halt");
	addReservedW('o',"obstacle");
	addReservedW('a',"add");
	addReservedW('t',"to");
	addReservedW('m',"move");
	addReservedW('n',"north");
	addReservedW('s',"south");
	addReservedW('e',"east");
	addReservedW('w',"west");
	addReservedW('r',"robot");
	addReservedW('d',"do");
	addReservedW('u',"until");
}

void Scanner::printRWT(){
	reservedWT->print();
}

//this is to initialize files and line number
//two files: the robogo program and the error.log
void Scanner::startScanning(const char* filename){
	file.open(filename,ios::in);
	if(!file)
		fileOK=0;//error file couldn't be opened or not found
	else
		fileOK=1;
	lineNum=0;
	errLog.open("error.log",ios::out);
}

/*this method is very effective one it doesn't use the strtok method
  but it uses a cursor for the current character read so the 
  manipulations are direct,
  this method calls another method to analyze a token just to make it
  more readable
*/
int Scanner::getnext(char& type,int&index){//type,chvalue are the return values
	if(file.eof()){
	
		if(cursor>=strlen(buffer)){
			type='-'; //end of the file return -1 to indicate that
			index=-1;
			file.close();
			errLog.close();
			return -1;
		}//here we need to continue manipulation tell all tokens of the 
		 //last file have been manipulated
	}
	if(cursor>=(linelength)){ //new line initializations
		lineNum++;
		cursor=0;  
		file.getline(buffer,80,'\n'); //reads one line from the program
		linelength=strlen(buffer);
	}
	//a buffer will be used to read one token char by char and later
	//to check the token for errors
	char tokenBuf[80]; //the worst case
	int tokenBufC=0; //token buffer chars count
	
	//the following block attempts to get a token which doesn't
	//starts with *- and doesn't contain tabs it's a pure token
	/***************************************************/
	if(cursor<linelength){
		while((cursor<linelength)&&((buffer[cursor]==' ')||(buffer[cursor]=='\t')))
			++cursor;  //all consequent spaces and tabs must be ignored
		if(cursor<(linelength-1))
			if((buffer[cursor]=='*')&&(buffer[1+cursor]=='-')){
				cursor+=2;
				if(cursor<(linelength-1))
					while((cursor<(linelength-1))&&(!((buffer[cursor]=='-')&&(buffer[1+cursor]=='*'))))
						cursor++;
						cursor+=2; //be careful here,it loops when find *- tell find -*
						   // or reach the end of line-1
			}  //here comments must be ignored
			
			//the first char is surely not space or tab because of the previous
			while((cursor<linelength)&&(buffer[cursor]!=' ')&&(buffer[cursor]!='\t')){
				tokenBuf[tokenBufC]=buffer[cursor];
				++cursor;
				++tokenBufC;
			} //now we got one token, it might contain errors
	}
	/***************************************************/
		analyzeToken(tokenBuf,tokenBufC,type,index);
	
	return 1;
}


//this method will analyze one token took from the main buffer it
//will check it for errors and return the data in the type and index
//this method will be called from inside getnext(...) 
void Scanner::analyzeToken(char* tokBuf,int tokBufSize,char& type,int &index){
	if(tokBufSize>0){
		if(tokBufSize>8){ //case1 long expression
				analyzeErr(tokBuf,tokBufSize,type,index);
				if(!checkErr)
					errLog<<"error: token with variable greater than 8 at line:"<<lineNum<<",col:"<<cursor-tokBufSize+1<<endl;
			}
			else{
				if((tokBufSize==1)&&((what(tokBuf[0])==2)||(what(tokBuf[0])==-1))){ //notation mark
					if(what(tokBuf[0])==2){ //2 can be replaced with a universal const
						type=tokBuf[0];
						index=-1;
						return;
					}
					else{ //illegal charachter
							errLog<<"error: illegal character at line:"<<lineNum<<",col:"<<cursor-tokBufSize+1<<endl;
							type='0'; index=-1; //this return parameters indicates error
					}
				}
				else{ 
					int numeric=1,ok=1;
					char* temp=toLowerStrncpy(tokBuf,tokBufSize); //lower case 
					for(int i=0;i<tokBufSize;i++){
						if(('a'<=temp[i])&&(temp[i]<='z')) 
							numeric=0; //this mean the token is not a numeric data
						else
							if(!((temp[i]<='9')&&(temp[i]>='0')))
								ok=0; //not numeric,not alphapetic
							    //this is illegal char: error case
					}
					
					if(ok){ //pure token with acceptable chars
						if(numeric==0){
							if(('0'<=temp[0])&&(temp[0]<='9')){
								errLog<<"error: illegal begining of variable at line:"<<lineNum<<",col:"<<cursor-tokBufSize+1<<endl;
								type='0'; //error case
								//variable starts with number
								index=-1;
							}
							else	
							{ //acceptable case variable
								Token var('v',temp,0);
								int pos;
								//search first the reserved words table, if not
								//found add it to the symbols table
								if((pos=reservedWT->search(var))==-1){
									index=symbolsTab->add(var);
									type='v';
									return;
								}//first check if it's a reserved word
								else{ //it's areserved word
									type=(*reservedWT)[pos].getType();
									index=-1;
									return;
								}
							}
							
						}
						else{ //a numeric data will be saved, we save it's int value
							Token num('i',temp,strtoint(temp));
							index=symbolsTab->add(num);
							type='i';
							
						}
					}
					else{ //token cotains notation marks: ; < =
						analyzeErr(temp,tokBufSize,type,index);
						if(!checkErr)
							errLog<<"error: illegal expression at line:"<<lineNum<<",col:"<<cursor-tokBufSize<<endl;
					}
	
				}
					
			}
	}
	else{
		type='0'; //empty token case
		index=-1;
	}

}

/*if the chechErr is 1 this method will findout if there is a recovable
  concatenations and correct them, it will print warrning messages when
  resolving a concatenation.
  it works as the following: take the first character, detect it's kind
		and loop as the following character belongs to the same kind
		when it stops it tests if the token(pure kind) we got is greater
		than eight if true it returns error else it returns wrrning message
		and decrease the cursor steps not used, and handle it as a correct
		token
  the cursor will change inside, it will become lass than it's old value
  for sure.  

*/
void Scanner::analyzeErr(char* tokenbuf,int tbufsize,char& type,int& index){
	if(checkErr){ //automatic error checking is on	
		int beginChar=what(tokenbuf[0]);
		int i=1;
		while((i<tbufsize)&&(what(tokenbuf[i])==beginChar))
			i++; //characters of the same type

		if(i>8){ //unrecovable error
				errLog<<"error: token with variable greater than 8 at line:"<<lineNum<<",col:"<<cursor-tbufsize+1<<endl;
				cursor=cursor-tbufsize+i; //move cursor back may be he can find more tokens
				type='0';
				index=-1;
				return;
		}

		char* chval=toLowerStrncpy(tokenbuf,i);
		cursor=cursor-tbufsize+i;
		
		switch (beginChar){
		//0 means token content is alphapetical characters
		case 0:{ //this { is neccessary for var bellow to be deifned
			errLog<<"warning: recovable concatenation has been detected and corrected at("<<lineNum<<","<<cursor<<")"<<endl;
			Token var('v',chval,0);
			int pos;
			if((pos=reservedWT->search(var))==-1){
				index=symbolsTab->add(var);
				type='v';
				
			}//first check if it's a reserved word
			else{ //it's areserved word
				type=(*reservedWT)[pos].getType();
			index=-1;		
				}}
			break;
		case 1:{ //numeric was excluded
			errLog<<"warning: recovable concatenation has been detected and corrected at("<<lineNum<<","<<cursor<<")"<<endl;
			Token num('i',chval,strtoint(chval));
			index=symbolsTab->add(num);
			type='i';
			   }
			break;
		case 2: //; > = it's a mark
			errLog<<"warning: recovable concatenation has been detected and corrected at("<<lineNum<<","<<cursor<<")"<<endl;
			type=chval[0];
			index=-1;
			cursor=cursor-i+1; //the first mark is a token here
			break;
		default: //illegal character at the begining
			errLog<<"error: illegal character at line:"<<lineNum<<",col:"<<cursor-tbufsize+1<<endl;
			type='0';
			index=-1;
		}
		delete [] chval;
	}
	else{ 
		type='0';
		index=-1;
	}
	

}

//helper function string to integer
int Scanner::strtoint(char* str){
	int result=0,length=strlen(str);
	for(int i=0;i<length;i++)
		result=result*10+(int)str[i]-(int)'0';
	return result;
}

//char* to lower case char*
char* Scanner::toLowerStrncpy(char * input,int length){ //use strncpy
	char* output=new char[length+1];
	for(int i=0;i<length;i++)
		output[i]=tolower(input[i]);
	output[length]='\0';
	return output;
}


int Scanner::what(char c){ //tells what is the char c:alphapit,numeric..
	if((('a'<=c)&&(c<='z'))||(('A'<=c)&&(c<='Z')))
		return 0;  //alphabetical 
	if(('0'<=c)&&(c<='9'))
		return 1;
	if((c==';')||(c=='=')||(c=='>')) //you may want to use a hashtable
		return 2;					// for notation marks, incase upagarading
	return -1; //error char
}
	
//view the errfile content
void Scanner::viewErrLog(){
	ifstream errfile("error.log",ios::nocreate);
	char buf[bufferSize];
	while(!errfile.eof()){
		errfile.getline(buf,bufferSize,'\n');
		cout<<buf<<endl;
	}
	errfile.close();
}

#endif


