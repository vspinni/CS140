


Class Shifter {
  public:

    /* Read_Grid_And_Shapes() initializes the grid from argc/argv, and the
       reads from standard input to get the shapes. */

    bool Read_Grid_And_Shapes(int argc, const char **argv);

    /* Apply_Shape() applies the shape in Shapes[index] to the grid,
       starting at row r and column c.  You'll note, if you call
       Apply_Shape twice with the same arguments, you'll end up 
       with the same grid as before the two calls. */

    void Apply_Shape(int index, int r, int c);

    /* Find_Solution() is the recursive procedure.  It tries all possible
       starting positions for Shape[index], and calls Find_Solution() 
       recursively to see if that's a correct way to use Shape[index].
       If a recursive call returns false, then it "undoes" the shape by
       calling Apply_Shape() again. */

    bool Find_Solution(int index);

    /* This prints the solution on standard output. */

    void Print_Solution() const;

  protected:

    /* This is the grid.  I have this be a vector of 0's and 1's, because it makes
       it easy to print the grid out. */

    vector <string> Grid                   

    /* These are the shapes, in the order in which they appear in standard input. */

    vector < vector <string> > Shapes;     

    /* These two vectors hold the starting positions of the shapes, both as you
       are finding a solution, and when you are done finding a solution. */

    vector <int> Solution_Rows;            
    vector <int> Solution_Cols;            
};

