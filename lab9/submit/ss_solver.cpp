//Shravan Pinni
//11/6/19
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
/*ss_solver.cpp Lab9
 *Shravan Pinni
 *This program solves a shapeshifter game grid from neopets
 *using recursion.
 */
using namespace std;

//Shifter class, almsost the same as Dr. Plank's provided class
//blueprint aside from making Apply Shape a bool and adding a function
//to check if the problem is solved.
class Shifter {
  
	public:
		//Reads in the grid and shapes provided.
		bool Read_Grid_And_Shapes(int argc, const char **argv);
		//Attempts to apply the shape and if successful returns true.
		bool Apply_Shape(int index, int r, int c);
		//Checks if the grid is equal to all 1s or not.
		bool Solved();
		//Recursive Function. Continues to apply the shapes until a solution is found.
		bool Find_Solution(int index);
		//Prints out the function.
		void Print_Solution() const;
  
	protected:
		
		//Grid for the game.
		vector <string> Grid;
		//Vector for the shapes.
		vector < vector <string> > Shapes;
		//Vector to hold the rows for the solution.
		vector <int> Solution_Rows;            
		//Vector to hold the columns for the solution.
		vector <int> Solution_Cols;            
};

//Main.
int main (int argc, const char* argv[]){
	
	Shifter shifter;
	shifter.Read_Grid_And_Shapes(argc, argv);
	shifter.Find_Solution(0);
	shifter.Print_Solution();	
	return 0;
}


bool Shifter::Read_Grid_And_Shapes(int argc, const char **argv){
	
	//Declaring variables.
	string s,temp;
	vector <string> v;
	stringstream ss;

	//Puts grid in from command line..
	Grid.resize(argc-1);
	for (int i = 0; i< argc-1;i++){			
		Grid[i] = (argv[i+1]); 
	}

	//Reads in the shapes from standard input and puts it into the Shapes vector.
	while (getline(cin, s)){
		
		//Gets a whole shape.
		ss.clear();
		ss << s;
		
		//Parses the whole shape and puts it in a vector.
		while(ss >> temp)	v.push_back(temp);

		//Puts the vector into Shapes and clears it.
		Shapes.push_back(v);
		v.clear();			
	}

	return true;
}


bool Shifter::Apply_Shape(int index, int r, int c){
	
	//Checks for out of bounds.
	if (Shapes[index].size()+r > Grid.size() || Shapes[index][0].size()+c > Grid[0].size())
		return false;

	//Applies the shape.
	for (unsigned int i = 0; i < Shapes[index].size(); i++){
		for (unsigned int j = 0; j < Shapes[index][i].size(); j++){
		
			//Checks what the shape interacts with and changes it.
			if (Shapes[index][i][j] == '1'){
				if (Grid[i+r][j+c] == '1')
					Grid[i+r][j+c] = '0';
				else 
					Grid[i+r][j+c] = '1';
			}
					
		}
	}
	return true;
}

bool Shifter::Solved(){		
	
	//Compares each part of the grid to 1 to check if it is solved.
	for (unsigned int i  = 0; i < Grid.size();i++){
		for (unsigned int j = 0; j < Grid[0].size();j++){
			if (Grid[i][j] == '0')
				return false;
		}
	}
	return true;
}


bool Shifter::Find_Solution(int index){

	//Checks if the given shape is inside Shapes or not.
	if (index >= (int)(Shapes.size())){
		return false;
	}

	if(index >=  (int)Solution_Rows.size()){
		Solution_Rows.push_back(0);
		Solution_Cols.push_back(0);
	}

	//Traverses the entire grid.
	for (unsigned int i = 0; i < Grid.size();i++){
		for (unsigned int j = 0; j < Grid[i].size();j++){
				
			//If the shape doesn't work then move on.
			if(!Apply_Shape(index, i, j))
				continue;

			//Applies recursion if the answer isn't found.
			if (!Solved())
				Find_Solution(index+1);
			
			//If it is solved it puts them into the solution rows and columns and returns.
			if (Solved()){
				Solution_Rows[index] = i;
				Solution_Cols[index] = j;
				return true;
			}

			//Applies the shape.
			Apply_Shape(index, i, j);
		}
	}
	return false;
}


void Shifter::Print_Solution() const{
	
	//Iterates through the shapes and solution vectors and prints.
	for (unsigned int i  = 0; i< Shapes.size();i++){
		for (unsigned int j = 0; j< Shapes[i].size();j++){
			cout << Shapes[i][j] << " ";	
		}	
		cout << Solution_Rows[i] << " " << Solution_Cols[i] << endl;
	}		
}
