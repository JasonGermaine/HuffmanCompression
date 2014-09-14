#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

class MyCipher {
private : 
   int shift ;
public :
   MyCipher( int s ) : shift( s ) { } 
 
  char operator( )( char c ) 
  {
      if ( isspace( c ) ) 
	  {
		  return ' ' ;
	  }
      else 
	  {
		  static string letters( "abcdefghijklmnopqrstuvwxyz" ) ;
		  string::size_type found = letters.find(tolower( c )) ;
		 int shiftedpos = ( static_cast<int>( found ) + shift ) % 26 ;
		 char shifted = letters[shiftedpos] ;
		 return shifted ;
      }
  }
} ;