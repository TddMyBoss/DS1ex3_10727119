// 10727119 吳恩賜 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

enum { BRACKETS1 = -1, BRACKETS2 = -2,  SPACE = 0, NUMBER = 1 , SYMBOL = 2 ,ERROR = 8887 };

struct Node {
  char character ;
  int number ;
  int category ;
  struct Node * next ; 
  struct Node * previous ;
} ;

struct Character {
 char word ;
 int number ; // ?詨? 
 int type ;   // ? 
} ;

class Sort {
 
 private:
  Character *character;
  int Size ;
  Node *node ;
  Node *Postfix ;
  
 public:

  Sort( string computation ) ;
  int getSize() ;
  Character getCharacter(int position) ;
  void Back() ;
  void MissionTwo() ;
        int level(char symbol) ;
  bool Check_Is_Infix() ;
  Sort() {
  
  }
};


bool Sort::Check_Is_Infix() {
 
 for ( int i = 0; i < Size ; i++ ) {
  if ( character[i].type == ERROR ) {
   cout << "Error 1: "<<character[i].word<<"is not a legitimate character.\n";
   return false;
  }
 }
 int CheckBrackets = 0 ;
 int x ; // ?斗銝??血銝?? 
 for ( int i = 0; i < Size ; i++ ) {          // ?臬??銝??
  if ( character[i].type == BRACKETS1 ) { 
      x = i ; 
   CheckBrackets++;
  } 
  else if ( character[i].type == BRACKETS2 && i > x )
   CheckBrackets-- ;
 }
 
 if ( CheckBrackets != 0 ) {
  cout << "Error 2: "<<"there is one extra close parenthesis.\n";
  return false;
 }
 
 bool Continue = true ;
 int Number = 0 ;
 int Symbol = 0 ;
 for ( int i = 0 ; i < Size && Continue ; i++ ) {
  if ( character[i].type == NUMBER ) {
   
   for ( i=i; i < Size && character[i].type == NUMBER ; i++ ) {            // ?詨? 
   }
   Number++ ;
     }
  if ( character[i].type == SYMBOL ) {
      Symbol++ ;
     }
  else if ( character[i].type <= 0 && character[i].type >= -2 ) {          // ?亦?祈??征??
  }
  else if ( character[i].type == NUMBER ) {
   
   for ( i=i; i < Size && character[i].type == NUMBER ; i++ ) {            // ?詨? 
   }
   Number++ ;
  }
  else
   Continue = false ;
 }
 
 if ( Symbol >= Number )
     Continue = false ;
 else
     Continue = true ;

 if ( !Continue ) {
  cout << "Error 3: "<<"there is one extra opearator.\n";
  return false;
 }
 return true;
}

