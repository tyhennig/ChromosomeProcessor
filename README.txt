This program reads the DNA nucleotides and stores the location in the sequence of each unique word

To compile, open your terminal to the location of the p1.c file and type: cc p1.c -lm
The -lm option ensures the compiler links to the necessary libraries included by the code.

To run the program, type ./a.out "name of the file to process"

Example: ./a.out chr1.fa


**NOTE**

The program, in its current state, can only hold up to 50 locations of any unique word.
I was working on using realloc to dynamically increase the array size as needed, but I was
getting an "invalid old size" error when trying to run the program on the real chr1.fa file, but it worked fine on a smaller test.fa file I used. If you would like to test this functionality:

Line 162 contains an if statement (rem >= 11)
uncommenting the 9 will allow the reallocation to happen, but could be unstable.
