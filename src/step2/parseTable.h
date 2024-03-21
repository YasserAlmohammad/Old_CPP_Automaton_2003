//parseTable.h
//the parse table class definition and implementation

#ifndef PARSETABLE_H
#define PARSETABLE_H

struct entry{
	char action;
	int val;
};

class ParseTab{
public:
	ParseTab();
	entry getEntry(int,char);
	

	entry table[41][24];

};

ParseTab::ParseTab(){
	
	//initiialize
	for(int i=0;i<41;i++)
		for(int j=0;j<24;j++){
			table[i][j].action='E';
			table[i][j].val=-1;
		}

	
	//fill data
	table[0][0].action='S';  table[0][0].val=2;
	table[0][19].action='M';  table[0][19].val=1;
	table[1][18].action='A';  table[1][18].val=-1;
	table[2][1].action='S';  table[2][1].val=3;
	table[3][1].action='S';  table[3][1].val=4;
	table[4][2].action='S';  table[4][2].val=9;
	table[4][3].action='S';  table[4][3].val=10;
	table[4][4].action='S';  table[4][4].val=7;
	table[4][5].action='S';  table[4][5].val=8;
	table[4][6].action='S';  table[4][6].val=12;
	table[4][7].action='S';  table[4][7].val=11;
	table[4][20].action='M';  table[4][20].val=5;
	table[4][21].action='M';  table[4][21].val=6;
	table[5][2].action='S';  table[5][2].val=9;
	table[5][3].action='S';  table[5][3].val=10;
	table[5][4].action='S';  table[5][4].val=7;
	table[5][5].action='S';  table[5][5].val=8;
	table[5][6].action='S';  table[5][6].val=12;
	table[5][7].action='S';  table[5][7].val=11;
	table[5][11].action='S';  table[5][11].val=13;
	table[5][21].action='M';  table[5][21].val=14;
	table[6][10].action='S';  table[6][10].val=15;
	table[7][7].action='S';  table[7][7].val=16;
	table[8][1].action='S';  table[8][1].val=19;
	table[8][7].action='S';  table[8][7].val=18;
	table[8][23].action='M';  table[8][23].val=17;
	table[9][7].action='S';  table[9][7].val=20;
	table[10][1].action='S';  table[10][1].val=19;
	table[10][7].action='S';  table[10][7].val=18;
	table[10][23].action='M';  table[10][23].val=21;
	table[11][8].action='S';  table[11][8].val=22;
	table[12][2].action='S';  table[12][2].val=9;
	table[12][3].action='S';  table[12][3].val=10;
	table[12][4].action='S';  table[12][4].val=7;
	table[12][5].action='S';  table[12][5].val=8;
	table[12][6].action='S';  table[12][6].val=12;
	table[12][7].action='S';  table[12][7].val=11;
	table[12][20].action='M';  table[12][20].val=23;
	table[12][21].action='M';  table[12][21].val=6;
	table[13][18].action='R';  table[13][18].val=1;
	table[14][10].action='S';  table[14][10].val=24;
	table[15][2].action='R';  table[15][2].val=2;
	table[15][3].action='R';  table[15][3].val=2;
	table[15][4].action='R';  table[15][4].val=2;
	table[15][5].action='R';  table[15][5].val=2;
	table[15][6].action='R';  table[15][6].val=2;
	table[15][7].action='R';  table[15][7].val=2;
	table[15][11].action='R';  table[15][11].val=2;
	table[15][13].action='R';  table[15][13].val=2;
	table[16][1].action='S';  table[16][1].val=19;
	table[16][7].action='S';  table[16][7].val=18;
	table[16][23].action='M';  table[16][23].val=25;
	table[17][1].action='S';  table[17][1].val=19;
	table[17][7].action='S';  table[17][7].val=18;
	table[17][23].action='M';  table[17][23].val=26;
	table[18][1].action='R';  table[18][1].val=10;
	table[18][7].action='R';  table[18][7].val=10;
	table[18][9].action='R';  table[18][9].val=10;
	table[18][10].action='R';  table[18][10].val=10;
	table[18][12].action='R';  table[18][12].val=10;
	table[19][1].action='R';  table[19][1].val=11;
	table[19][7].action='R';  table[19][7].val=11;
	table[19][9].action='R';  table[19][9].val=11;
	table[19][10].action='R';  table[19][10].val=11;
	table[19][12].action='R';  table[19][12].val=11;
	table[20][14].action='S';  table[20][14].val=28;
	table[20][15].action='S';  table[20][15].val=29;
	table[20][16].action='S';  table[20][16].val=30;
	table[20][17].action='S';  table[20][17].val=31;
	table[20][22].action='M';  table[20][22].val=27;
	table[21][12].action='S';  table[21][12].val=32;
	table[22][1].action='S';  table[22][1].val=19;
	table[22][7].action='S';  table[22][7].val=18;
	table[22][23].action='M';  table[22][23].val=33;
	table[23][2].action='S';  table[23][2].val=9;
	table[23][3].action='S';  table[23][3].val=10;
	table[23][4].action='S';  table[23][4].val=7;
	table[23][5].action='S';  table[23][5].val=8;
	table[23][6].action='S';  table[23][6].val=12;
	table[23][7].action='S';  table[23][7].val=11;
	table[23][13].action='S';  table[23][13].val=34;
	table[23][21].action='M';  table[23][21].val=14;
	table[24][2].action='R';  table[24][2].val=3;
	table[24][3].action='R';  table[24][3].val=3;
	table[24][4].action='R';  table[24][4].val=3;
	table[24][5].action='R';  table[24][5].val=3;
	table[24][6].action='R';  table[24][6].val=3;
	table[24][7].action='R';  table[24][7].val=3;
	table[24][11].action='R';  table[24][11].val=3;
	table[24][13].action='R';  table[24][13].val=3;
	table[25][1].action='S';  table[25][1].val=19;
	table[25][7].action='S';  table[25][7].val=18;
	table[25][23].action='M';  table[25][23].val=35;
	table[26][10].action='R';  table[26][10].val=5;
	table[27][1].action='S';  table[27][1].val=19;
	table[27][7].action='S';  table[27][7].val=18;
	table[27][23].action='M';  table[27][23].val=36;
	table[28][1].action='R';  table[28][1].val=12;
	table[28][7].action='R';  table[28][7].val=12;
	table[29][1].action='R';  table[29][1].val=13;
	table[29][7].action='R';  table[29][7].val=13;
	table[30][1].action='R';  table[30][1].val=14;
	table[30][7].action='R';  table[30][7].val=14;
	table[31][1].action='R';  table[31][1].val=15;
	table[31][7].action='R';  table[31][7].val=15;
	table[32][7].action='S';  table[32][7].val=37;
	table[33][10].action='R';  table[33][10].val=8;
	table[34][1].action='S';  table[34][1].val=19;
	table[34][7].action='S';  table[34][7].val=18;
	table[34][23].action='M';  table[34][23].val=38;
	table[35][10].action='R';  table[35][10].val=4;
	table[36][10].action='R';  table[36][10].val=6;
	table[37][10].action='R';  table[37][10].val=7;
	table[38][9].action='S';  table[38][9].val=39;
	table[39][1].action='S';  table[39][1].val=19;
	table[39][7].action='S';  table[39][7].val=18;
	table[39][23].action='M';  table[39][23].val=40;
	table[40][10].action='R';  table[40][10].val=9;



}


entry ParseTab::getEntry(int line,char symbol){
	switch(symbol){
	case 'b': return table[line][0];  
	case 'i': return table[line][1];  
	case 'm': return table[line][2];  
	case 'a': return table[line][3];  
	case 'r': return table[line][4];   
	case 'o': return table[line][5];  
	case 'd': return table[line][6];  
	case 'v': return table[line][7];  
	case '=': return table[line][8];   
	case '>': return table[line][9];  
	case ';': return table[line][10]; 
	case 'h': return table[line][11];  
	case 't': return table[line][12];   
	case 'u': return table[line][13];   
	case 'n': return table[line][14];  
	case 's': return table[line][15];   
	case 'e': return table[line][16];  
	case 'w': return table[line][17];   
	case '-': return table[line][18];   
	case 'P': return table[line][19];   
	case 'L': return table[line][20];  
	case 'S': return table[line][21];   
	case 'D': return table[line][22];   
	case 'T': return table[line][23];  
	}
}


#endif