Sort::Sort( string computation ) {
 Size = computation.size();
 character = new Character[Size];
 bool End = false ;
 for ( int i = 0,j = 0; i < Size && !End ; i++, j++ ) {
  if ( computation.at(i) <= '9' && computation.at(i) >= '0' ) {
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
    
  } 
  else if( computation.at(i) == '(' || computation.at(i) == ')' ) {
    character[i].word = computation.at(i);
    if( computation.at(i) == '(' )
     character[i].type = BRACKETS1;
    if( computation.at(i) == ')' )
     character[i].type = BRACKETS2;
  } 
  else if( computation.at(i) == '+' || computation.at(i) == '-' || computation.at(i) == '*' || computation.at(i) == '/' ) {
    character[i].word = computation.at(i) ;
    character[i].type = SYMBOL ;
  } 
  else if( computation.at(i) == ' ' ) {
   character[i].word = computation.at(i) ;
   character[i].type = SPACE ;
  } 
  else {
   character[i].word = computation.at(i) ;
   character[i].type = ERROR ;
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

int Sort::level(char symbol) {
 if ( symbol == '*' || symbol == '/' )
  return 2 ;
 else if( symbol == '+' || symbol == '-' )
  return 1 ;
 else 
  return 0 ;
}

void Sort::MissionTwo() {
 
 Postfix = new Node() ;
 node = new Node();
 for(int i =0;i<Size ;i++){
  node->character = character[i].word;
  node->category = character[i].type;
  node->number = character[i].number;
  node->next = new Node();
  node->next->previous = node;
  node = node->next;
 }
 int tempCurrentPosition = 0;
 char temp[Size] ={'\0'};
 Back();
 while(1) {
  if( node->category == BRACKETS1 ) { // (
   tempCurrentPosition++;
   temp[tempCurrentPosition] = '(';
  } // if
  else if ( node->category == BRACKETS2 ) { // )
   while(temp[tempCurrentPosition] != '(') {
    Postfix->character = temp[tempCurrentPosition];
    Postfix->category = SYMBOL;
    Postfix->next = new Node();
    Postfix->next->previous = Postfix;
    Postfix = Postfix->next;
    tempCurrentPosition--;
   } // while
   
   tempCurrentPosition--;
  } // else if
  
  else if ( node->category == NUMBER ) { // 1~9
   Postfix->number = node->number;
   Postfix->category = node->category;
   Postfix->next = new Node();
   Postfix->next->previous = Postfix;
   Postfix = Postfix->next;
  } // else if
  
  else if ( node->category == SYMBOL ) { // +-*/
  
   while(level(temp[tempCurrentPosition])>=level(node->character)) {
    Postfix->character = temp[tempCurrentPosition];
    Postfix->category = SYMBOL ;
    Postfix->next = new Node();
    Postfix->next->previous = Postfix;
    Postfix = Postfix->next;
    tempCurrentPosition--;
   } // while
   
   tempCurrentPosition++;
   temp[tempCurrentPosition] = node->character;
  } // else if
   
  if( node == NULL||node->next == NULL)
   break;
  else
   node = node->next;
 } // while
 
 while(tempCurrentPosition>0) {
  Postfix->character = temp[tempCurrentPosition] ;
  Postfix->category = SYMBOL ;
  Postfix->next = new Node() ;
  Postfix->next->previous = Postfix ;
  Postfix = Postfix->next ;
  tempCurrentPosition-- ;
 } // while
 
 Back() ;
 while(Postfix->previous!=NULL)
  Postfix=Postfix->previous;
 
 cout<<"Postfix expression: ";
 while(Postfix!=NULL&&Postfix->next!=NULL) {
  if(Postfix->category == SYMBOL)
   cout<<Postfix->character;
  else if(Postfix->category == NUMBER)
   cout<<Postfix->number;
  
  if(Postfix->next != NULL && (Postfix->next->category ==1||Postfix->next->category ==2))
   cout<<",";
  
  Postfix = Postfix->next; 
 }
}

void Sort::Back() {
 while( node!=NULL&&node->previous != NULL )
  node = node->previous;
}


bool Menu ( int command ) {

 string input ;
    cout << "*** Path Finding ***" << endl ;
 cout << "0. Quit             " << endl ;
 cout << "1. Check it is Infix" << endl ;
 cout << "2. Infix to postfix " << endl ;
 cout << "********************" << endl ;
 cout << "Input a command (0, 1, 2) : " ;
 cin >> command ;
 Sort *sort ;
 switch(command) {
  case 0:
   return false ;
   break ;
  case 1:
   cout << "Enter the Infix: " ;
   for( int i = 0; i<2 ; i++ ) {
    getline( cin, input ) ;
   }
   
   sort = new Sort(input) ;
   cout << "Input: " << input << endl ;
   
   if ( sort->Check_Is_Infix() )
    cout << "It is a legitimate infix expression.\n" ;
   
   return true ;
   break ;
  case 2:
   cout << "Enter the Infix: " ;
   for( int i = 0; i<2 ; i++ ) {
    getline( cin, input ) ;
   }
   
   sort = new Sort(input) ;
   cout << "Input: " << input << endl ;
   
   if ( sort->Check_Is_Infix() ) {

    sort->MissionTwo() ;
              
      }
   return true ;
   break ;
  default:
   cout << "Error : Not correct instruction, Please Enter new one.\n" ;
   return true ;
   break ;
 }
}

int main ( int argv, char *arg[] ) {
	int number ;
	while ( Menu( number ) ) {
		cout<<endl;
		
	}
	
	cout << "Bye Bye~~";
	
}
