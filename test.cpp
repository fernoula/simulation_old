#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class CS
{
public:

  Int_t val=0;
  vector <Double_t> Energy;
  vector <Double_t> Cross;

  Double_t maxCrossSection;
  
  CS()
  {
    ;
  }


  Int_t ReadFile(const char* CrossSectionFile)
  {
    ifstream cross_file;
    string line;
    Int_t line_counter;
   

    cross_file.open(CrossSectionFile);
    if(!cross_file.is_open())
      {
	cout << " cross section file: " << CrossSectionFile << " is NOT open " << endl;
      }
    else
      {
	cout << " cross section file: " << CrossSectionFile << " is being read " << endl;
	line_counter = 0;
	do
	  {
	    getline(cross_file, line);
	    if(!line.empty())
	      line_counter++;
	  } while(!cross_file.eof());
	cross_file.close();

	val = line_counter-1;
	Energy.resize(val,0);
	Cross.resize(val,0);

	cout << val << endl;

	cross_file.open(CrossSectionFile);
	getline(cross_file,line);
	cout << line << endl;

	for(Int_t i=0; i<val; i++)
	  {
	    cross_file >> Energy[i] >> Cross[i];
	    //cout << Energy [i] << " " << Cross[i] << endl;
	  }

	// std::vector<Double_t>::iterator it
	auto it = std::max_element(Cross.begin(),Cross.end());
	maxCrossSection = *it; 
	
      }

    return 1;
  }

  
  Double_t CrossSection(Double_t En)
  {    

    En = En*(4./22);
    
    Double_t diff_En = 0.0;
    Double_t cross = 0.0;

    // returns an iterator pointing to the first element in the range
    // [first,last) which doesn't compare less than val
    auto it = std::lower_bound(Energy.begin(),Energy.end(),En);

    if(En > Energy[Energy.size()-1])
      return 0;
    
    Int_t index = std::distance(Energy.begin(),it);

    //cout << " En: " << En << " Energy: " << Energy[index] << " " << Cross[index] << endl;
    cross = Cross[index]/maxCrossSection;

    //cout << Cross[index] << " " << maxCrossSection << " " << cross << endl;
    
    return cross;
  }

  
};

