#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

enum { BRACKETS1 = -1, BRACKETS2 = -2,  SPACE = 0, NUMBER = 1 , SYMBOL = 2 ,ERROR = 8887 };

struct Character {
	char word ;
	int number ; // 數字 
	int type ;   // 型別 
};


class Sort {
	
	private:
		Character *character;
		int Size ;
		
	public: 
		
		Sort( string computation ) ;
		int getSize();
		Character getCharacter(int position);
		bool Check_Is_Infix() ;
		Sort() {
			Size = 0 ;
		}
};

/*
Sort::Sort() {
	Size = 0;
}
*/
 
bool Sort::Check_Is_Infix() {
	
	for ( int i = 0; i < Size ; i++ ) {
		if ( ( character[i].type == ERROR ) ) {
			cout << "Error 1: "<<character[i].word<<"is not a legitimate character.\n";
			return false;
		}
	}
	int CheckBrackets = 0;
	for ( int i = 0; i < Size ; i++ ) {          // 是否有上下括號 
		if (character[i].type == BRACKETS1)
			CheckBrackets++;
		else if (character[i].type == BRACKETS2)
			CheckBrackets--;
	}
	
	if ( CheckBrackets != 0 ) {
		cout << "Error 2: "<<"there is one extra close parenthesis.\n";
		return false;
	}
	
	bool Continue = true;
	for ( int i = 0 , j = 1; i<Size && Continue ; i++) {
		if ( ( character[i].type == NUMBER) ) // j % NUMBER == 0 
			j++;
			for ( i=i; i<Size && character[i].type == NUMBER ; i++ ) ;
			
		if ( ( character[i].type == SYMBOL) ) // j % SYMBOL == 2 
			j++;
		else if ( character[i].type <=0 && character[i].type >= -2 );
		else if ( ( character[i].type == NUMBER ) );
		else
			Continue = false;
	}
	if ( !Continue ) {
		cout << "Error 3: "<<"there is one extra opearator.\n";
		return false;
	}
	return true;
}

Sort::Sort( string computation ) {
	Size = computation.size();
	character = new Character[Size];
	bool End = false;
	for ( int i = 0,j = 0; i < Size && !End ; i++, j++ ) {
		if ( computation.at(i) <= '9' && computation.at(i) >='0' ) {
				character[j].type = NUMBER;			
				character[j].number = 0;
				for ( i = i ; computation.at(i) <= '9' && computation.at(i) >= '0' && i < Size  ; i++ ) {
					character[i].word = computation.at(i);
					// character[j].number *= 10;
					character[j].number = character[j].number*10 + ( computation.at(i) -'0' ) ;
					if( i+1 >= Size )
						break;
					if( computation.at(i+1) > '9' || computation.at(i+1) < '0' )
						break;
				} 
					if ( i == Size - 1 ) {
						End = true;
					}
				/*	
				for ( int u = j, k = 0 ; k < i-u ; k++,j++) {
					character[j].number = character[u].number;
				}
				*/ 
				
		} 
		else if( computation.at(i) == '(' || computation.at(i) == ')' ) {
				character[i].word = computation.at(i);
				if( computation.at(i) == '(' )
					character[i].type = BRACKETS1;
				if( computation.at(i) == ')' )
					character[i].type = BRACKETS2;
		} 
		else if( computation.at(i) == '+' || computation.at(i) == '-' || computation.at(i) == '*' || computation.at(i) == '/' ) {
				character[i].word = computation.at(i);
				character[i].type = SYMBOL;
		} 
		else if( computation.at(i) == ' ' ){
			character[i].word = computation.at(i);
			character[i].type = SPACE;
		} 
		else {
			character[i].word = computation.at(i);
			character[i].type = ERROR;
		}
		if( i+1 > Size)
			break;
	}
}

int Sort::getSize() {
	return Size;
}

Character Sort::getCharacter(int position){
	return character[position];
}

bool Menu (int command) {
	
	string input ;
    cout << "*** Path Finding ***" << endl;
	cout << "0. Quit             " << endl;
	cout << "1. Check it is Infix" << endl;
	cout << "2. Infix to postfix " << endl;
	cout << "********************" << endl;
	cout << "Input a command (0, 1, 2) : " ;
	cin >> command ;
	Sort *sort ;
	switch(command){
		case 0:
			return false;
			break;
		case 1:
			cout << "Enter the Infix: ";
			for(int i = 0;i<2;i++){
				getline( cin, input );
			}
			
			sort = new Sort(input);
			cout << "Input: " << input << endl ;
			
			if(sort->Check_Is_Infix())
				cout << "It is a legitimate infix expression.\n";
			return true;
			break;
		case 2:
			return true;
			break;
		default:
			cout << "Error : Not correct instruction, Please Enter new one.\n";
			return true;
			break;
	}
}

int main ( int argv, char *arg[] ) {
	int selection;
	while ( Menu( selection ) ) {
		cout<<endl;
		
	}
	
	cout << "Bye Bye~~";
	
}
