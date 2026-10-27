# Lab6_VectorLab
A program for performing various operations on vectors.
- **Program Functions**
  > This program acts as a simple vector calculator, allowing for the
  > entry of vectors into memory, adding and subtracting vectors, scalar multiplication,
  > and the taking of dot products and cross products. These values can then be saved to
  > and loaded from CSV files.
- **Building the Program**
  > A Makefile is provided with the rest of the program. In order to run this
  > file, ensure that you have all header and program files in one folder and run the make
  > command.
- **Running the Program**
  > There is only one command line option for this program, that being _-h_.
  > Running the program with this command provides a list of useful keywords and
  > syntax to use with the program.
- **Command List**
  > Enter a vector's name to display its data.
  > Enter a vector name followed by up to three numbers seperated by spaces to create a vector in memory.
  > Add vectors with _vect1 + vect2_
  > Subtract vectors with _vect1 - vect2_
  > Perform scalar multiplication with _vect1 * number_
  > Find a dot product with _vect1 * vect2_
  > Find a cross product with _vect1 x vect2_
  > All operations, except the dot product, can assign their result to a new vector by including _vect =_ before the operation.
  > Enter _list_ to see all vectors currently in memory.
  > Enter _clear_ to clear memory of all vectors.
  > Enter _exit_ or _quit_ to exit the program.
- **Dynamic Memory Use**
  > This program uses dynamic memory in the storage of the vectors internally, alongside memory allocations
  > inside the program in order to better handle user input. The program has been tested for memory leaks, and
  > when exited properly, will not allow any memory to leak.
