//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#include "mySystem_SimpleFileEditor.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#define FILE_NAME "oop.txt"

SIMPLE_FILE_EDITOR::SIMPLE_FILE_EDITOR( )
{
    //BEGIN: DO NOT CHANGE
    mNX = 100; // number of columns
    mNY = 100; // number of rows
    mBitmap = new int[mNX*mNY];
    for ( int i = 0; i < mNX*mNY; ++i ) {
        mBitmap[ i ] = 0;
    }
    readFile( );
    //END: DO NOT CHANGE

}

/*
Set up the bitmap based on the data stored in a file.

Each line in the file is mapped to one row
of the bitmap in a consecutive manner.

Steps:
Open the file.
Read a file.
 Repeat until EOF
   read a line from the file each time
   set the bitmap based on the current line
Close the file.
*/
void SIMPLE_FILE_EDITOR::readFile( )
{
	//char line[100];
	string inputString;
	fstream file;
	file.open("./bin/release/oop.txt");
	int linenumber = 0;
	int index = 0;
	int index2 = 0;
	int length = 41;


	 if(!file)
	  { cout<<"error"<<endl;
	   system("pause");}
	else{
	while(!file.eof()){
		while(getline(file, inputString)){
		cout<<"inputstring:"<<inputString<<endl;
       // cout<<inputString.size()<<endl;
		
		if(inputString.size()<length){
		for(int i = inputString.size();i<length+1;i++){
			inputString[i] = 0;
		 }
		}

		stringstream ss;
		ss << index;
		ss >> inputString[length+4];//int to string
		ss.clear();
		ss << index2;
		ss >> inputString[length+5];
		ss.clear();

		storeOneRowToBitmap(inputString);

		/*
	    for (int i =0 ;i<42;i++){
			//cout<<"mBitmap["<<index<<"]="<<inputString[i]<<endl;
			if(inputString[i] == ' '){
				mBitmap[ index ] = 0;
			}
			else{
				mBitmap[ index ] = inputString[i];
			}
		 index++;
		    }
         */

		if(index == 9){
			index2++;
			index = 0;
		}
		else{
			index++;
		}
		//index = index-42+100;
		  }
	    }
	file.close();
	   }
	  

	
}

/*
Set one row of the bitmap based on the input string inputString.
The elements of the row are mapped one to one to the input string.

The element of a bitmap is set as follows.

If inputString[i] is the space character, 
the value of the element is set as 0.
Otherwise, the value of the element is set to (int) inputString[i].
*/
void SIMPLE_FILE_EDITOR::storeOneRowToBitmap( const string &inputString )
{
	int index, index2;
	int length = 41;
	stringstream ss;
	    ss << inputString[length+4];
		ss >> index;
		ss.clear();
		ss << inputString[length+5];
		ss >> index2;
		ss.clear();
		index = index+index2*10;

	
	    for (int i =0 ;i<length+1;i++){
			if(inputString[i] == ' '){
				mBitmap[ 100*index+i ] = 0;
			}
			else{
				mBitmap[ 100*index+i ] = inputString[i];
			}
		    }


}

/*
Show the system title.
Show "No input is required!".
*/
void SIMPLE_FILE_EDITOR::askForInput( )
{
    //Show the system title
    //
    cout << "SIMPLE_FILE_EDITOR" << endl;
    cout << "No input is required!" << endl;
}

/*
Get the dimension of the bitmap to (nx, ny).
nx : number of columns
ny : number of rows
*/
void SIMPLE_FILE_EDITOR::getBitmapDimension(int &nx, int &ny) const
{
    nx = mNX;
    ny = mNY;
}

/*
Return the bitmap value at (x, y).
x : column index
y : row index
*/
int SIMPLE_FILE_EDITOR::getBitmapValue(int x, int y) const
{
    return mBitmap[ x+100*y ];
}

