﻿//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2017/03/11
//
#include "mySystem_MonteCarlo.h"
#include "myBasicTools.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

#define MAX_SAMPLES 1000000

MONTE_CARLO_SYSTEM::MONTE_CARLO_SYSTEM( )
{
    //BEGIN DO NOT CHANGE ANYTHING HERE
    mFunctionType = FUNCTION_EXPONENTIAL_SINE;
    cout.precision(8);
    //
    mMinX = 0.0;
    mMaxX = 3.141592654*3.0;
    mMinY = -2.0;
    mMaxY = 2.0;
    mMinNumSamples = 100;
    mMaxNumSamples = MAX_SAMPLES;
    mNumSamples = 5000;
    computeSamples( );
    computeArea( );
    //END DO NOT CHANGE ANYTHING HERE
}

/*
Show the message to the user.
*/
void MONTE_CARLO_SYSTEM::askForInput( )
{
    cout << "MONTE_CARLO_SYSTEM::askForInput( )" << endl;
    cout << "Use keys to control......" << endl;
    cout << "1: FUNCTION_EXPONENTIAL_SINE" << endl;
    cout << "2: FUNCTION_COSINE" << endl;
    cout << "3: FUNCTION_SINE_COSINE" << endl;
    cout << "4: FUNCTION_EXPONENTIAL" << endl;
   
    cout << "m: minimum number of sample points" << endl;
    cout << ",: decrease the number of sample points" << endl;
    cout << ".: increase the number of sample points" << endl;
    cout << "/: maximum number of sample points" << endl;

}

/*
Handle the key events.
*/
bool MONTE_CARLO_SYSTEM::handleKeyPressedEvent( int key )
{

    bool flgHandled = false;
	switch(key){
	case('1'):
		mFunctionType = FUNCTION_EXPONENTIAL_SINE;
		break;
	case('2'):
		mFunctionType = FUNCTION_COSINE;
		break;
	case('3'):
		mFunctionType = FUNCTION_SINE_COSINE;
		break;
	case('4'):
		mFunctionType = FUNCTION_EXPONENTIAL;
		break;
	case('.'):
		if(mNumSamples >= mMinNumSamples && mNumSamples <= MAX_SAMPLES){
			mNumSamples = mNumSamples + 1000;}
		else if (mNumSamples < mMinNumSamples){
		mNumSamples = mMinNumSamples;}
		else if (mNumSamples > MAX_SAMPLES){
		mNumSamples = MAX_SAMPLES;}
		break;
	case(','):
		if(mNumSamples >= mMinNumSamples && mNumSamples <= MAX_SAMPLES){
			mNumSamples = mNumSamples - 1000;}
		else if (mNumSamples < mMinNumSamples){
		mNumSamples = mMinNumSamples;}
		else if (mNumSamples > MAX_SAMPLES){
		mNumSamples = MAX_SAMPLES;}
		break;
	case('/'):
		mNumSamples = MAX_SAMPLES;
		break;
	case('m'):
		mNumSamples = mMinNumSamples;
		break;
	}
	computeSamples( );
    computeArea( );
	reset();
	
    //
    return flgHandled;
}

/*
Reset the system state.
Steps:
compute the samples
compute the area
*/
void MONTE_CARLO_SYSTEM::reset( )
{
    srand(0);
    computeSamples( );
    computeArea( );
}

/*
Return the range [mMinX, mMaxX] of x to [minX, maxX].

    minX = mMinX;
    maxX = mMaxX;

*/
void MONTE_CARLO_SYSTEM::getRangeOfX( double &minX, double &maxX ) const
{
    minX = mMinX;
    maxX = mMaxX;
}

