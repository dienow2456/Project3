#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include<fstream>


using namespace std;
const int STX =0x02 ,ETX = 0x03;
 	//put the last element of the string a[] to the beginning
void compareStrings(string &a) {
    char t=a[a.length() -1];
    for(int i=a.length() -1; i>0; i--){
    	a[i]=a[i-1];
		}
	a[0]=t;
}

 	// encoding
string bwt(const string &s) {
   for (int i=0; i<s.length() ; i++) {
        if (s[i] == STX||s[i]==ETX) printf("Input can't contain STX or ETX");
    }
    string ss;
	ss+=STX;
	ss+=s;
	ss+=ETX;
	vector<string> table;
	for(int i=0; i<ss.length() ;i++){
		table.push_back(ss);
		compareStrings(ss);
		}
    //table.sort();
    sort(table.begin(), table.end() );
    string out;
    for (size_t i=0;i<table.size();i++) {
        out += table[i][table.size()-1];
    }
    return out;
}
 	//decoding
string ibwt(const string &r) {
    int len = r.length();
    vector<string> table(len);
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            table[j] = r[j] + table[j];
        }
        sort(table.begin(), table.end());
    }
    string s="";
    s+=table[0];
    for(int i=0; i<s.length() ;i++){
    	if (s[i] == ETX) {
            return s.substr(1, s.length() - 2);
        }
    }
    return {};
}
 
string makePrintable(const string &s) {
	string ss="";
	ss+=s;
    for (int i=0; i<s.length() ; i++) {
        if (ss[i] == STX) ss[i] ='^';
        else if (ss[i] == ETX) ss[i] = '|';
    }
    return ss;
}
                                
int main() {
	//open the input file containing the information to be encoded
    string res;
    fstream f;
	f.open("input.txt", ios::in);
	string data;
	string line;
	while (!f.eof())
	{
		getline(f, line);
		data += line;
	}
    char* input_text = new char[data.size()+1];
	copy(data.begin(), data.end(), input_text);
	input_text[data.size()] = '\0';
    printf("%s\n", input_text);
    printf(" --> ");
    //burrows wheeler transform encoding
    res = bwt(input_text);
    //create output.txt file to contain encrypted code	
    fstream output("output.txt",ios::out);
    output<<makePrintable(res);
   	// decoding 
    output.close() ;
	cout << makePrintable(res) << "\n";
    string r=ibwt(res);
    cout << " --> " << r << "\n\n";
    return 0;
}
	
  
