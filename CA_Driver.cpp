#include "HuffTree.h"
#include "HuffCode.h"
#include "MyCipher.h"



using namespace std;

int main()
{
	ifstream input;
	input.open( "file.txt" );  //  The input file
	INode* root = BuildTree(input);
	input.close();

	string code;
	HuffCode hc;
    hc.GenerateCodes(root, code);

	ofstream output;
	output.open("encodedFile.txt");

	input.open("file.txt");
	string encodedString = hc.encode(input);
	output << encodedString;
	output.close();
	input.close();

	cout << encodedString << endl;

	string decodedString;
	hc.decodeFromRoot(root, encodedString, decodedString);
	
	output.open("decodedFile.txt");
	output << decodedString;
	output.close();


	hc.compress(encodedString);

	input.open("compressedFile.txt");
	hc.decompress(input);
	input.close();


	input.open("decompressedFile.txt");
	string s1;
	input >> s1;
	string s2;
	hc.decodeFromRoot(root,s1, s2 );
	cout <<"\n\n\n" << s2 << endl;

	

	





	// Part Two
	input.open("file.txt");
	string text;
	char c;
	while(true) 
	{ if(input.eof()) break;
		input.get(c);
		if(c != ('\n'))
		{	
			text += c;
		}
	}
	cout << "shift ?\n" ;
	int myshift = 0 ;
	cin >> myshift ;
	transform ( text.begin( ) , text.end( ) , text.begin( ) , MyCipher( myshift ) ) ;
	output.open("encryptedFile.txt");
	output << text;
	output.close();

	system ("pause");
	return 0;
}