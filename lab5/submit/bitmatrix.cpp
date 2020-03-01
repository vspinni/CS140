#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "bitmatrix.hpp"
using namespace std;

/*Bitmatrix.cpp Lab 5
 *Venkata Shravan Pinni
  This file defines the functions provided in 
  bitmatrix.hpp.
  */

//Manual Rows & Cols Input Constructor.
Bitmatrix::Bitmatrix(int rows, int cols)
{		
	//Throw Error checking.
		if (rows <=0) throw ((string) "Bad rows");
		if (cols <=0) throw ((string) "Bad cols");

	M.resize(rows);
	for (int i = 0; i< rows; i++){
		M[i].resize(cols,'0');				
	}
}
 
//Constructor that reads from file.
Bitmatrix::Bitmatrix(const string &fn)
{
	
	ifstream fin;
	fin.open(fn.c_str());
	string temp;

	//Count is an indefinite iterator.
	int count = 0;
		
		//Error checking.
		if (!(fin.is_open())) throw ((string) "Can't open file");
		if (fin.bad()) throw ((string) "Bad file format");
	
	//Used while loop with indefinite iterator so I could parse to the end of the file. 
	while (getline(fin,temp)){
		
		//Error check.
		if (temp == "")
			continue;
		//Adding to the matrix.
		M.resize(count+1);
		for (int i  = 0; i < (int)temp.size(); i++){
			
			//Error checking.
			if (temp[i]== ' ')
				continue;
			if (temp[i] != '1' && temp[i]!='0' && temp[i]!=' ')
				throw ((string) "Bad file format");
			M[count].push_back(temp[i]);
		}
		//Incrementing the iterator.
		count++;
	
	}
	fin.close();
}
 
//Making a copy of the bitmatrix.
Bitmatrix *Bitmatrix::Copy() const
{
	Bitmatrix *B = new Bitmatrix( M.size(), M[0].size());
	B -> M = M;
	return B;
}

//Writing Matrix to a file.
bool Bitmatrix::Write(const string &fn) const
{
	ofstream fout;
	fout.open(fn.c_str());
	for (unsigned int i = 0; i < M.size();i++){
		fout << M[i]<< endl;
	}
	fout.close();
	return true;
}
 
//Printing matrix to Standard output.
void Bitmatrix::Print(size_t w) const
{
	//Checking that w is valid
	if (w !=0){
		for (int i  = 0; i < (int)M.size();i++){
			for (int j = 0; j < (int)M[0].size();j++){
				cout << M[i][j];
			
				//Checking if space should be put in.
				if ((j!=0 || w==1) && ((j+1) % w ==0) && (j+1!=(int)M[0].size()))
					cout << " ";
			}
			//Checking if new line should be added.
			if (i!=(int)M.size()-1)
				cout << endl;
			if ((i!=0 || w==1) && ((i+1)%w==0) && (i+1!= (int)M.size()))
				cout << endl;
		}
		cout << endl;
	}
	//If w is 0 it just outputs normally.
	else{
		for (int i = 0; i < (int)M.size();i++)
			cout << M[i]<< endl;	
	}
}
 
//Prints Matrix as PGM in specified format.
bool Bitmatrix::PGM(const string &fn, int p, int border) const
{
	//Error Checking.
	if (p <=0 || fn == "."||border < 0)
		return false;

	//Calculating the total rows & columns.
	int trows = p*M.size() + ((M.size()+1)*border);
	int tcols = p*M[0].size() + ((M[0].size()+1)*border);

	ofstream fout;
	fout.open(fn.c_str());

	//PGM formatting.
	fout << "P2" << endl << tcols << " " << trows << endl <<  "255" << endl;

	//Outputting top border if there is one.
	for (int i  = 0; i < border; i++){
		for (int j = 0; j < tcols; j++){
			fout << "0 ";
		}
		fout << endl;
	}

	//Outputting rest of the pgm.
	for (int i = 0; i < Rows(); i++){
		for (int k = 0; k<p; k++){
			
			//Outputting the left outer border.
			for (int j = 0; j < border;j++){
				fout << "0 ";
			}
			
			//Outputs the values p times and then adds a border.
			for (int j = 0; j < Cols();j++){
				for (int l = 0; l < p; l++){
					//Translates into colors.
					if (M[i][j] == '1')
						fout << "100 ";
					else 
						fout << "255 ";
				}

				//Outputting the intermediate and ending borders vertically.
				for (int j = 0; j<border;j++){
					fout << "0 ";
				}	
			}
			fout << endl;
		}
		//Outputting horizontal borders aside from top.
		for (int i  = 0; i < border; i++){
			for (int j = 0; j < tcols; j++){
				fout << "0 ";
			}
		fout << endl;
		
		}
	}
	fout.close();
	return true;
}

