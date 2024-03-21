/*mainProject.cpp
this file is the executable one, it uses all other classes 
to perform the program
*/
  
#include <iostream.h>
#include "HashTable.h"
#include "Token.h"
#include "TScanner.h"
#include "Driver.h"
#include <stdlib.h>


main(){
	int choice=0;
	char c='c';
	char filename[80];


	HashTable<Token>* symbolsTable=new HashTable<Token>;
	Scanner scanner(symbolsTable);
	Driver driver;
	cout<<"         _________________________________________________ \n";
	cout<<"        |                                                 |\n";
	cout<<"        | welcome to ROBOGO simulator interpreter program |\n";
	cout<<"        |_________________________________________________|\n";
	cout<<"                 |___________ LEVEL 1 ___________|    \n "<<endl; 

	do{
		cout<<"Press :\n";
		cout<<"1:           enter the file name you want to scan\n";
		cout<<"2:           switch ON/OFF automatic correction for recovable errors\n";
		cout<<"3:           view Error.log file content for the last interpreted program\n";
		cout<<"4:           interpret and maipulate your program\n";
		cout<<"5:           to get help on the program\n";
		cout<<"6:           Exit\n";
		cin>>choice;
		if(!cin.fail()){  //exception
			switch(choice){
			case 1: cout<<"input path:";
				cin>>filename;
				cout<<"now you can interpret your program "<<endl;
				break;
			case 2: scanner.switchErrCheck();
				break;
			case 3: scanner.viewErrLog();
	
				break;
			case 4:scanner.startScanning(filename);
				if(scanner.fileOK)
					driver.scan(scanner,symbolsTable);
				else
					cout<<"the file you choose couldn't be opened\n";
				break;
			case 5://for now simpilfied help, can be read from a file later
				cout<<"***** Welcome to ROBOGO interpreter help ***"<<endl;
				cout<<"first you must define the file which contains the program, you can"<<endl;
				cout<<"change it any time you want."<<endl;
				cout<<"after this you may want to interpret the program and view the results"<<endl;
				cout<<"the automatic error correction is ON by default you can turn it OFF "<<endl;
				cout<<"as for the errors it will be saved to error.log on the same directory the"<<endl;
				cout<<"the program is, you can veiw it's content in the screen too"<<endl;
				cout<<"as for the results it will be saved to output.txt file if you want to check"<<endl;
				cout<<"it later\n"<<"goodluck!"<<endl;
				symbolsTable->print();
				break;
			case 6: cout<<"you choose to exit the program"<<endl;
				break;
			default: cout<<"you entered incorrect choice try again\n";
		
			}
		}
		else{ cout<<"this is a bad choice my friend"<<endl;
			exit(1);
		}
	}while(choice!=6);

	delete symbolsTable; //what was created using new bust be deleted
	
	return 0;
}
