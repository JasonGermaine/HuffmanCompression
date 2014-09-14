/***************************************************************************************
*    Title: Huffman coding
*    Author: 
*    Date: 2014
*    Code version: 
*    Availability:http://rosettacode.org/wiki/Huffman_coding
*
***************************************************************************************/


#include "HuffTree.h"
#include <bitset>
using namespace std;

typedef map<char, string> HuffCodeMap;
class HuffCode
{
public:
	HuffCode();
	HuffCodeMap codes;
	void decodeFromRoot(const INode* root, string encodedString, string &decodedString);
	void GenerateCodes(const INode* node, const string code);
	string encode(ifstream& input);
	void compress(string);
	void decompress(ifstream& input);
private:
	void decode(const INode* root, const INode* node, string encodedString, string &decodedString);
};

HuffCode::HuffCode()
{
}

void HuffCode:: GenerateCodes(const INode* node, const string code)
{
    if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node))
    {
        codes[lf->c] = code;
		cout << code << " - " << lf->c << endl;
    }
    else if (const InternalNode* in = dynamic_cast<const InternalNode*>(node))
    {
        string leftCode = code;
		leftCode.append("0");
        GenerateCodes(in->left, leftCode);
 
        string rightCode = code;
        rightCode.append("1");
        GenerateCodes(in->right, rightCode);
    }
}

string HuffCode:: encode(ifstream& input)
{
	map<char, string>::iterator i_code = codes.begin();
	string encodedString;
	char c;

	while(input.get(c)) 
	{ 
		i_code = codes.find(c);
		encodedString.append(i_code->second);	
	}

	i_code = codes.find('^');
	encodedString.append(i_code->second);
	return encodedString;
}


void HuffCode:: decodeFromRoot(const INode* root, string encodedString, string &decodedString)
{
	const INode* node = root;
	if (const InternalNode* in = dynamic_cast<const InternalNode*>(node))
		{
			if(encodedString[0] == '0')
			{
				encodedString.erase(encodedString.begin());
				decode(root, in->left,encodedString, decodedString);
			}
			else
			{
				encodedString.erase(encodedString.begin());
				decode(root, in->right, encodedString, decodedString);
			}
		}
}
void HuffCode::decode(const INode* root, const INode* node, string encodedString, string &decodedString)
{
		if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node))
		{
			if(lf->c != '^')
			{
				decodedString += lf->c;
				decodeFromRoot(root, encodedString, decodedString);
			}
			
		}
		else if (const InternalNode* in = dynamic_cast<const InternalNode*>(node))
		{
			if(encodedString[0] == '0')
			{
				encodedString.erase(encodedString.begin());
				decode(root, in->left,encodedString, decodedString);
			}
			else
			{
				encodedString.erase(encodedString.begin());
				decode(root, in->right, encodedString, decodedString);
			}
		}
}


void HuffCode::compress(string encodedString)
{
	string chunk, compressed;
	unsigned long long decimal;
	ofstream output;
	output.open("compressedFile.txt");

	while(encodedString.size() > 0)
	{
		
		if(encodedString.size() >= 8)
		{
			chunk = encodedString.substr(0, 8);
			encodedString.erase(0, 8);
			decimal = bitset<8>(chunk).to_ullong();
			compressed = compressed + to_string(decimal) + " ";
		}

		else
		{
			int j = 8 - encodedString.size();
			for(int i = 0; i < j; i++)
			{
				encodedString += '0';
			}

			decimal = bitset<8>(encodedString).to_ullong();
			compressed += to_string(decimal);
			encodedString.erase(0, encodedString.size());
		}
		
	}
	
	output << compressed;
	output.close();
}

void HuffCode::decompress(ifstream& input)
{
	ofstream output;
	output.open("decompressedFile.txt");
	string decompressed;
	int chunk;
	while(input >> chunk)
	{
		bitset<8> bin(chunk);
		cout << bin;
		decompressed += bin.to_string();
	}

	output << decompressed;
	output.close();
}