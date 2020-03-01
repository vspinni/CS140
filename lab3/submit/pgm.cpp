#include "pgm.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

/* pgm.cpp
  Venkata Shravan Pinni
  This file of functions defines the functions detailed in the 
  pgm.hpp header file and Pgm class.*/
	


bool Pgm::Read(const std::string &file)
{
  ifstream fin;
  string s;
  size_t i, j, r, c, v;

  fin.open(file.c_str());
  if (fin.fail()) return false;
  
  if (!(fin >> s)) return false;
  if (s != "P2") return false;
  if (!(fin >> c) || c <= 0) return false;
  if (!(fin >> r) || r <= 0) return false;
  if (!(fin >> i) || i != 255) return false;

  Pixels.resize(r);
  for (i = 0; i < r; i++) {
    Pixels[i].clear();
    for (j = 0; j < c; j++) {
      if (!(fin >> v) || v > 255) return false;
      Pixels[i].push_back(v);
    }
  }
  if (fin >> s) return false;
  fin.close();
  return true;
}

//This function takes a vector of vector of ints and writes a PGM file with it.
bool Pgm::Write(const std::string &file) const{

	//Error checking.
	if (Pixels.size()==0) return false;

	int cols = Pixels[0].size();
	int rows = Pixels.size();
	int count = 0;
	ofstream fout;

	//Error checking.
	if (fout.fail()) return false;
	
	//Printing the proper format pgm file to the output file.
	fout.open(file.c_str());
	fout << "P2"<<endl;
	fout << cols << " " << rows << endl;
	fout << "255"<<endl;

	//Printing pixels
	for (unsigned int i = 0;i<Pixels.size();i++){
		for (unsigned int j = 0;j<Pixels.at(i).size();j++){
		
			fout << Pixels.at(i).at(j);
			
			//Print in 20s per line.
			count++;
			
			//printing end lines.
			if( (count > 19) && ( ( (i<Pixels.size()-1) || (j<Pixels.at(0).size()-1) ) ) ){
				fout << endl;
				count = 0;
			//printing spaces.
			} else if( ((i<Pixels.size()-1) || (j<Pixels.at(0).size()-1)) ){		
				fout << " ";
			}else {};
		}
	}
	fout << endl;
	fout.close();
	return true;
}

/*This function takes rows, columns, and a pixel value to return a
  return a vector of the indicated values corresponding to a PGM file*/
bool Pgm::Create(size_t r,size_t c,size_t pv){

	//Error Checking.
	if (pv > 255) return false;

	//Clearing Pixels.
	Pixels.resize(0);
	Pixels.clear();

	//inputting pixels of designated p values.
	for (unsigned int i =0;i<r;i++){

		vector <int> vect;
		Pixels.push_back(vect);

		for (unsigned int j=0;j<c;j++){		
			Pixels.at(i).push_back(pv);
		}
	}
	return true;
}

/*This function takes a vector form of a PGM file and rotates it 
90 degrees clockwise. */
bool Pgm::Clockwise(){

	int oldcol = Pixels.at(0).size();
	int oldrow = Pixels.size();
	int var = 0;

	//switching rows with columns top to right.
	vector < vector <int> > temp(oldcol);
	
		for(int i = 0;i<oldcol;i++){
			temp.at(i).resize(oldrow);
		}
	
		for (int i = 0;i<oldcol;i++){
			//var keeps track of the column offset.
			var = 0;
			for(int j = oldrow-1;j>=0;j--){
				temp[i][var] = Pixels[j][i];
				var++;
			}
		}
		//reassigning new output back to Pixels.
		Pixels = temp;

	return true;
}
 
/*This function takes a vector form of a PGM file and rotates it
 90 degrees counter clockwise. */
bool Pgm::Cclockwise(){

	int oldcol = Pixels.at(0).size();
	int oldrow = Pixels.size();
	int var = 0;
	vector < vector <int> > temp(oldcol);

		for(int i = 0;i<oldcol;i++){
			temp.at(i).resize(oldrow);
		}

		//switching rows with columns top to left.
		for (int i = oldcol-1;i>=0;i--){
			
			for(int j = 0;j<oldrow;j++){
				
				//var keeps track of row offset.
				temp[var][j] = Pixels[j][i];

			}
			var++;
		}
	//reassigning new output back to Pixels.
	Pixels = temp;
	return true;

}

/*This function takes a width and pixel value and creates a 
 padding to a PGM file with those given values.*/
bool Pgm::Pad(size_t w, size_t pv){

	//Error checking.
	unsigned int a = 0;
	if ((pv > 255) || (pv<a)) return false;

	//2w is for padding on both sides.
	vector <vector <int> > temp (Pixels.size()+(2*w));
	vector <int> sides ((Pixels.at(0).size() + (2*w)),pv);

	for (unsigned int i = 0; i<temp.size();i++){
		temp[i] = sides;		
	}

	//starting with sides padding and going until original image ends.
	for (unsigned int i  = 0;i<Pixels.size();i++){
		for(unsigned int j = 0;j<Pixels.at(0).size();j++){
			temp[i+w][j+w] = Pixels[i][j];
		}
	}
	
	//putting output back to Pixels.
	Pixels = temp;
	return true;
}

/*This program takes inputs of rows and columns and 
 creates a new PGM file of a pre-existing one repeating 
 the indicated number of rows and columns*/
bool Pgm::Panel(size_t r, size_t c){

	//Error checking
	if ((r<=0) || (c<=0)) return false;

	int rows = Pixels.size();
	int cols = Pixels[0].size();
	int trows = rows * r;
	int tcols = cols * c;
	int crows = 0, ccols = 0;

	vector < vector <int> > temp(trows);
	
	//New vector for final output.
	for (int i  = 0;i<trows;i++){
		temp[i].resize(tcols);
	}
	
	for (int i  = 0;i<trows;i++){
		//counter for an iteration of rows.
		if(crows == rows)
			crows=0;
		for(int j = 0;j<tcols;j++){
			//counter for an iteration of columns.
			if(ccols == cols)
				ccols=0;
			temp[i][j] = Pixels[crows][ccols];
			ccols++;
		}
		crows++;
	}	
	//reassigning output to Pixels.
	Pixels = temp;
	return true;
}

/*This program takes an input of start row, start column, columns,
 and rows and returns a cropped image from the starting location
 over the number of columns and down the number of rows*/
bool Pgm::Crop(size_t r, size_t c, size_t rows, size_t cols){

	//Error Checking.
	if ((rows + r)>Pixels.size()) return false;
	if ((cols + c) > Pixels.at(0).size()) return false;
	if ((r ==0) || (c==0)) return false;
	
	//New vector of cropped size.
	vector < vector <int> > crop;
	crop.resize(rows);
	vector <int> f;
	for (unsigned int i = 0;i<cols;i++){
		crop.push_back(f);
	}

	//putting targeted crop into temp vector.
	for(unsigned int i = 0;i < rows;i++){
		for(unsigned int j = 0;j < cols;j++){
			crop[i].push_back(Pixels[r+i][c+j]);
		}
	}

	Pixels.resize(rows);

	//Putting the cropped output back into Pixels.
	for(unsigned int i = 0;i < rows;i++){
		
		Pixels[i].resize(cols);
		for(unsigned int j = 0;j < cols;j++){
	
			Pixels[i][j] = crop[i][j];
		}
	}

	return true;
}

        