/*
Uniformly generate all the random sample points
inside [mMinX, mMaxX] x [mMinY, mMaxY].

The number of sample points is mNumSamples.
*/
void MONTE_CARLO_SYSTEM::computeSamples( )
{
	mX.clear();
	mY.clear();
	srand((unsigned)time(NULL));
	double low , up, rndf,x,y;
	low=mMinX;
	up=mMaxX;
	//Compute the coordinates of the sample points.
	for(int i=0;i<mNumSamples;i++){
	 rndf = (double) rand() / (RAND_MAX + 1.0); // 
      x = (up - low) * rndf + low; 
		mX.push_back(x);
	}
	low=mMinY;
	up=mMaxY;
	for(int i=0;i<mNumSamples;i++){
     rndf = (double) rand() / (RAND_MAX + 1.0); // ｲ｣･ﾍ [0, 1)
      y = (up - low) * rndf + low;  // 
		mY.push_back(y);
	}
}

/*
Compute the area based on the Monte Carlo Simulation.
Steps:
1. compute the number of samples inside the area
2. compute the ratio which is equal to

number of samples inside the area 
divided 
by total number of samples

3. Based on the ratio, compute the area

Return the area value
*/
double MONTE_CARLO_SYSTEM::computeArea( ) const
{
    double area =1.0;
	double numberpoint = 0.0;;
	float ratio = 0.0;

	for(int i = 0; i < getNumSamples(); i++){
		if(isInsideArea(mX[i],mY[i])){
		numberpoint++;}
	}
	ratio = numberpoint / getNumSamples();
	area = (mMaxX - mMinX) * (mMaxY - mMinY) * ratio;
    cout << "Area:" << area << endl;
    return area;

}

/*
Return the number of sample points.
Return mNumSamples.
*/
int MONTE_CARLO_SYSTEM::getNumSamples( ) const
{
    //Return the number of sample points
    return mNumSamples;
}

/*
 x = mX[ sampleIndex ];
 y = mY[ sampleIndex ];
*/
void MONTE_CARLO_SYSTEM::getSample(int sampleIndex, double &x, double &y ) const
{
   x = mX[ sampleIndex ];
   y = mY[ sampleIndex ];

}

/*
Based on the function type mFunctionType,
compute the function value for a given value x.
Return the function value.
*/
double MONTE_CARLO_SYSTEM::getValue(double x) const
{
    double y;
	double e = 2.718281828;
    y = rand( )/(float)RAND_MAX;

    switch( mFunctionType ) {
    case FUNCTION_EXPONENTIAL_SINE:
		y = -x/4.0;
		y = pow(e,y);
		y = (-2)*y*sin(x) ;
        break;
    case FUNCTION_COSINE:
		y = -cos(x);
        break;
    case FUNCTION_SINE_COSINE:
		y = -sin(x)*cos(x); 
        break;
    case FUNCTION_EXPONENTIAL:
		y = x-2;
		y = pow(y,2);
		y = -(y/5.0); 
		y = pow(e,y);
		y = -2*y;

        break;
    }
    return y;
}

/*
Given a point (x,y).
Check if the point lies inside the area.
Return true if it lies inside the area.
Return false otherwise.

The area is defined as the region bounded by
the x-axis and the curve of the function f(x).

Assume that (x,y) lies inside area, then
one of the following conditions must be satisfied.

- If f(x) >= 0 and y >=0, then y <= f(x).
- If f(x) <= 0 and y <=0, then y >= f(x).

Otherwise, (x,y) does not lay inside the area.
*/
bool MONTE_CARLO_SYSTEM::isInsideArea( double x, double y ) const
{
    double realY = getValue( x );
	for(int i =0 ;i<mNumSamples;i++){
		if (y >=0){
			if(realY >= 0 && realY>=y){
				mX[mNumSamples];
				return true;}
			else
				return false;
		}
		else if(y <0){
			if(y <= 0&& realY<=y)
				return true;
			else
				return false;
		}

    /*if( realY >= 0 && mY[i] >=0 && mY[i] <= realY){
		return true;
	}
    else if(realY <= 0 && mY[i] <=0 && mY[i] >= realY){
		return true;
	}
	else {
		return false;
	}*/
	}

}