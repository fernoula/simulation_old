#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdlib.h>
using namespace std;

int main(int argc, char **argv)
{
    string alouminum(argv[1]);//original filename
//    cout<<alouminum<<endl;
    
    vector<string> s2,s6,s8,s10;//will store keV/MeV (unneccessary)
    vector<double> s1,s3,s4,s5,s7,s9;//will store values to save.
    string keV="keV";//this is just here to utilize in comparisons;
    string um="um";
    string m="m";

    
    ifstream in(alouminum.c_str());//open in file
    string input/*temporary*/,Straggling="Straggling"/*for comparison*/,commentline/*to save comment line*/;
    //This while loop reads the crap before the actual data.
    while (in>>input)//This saves in input automatically. if EOF will kill it (will never EOF)
    {
        if (input==Straggling)//Check if "Straggling is reached.
        {
            in>>input;//Second Straggling
            in>>commentline;//save this for later.
            for (int i=0;i<5;i++) in>>input; //throw away the rest  --------
            break;//kill loop since we can start reading data.
        }
        input.clear();
    }
    //Reads the rest until it reaches  a line that begins with '-'
    while(!(in.eof()))
    {
        string str1, str2,str3, str4, str5;  //probably in>>str1 for all will work but meh.
        string str6, str7, str8, str9, str10;
	
        in>>str1;
        if (str1.c_str()[0]=='-') break;//This checks for end of file.
        
        s1.push_back(atof(str1.c_str()));
	
        in>>str2;    
        if(str2==keV)
            s1[s1.size()-1]/=1000.0;
        
        in>>str3;        
        s3.push_back(atof(str3.c_str()));
        
        in>>str4;       
        s4.push_back(atof(str4.c_str()));
	
        in>>str5;
	s5.push_back(atof(str5.c_str()));

	in>>str6;
	if(str6==um)
	  s5[s5.size()-1]/=1000.0;
	if(str6==m)
	  s5[s5.size()-1]*=1000.0;
	    	
        in>>str7;
	s7.push_back(atof(str7.c_str()));

	in>>str8;
	if(str8==um)
	  s7[s7.size()-1]/=1000.0;

        in>>str9;
	s9.push_back(atof(str9.c_str()));

	in>>str10;
	if(str10==um)
	  s9[s9.size()-1]/=1000.0;

      
        //cout<<str<<endl;
    }
//
    string outputfilename=alouminum+".out";//output file name
    ofstream out(outputfilename.c_str());//open file.
    for (int i=0;i<5;i++) out<<commentline<<"\t";//put comment lines on top
    out<<endl;//start new line
    
    for(int i=0; i<s1.size();i++)//save data.
    {
        out<<fixed<<showpoint;
        out<<setprecision(8);
        out<<setw(10)<<s1[i]<<"\t"<<s3[i]<<"\t"<<s4[i]<<"\t"<<s5[i]<<"\t"<<s7[i]<<"\t"<<s9[i]<<endl;
    }
    
	return 0;
}