//Returns Rows of M.
int Bitmatrix::Rows() const
{
	return M.size();
}

//Returns Columns of M.
int Bitmatrix::Cols() const
{
	return M[0].size();
}

//Returns value at M[row][column].
char Bitmatrix::Val(int row, int col) const
{
	//Error checking.
	if (row >= (int)M.size() || col >= (int)M[0].size() || row <0 || col <0)
		return 'x';
	
	return M[row][col];
}
 
//Sets a the value at a particular index at row, col
bool Bitmatrix::Set(int row, int col, char val)
{
	//Error checking.
	if ((val != '0') && (val != '1')&& (val != 0) && (val != 1))
		return false;
	if (row >= (int)M.size() || col >= (int)M[0].size() || row <0 || col < 0)
		return false;

	//Checking whether val is a char version or int version.
	if ((val == '1') || (val == '0'))
		M[row][col] = val;
	else
		M[row][col] = val+'0';	

	return true;
}

//Swaps specified rows.       
bool Bitmatrix::Swap_Rows(int r1, int r2)
{
	//Error checking.
	if (r1 >= (int)M.size() || r1 <0 || r2 >= (int)M.size() || r2 < 0)
		return false;

	//Swap procedure.
	swap (M[r1],M[r2]);
	return true;
}

//Sets a row += another row.
bool Bitmatrix::R1_Plus_Equals_R2(int r1, int r2)
{
	//Error Checking.
	if (r1>= (int)M.size() || r2 >= (int)M.size() || r1 <0 || r2 < 0 )
		return false;
	
	//Adding them index by index.
	for (int i = 0; i < (int)M[0].size();i++){
		M[r1][i] = ((M[r1][i]-'0') ^ (M[r2][i]-'0')) +'0';
	}
	return true;
}
      

//Adds 2 bitmatrices.
Bitmatrix *Sum(const Bitmatrix *a1, const Bitmatrix *a2)
{
	//Error cehcking.
	if ((a1->Rows() != a2->Rows()) || (a1->Cols() != a2->Cols()))
		return NULL;

	//Return *matrix.
	Bitmatrix *temp = new Bitmatrix(a1 -> Rows(), a1 -> Cols());
	
	//Adds index by index using ^.
	for (int i = 0; i <temp -> Rows() ; i++){
		for (int j = 0; j < temp-> Cols();j++){
			temp -> Set(i, j, (((a1->Val(i,j)-'0') ^ (a2->Val(i,j)-'0'))+'0'));
		}
	}
	return temp;	
}

//Multiplies given Matrices if valid.
Bitmatrix *Product(const Bitmatrix *a1, const Bitmatrix *a2)
{	
	//Error Checking if matrixes are multipliable.
	if (a1->Cols() != a2->Rows())
		return NULL;

	//Return *matrix.
	Bitmatrix *temp = new Bitmatrix(a1->Rows(),a2 -> Cols());

	//Multiplies matrices index by index
	for (int i = 0; i < temp -> Rows() ; i++){
		for (int j = 0; j < temp-> Cols();j++){
			int sum = 0;

			//Sum is for dot product.
			for (int k = 0; k < a1 -> Cols();k++){
				sum+=  (a1->Val(i,k) * a2->Val(k,j));
			}
			//Going back to a 0 or 1.
			sum = sum % 2;	
			temp -> Set(i,j,sum);
		}
	}
	return temp;
}

