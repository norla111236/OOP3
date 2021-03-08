//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#include "mySystem_SortingVisualization.h"
#include <iostream>

using namespace std;

SORTING_VISUALIZATION::SORTING_VISUALIZATION( )
{
    mNumElements = 20;
    mMinValue = 1;
    mMaxValue = 30;
	mCurrentIndex = 0;
	mMaxNonHandledElementIndex = mNumElements;
    reset( );
}

/*
Generate randomly the elements between mMinValue and mMaxValue.
The total number of elements is mNumElements.
*/
void SORTING_VISUALIZATION::reset( )
{
	mNumbers.clear();
	srand((unsigned)time(NULL));
	double low , up, rndf,x;
	low=mMinValue;
	up=mMaxValue;
	//Compute the coordinates of the sample points.
	for(int i=0;i<mNumElements;i++){
	 rndf = (double) rand() / (RAND_MAX + 1.0); // 
      x = (up - low) * rndf + low; 
		mNumbers.push_back(x);
	mMaxNonHandledElementIndex = mNumElements;
	}
}

/*
Show the system title.
Ask to input the range [mMinValue, mMaxValue] of the elements.
Ask to input the number of elements.
Generate the elements.
*/
void SORTING_VISUALIZATION::askForInput( )
{
     cout << "//////////////////////////////" << endl;
    cout << "SORTING_VISUALIZATION" << endl;
    cout << "//////////////////////////////" << endl;
	cout << "input the range [mMinValue, mMaxValue] of the elements."<<endl;
	cin >> mMinValue;
	cin >> mMaxValue;
	cout<<"input the number of elements."<<endl;
	cin >> mNumElements;
    cout << "Press SPACEBAR to visualize the process..." << endl;
    cout << "//////////////////////////////" << endl;

   
}

/*
Two elements whose
indices are (index) and (index+1).

Swap these two elements if their order is incorrect.
*/
void SORTING_VISUALIZATION::checkAndSwapTwoElements( int index )
{
		if ( mNumbers[ index ] > mNumbers[ index+1 ]) {
			swap(mNumbers[ index ],mNumbers[ index+1 ]);}

}

/*
Perform one swap step for two elements.
The first element is indicated by mCurrentIndex.
*/
void SORTING_VISUALIZATION::processOneSwapStep( )
{
	checkAndSwapTwoElements(mCurrentIndex);
	mMaxNonHandledElementIndex = mNumElements;

	if(mCurrentIndex<mMaxNonHandledElementIndex-2){
	mCurrentIndex++;}
	else{
		mCurrentIndex = 0;
	}
	/*
	int a;
	a = mNumbers[ mCurrentIndex ];
	mNumbers[ mCurrentIndex ] = mNumbers[ mCurrentIndex+1 ];
	mNumbers[ mCurrentIndex+1 ] = a;
	*/
	
         
}

/*
Return the current element that will be processed.
*/
int SORTING_VISUALIZATION::getCurrentElementIndex( ) const
{
    return mCurrentIndex;
}

/*
Return the index of the last non-handled element.

mMaxNonHandledElementIndex
*/
int SORTING_VISUALIZATION::getMaxNonHandledElementIndex( ) const
{
    return mMaxNonHandledElementIndex;
}

/*
Return the number of elements.
*/
int SORTING_VISUALIZATION::getNumOfElements( ) const
{
    //Return the number of elements
    return mNumElements;
}

/*
Return the element whose index is elementIndex.
*/
int SORTING_VISUALIZATION::getElement( int elementIndex ) const
{
    return mNumbers[elementIndex];
}