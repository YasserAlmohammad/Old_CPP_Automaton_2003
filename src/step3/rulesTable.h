//rulesTabe.h
//we made aspecial table for the rules

#ifndef RULESTABLE_H
#define RULESTABLE_H

struct rule{
	char name;
	char* shape;
	int length;
};



/*
class Rule{
public:
	Rule();
	Rule(char,const char*,int);
	char name;
	char* shape;
	int length;
};

Rule::Rule(){
	Rule('Z',"Z",-2);
}

Rule::Rule(char n,const char* sh,int len){
	name=n;
	char* shape=new char[strlen(sh)+1];
	shape[strlen(sh)]='\0';
	shape=strcpy(shape,sh);
	length=len;
}
*/


class RulesTab{
public:
	RulesTab();
	rule& operator[](int index){return table[index];}
private:
	rule table[15];

};

RulesTab::RulesTab(){

	table[0].name='Z';    table[0].shape="Z";			 table[0].length=1;
	table[1].name='P';    table[1].shape="b i i L h";    table[1].length=5;
	table[2].name='L';    table[2].shape="S;";           table[2].length=2;
	table[3].name='L';    table[3].shape="LS;";          table[3].length=3;
	table[4].name='S';    table[4].shape="r v T T";      table[4].length=4;
	table[5].name='S';    table[5].shape="o T T";        table[5].length=3;
	table[6].name='S';    table[6].shape="m v D T";      table[6].length=4;
	table[7].name='S';    table[7].shape="a T t v";      table[7].length=4;
	table[8].name='S';    table[8].shape="v=T";			 table[8].length=3;
	table[9].name='S';    table[9].shape="d L u T>T";    table[9].length=6;
	table[10].name='T';    table[10].shape="v";			 table[10].length=1;
	table[11].name='T';   table[11].shape="i";			 table[11].length=1;
	table[12].name='D';   table[12].shape="n";			 table[12].length=1;
	table[13].name='D';   table[13].shape="s";			 table[13].length=1;
	table[14].name='D';   table[14].shape="e";			 table[14].length=1;
	table[15].name='D';   table[15].shape="w";			 table[15].length=1;

	
}






#endif