//Taking a Set part of the given bitmatrix.
Bitmatrix *Sub_Matrix(const Bitmatrix *a1, const vector <int> &rows)
{
	//Error checking.
	if (rows.size()==0)
		return NULL;

	//Result *matrix.
	Bitmatrix *temp = new Bitmatrix(rows.size(),a1->Cols());

	//Making result *matrix.
	for (int i  = 0; i < (int)rows.size();i++){
		for (int j = 0;j<temp->Cols();j++){
			
			//Checking validity of individual values.
			if (rows[i] > a1-> Rows() || rows[i] <0)
				return NULL;

			//Setting index by index.
			temp->Set(i,j,a1->Val(rows[i],j));
		}
	}
	return temp;
}

//Inverting a given matrix if possible.
Bitmatrix *Inverse(const Bitmatrix *m)
{
	//Checks if matrix is invertable.
	if (m->Rows() != m->Cols()) return NULL;

	//Making copy matrix.
	Bitmatrix *copy  = m->Copy();
	Bitmatrix *iden = new Bitmatrix(m->Rows(),m->Cols());
	
	//Making boolean that checks if it is invertable.
	bool isAble = true;

	//Making identity matrix.
	for (int i  = 0;i < iden->Rows();i++){
		iden -> Set (i,i,1);
	}
	
	//Step 1 from the lab writeup for inverse.
	for (int i  = 0; i < m->Rows();i++){
		if (copy->Val(i,i) !='1'){
			
			//Checking if it is invertable or not.
			if (i+1>= m->Rows())
					return NULL;

			for (int j = i+1; j < m-> Rows();j++){
				isAble = false;
				if (copy->Val(j,i)=='1'){
					copy->Swap_Rows(i,j);
					iden->Swap_Rows(i,j);
					isAble = true;
					break;
				}
			}
			//if it is inversable or not.
			if (!isAble){
				return NULL;
			}
		}
		//Part 2 of the write up inverting procedure.
		for (int j = i+1;j<m->Rows();j++){
			if (copy->Val(j,i) == '1'){
				copy -> R1_Plus_Equals_R2(j,i);
				iden -> R1_Plus_Equals_R2(j,i);
			}
		}
	}
	
	//Part 3 of the write up inverting procedure.
	for(int i  = m->Rows()-1;i>=0;i--){	
		for (int j = i+1; j < m->Rows();j++){
			if (copy ->Val(i,j)=='1'){
				copy ->R1_Plus_Equals_R2(i,j);
				iden ->R1_Plus_Equals_R2(i,j);
			}
		}
	}

	return iden;
}

//Hash function from Dr. Planks lecture Notes.
unsigned int djb_hash(const string &s)
{
	size_t i;
	unsigned int h;
	h = 5381;
	for (i = 0; i < s.size(); i++) {
		h = (h << 5) + h + s[i];
	}
	return h;
}

//Constructor for BM_Hash.
BM_Hash::BM_Hash(int size)
{
	if (size <=0) throw ((string) "Bad size"); 
	
	Table.resize(size);

}

//Function that stores the key and bitmatrix.
bool BM_Hash::Store(const string &key, Bitmatrix *bm)
{
	unsigned int index = djb_hash(key) % Table.size();
	
	//Checks if the key is already there.
	for (int i  = 0; i < (int)Table[index].size();i++){
		if (Table[index][i].key==key)
			return false;
	}

	HTE store;
	store.key = key;	
	store.bm = bm;	
	Table[index].push_back(store);
	return true;
}
 
//Finds a value associated with the given key if in table.
Bitmatrix *BM_Hash::Recall(const string &key) const
{
	unsigned int index = djb_hash(key) % Table.size();

	//Checks if the key is there.
	for (int i  = 0; i < (int)Table[index].size();i++){
		if (Table[index][i].key==key)
			return Table[index][i].bm;
	}
	//Returns null if the key is not there.
	return NULL;
}
 
//Returns a vector of all the values in the hash table.
vector <HTE> BM_Hash::All() const
{
	vector <HTE> rv;
	
	for (unsigned int i = 0; i < Table.size();i++){
		for (unsigned int j  = 0; j < Table[i].size();j++){
			rv.push_back(Table[i][j]);
		}
	}
	return rv;
}

