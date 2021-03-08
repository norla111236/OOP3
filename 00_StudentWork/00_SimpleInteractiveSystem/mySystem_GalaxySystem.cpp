//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#include "mySystem_GalaxySystem.h"
#include <iostream>
#include<ctime>

using namespace std;

namespace {
	double getRandDouble(double L, double U) {
		return L + (U - L) * rand() / (double)RAND_MAX;
	}
};

GALAXY_SYSTEM::GALAXY_SYSTEM()
{
	cout << "GALAXY_SYSTEM::GALAXY_SYSTEM -- starting...." << endl;
	mTimeStep = 0.0025;
	mMaxV = 100.0;
	mNumOfObjs = 100;
	mNumLargeObjs = 2;
	mMinR = 0.5;            //minimum radius of objects
	mMaxR = 3.0;            //maximum radius of objects
	mSpaceSize = 300.0;
	mG = 5;              //gravitational constant
	generateObjects();
	cout << "GALAXY_SYSTEM::GALAXY_SYSTEM -- end...." << endl;
}

/*
Generate randomly the positions,
velocities and radii of the objects.

Also, if the objects are large,
set their masses to be a large number.

The mass of an  object depends on the object's radius.

The position of an object is inside
[-halfSpaceSize, halfSpaceSize]x[-halfSpaceSize, halfSpaceSize].

The velocity of an object is inside
[-100.0, 100]x[-100.0, 100].

Initialize the alive flag of each object.
the alive flag indicates whether the object is alive or not.
If the object is not alive, ignore it in all the calculations.

If there's only one large object,
set its position to the origin
and set its velocity to zero.

*/
void GALAXY_SYSTEM::generateObjects()
{
	mX.clear();
	mY.clear();
	mR.clear();
	mMass.clear();
	mAlive.clear();
	mVx.clear();
	mVy.clear();
	mFx.clear();
	mFy.clear();

	
	//small objects
	srand((unsigned)time(NULL));

	double low , up, rndf,x,y,r,mass;
	low = -mSpaceSize/2;
	up = mSpaceSize/2;
	//Compute the coordinates of the sample points.
	
	for(int i=0;i<mNumOfObjs;i++){
	 rndf = (double) rand() / (RAND_MAX + 1.0); // 
      x = (up - low) * rndf + low; 
	 // cout<<"x:"<<x<<endl;
		mX.push_back(x);
     rndf = (double) rand() / (RAND_MAX + 1.0); // [0, 1)
      y = (up - low) * rndf + low;  // 
	//  cout<<"y:"<<y<<endl;
		mY.push_back(y);
	}
	
	low = mMinR;
	up = mMaxR;
	for(int i=0;i<mNumOfObjs;i++){
	 rndf = (double) rand() / (RAND_MAX + 1.0); // 
      r = (up - low) * rndf + low; 
	//  cout<<"r:"<<r<<endl;
		mR.push_back(r);
		mass = mR[i]*mR[i];
		mMass.push_back(mass);
		mAlive.push_back(true);
	}
	
	low = -mMaxV;
	up = mMaxV;
	double vx,vy;
	//Compute the coordinates of the sample points.
	for(int i=0;i<mNumOfObjs;i++){
	 rndf = (double) rand() / (RAND_MAX + 1.0); // 
      vx = (up - low) * rndf + low; 
		mVx.push_back(vx);
     rndf = (double) rand() / (RAND_MAX + 1.0); // ｲ｣･ﾍ [0, 1)
      vy = (up - low) * rndf + low;  // 
		mVy.push_back(vy);
	}


	for (int i = 0; i < mNumLargeObjs; i++) {
		mR[i] = mMaxR*2.0;
		mMass[i] = mMaxR*mMaxR * 1000;
		mVx[i] = 0;
		mVy[i] = 0;
		if (mNumLargeObjs == 1) {
			mX[i] = 0;
			mY[i] = 0;
		}
	}

	//Fill in here
	/* You can remove the following lines.*/
	mX.resize(mNumOfObjs);
	mY.resize(mNumOfObjs);
	mR.resize(mNumOfObjs);
	mMass.resize(mNumOfObjs);
	mVx.resize(mNumOfObjs);
	mVy.resize(mNumOfObjs);
	mFx.resize(mNumOfObjs);
	mFy.resize(mNumOfObjs);
}

/*
Handle the key events.
*/
bool GALAXY_SYSTEM::handleKeyPressedEvent(int key)
{
	bool flgHandled = false;
	switch (key) {
	case'1':
		mNumLargeObjs = 1;
		generateObjects();
		break;
	case'2':
		mNumLargeObjs = 2;
		generateObjects();
		break;
	case'3':
		mNumLargeObjs = 3;
		generateObjects();
		break;
	}
	return flgHandled;
}

/*
Generate the objects.
Call generateObjects( ).
*/
void GALAXY_SYSTEM::reset()
{
	generateObjects();
}

/*
Show the system title.
Show the key usage.
*/
void GALAXY_SYSTEM::askForInput()
{
	cout << "GALAXY_SYSTEM::askForInput" << endl;
	cout << "Key usage:" << endl;
	cout << "1: one large object" << endl; // generate the objects. Only one large object
	cout << "2: two large object" << endl; // generate the objects. Only two large objects
	cout << "3: three large object" << endl; // generate the objects. Only three large objects
	cout << "r: reset" << endl; 		// reset the positions of the objects

}

/*
Return the number of objects
return mNumOfObjs
*/
int GALAXY_SYSTEM::getNumOfObjs() const
{
	return mNumOfObjs;
}

/*
Get the object information based on the object index.
(x,y) = position
r = radius
Return the alive flag.
*/
bool GALAXY_SYSTEM::getObjInfo(int objIndex, double &x, double &y, double &r) const
{
	x = mX[objIndex];
	y = mY[objIndex];
	r = mR[objIndex];
	return mAlive[objIndex];
}

/*
Merge the objects if they overlap with each other.
Modify the velocities of the objects after merging
based on the conservation of momentum.
Set the alive flags of the objects accordingly.

Pseudo-code

For each pair of the objects
if they do not overlap continue
If they overlap
do
turn off the alive flag of the object with smaller radius
compute the new velocity of the larger object
*/
void GALAXY_SYSTEM::mergeObjects()
{

	for (int i = 0; i < mNumOfObjs; ++i) {
		if (!mAlive[i]) continue;
		for (int j = i + 1; j < mNumOfObjs; ++j) {
			if (!mAlive[j]) continue;

			double d = sqrt(((mX[i] - mX[j])*(mX[i] - mX[j])) + ((mY[i] - mY[j])*(mY[i] - mY[j])));
			if (d <= mR[i] + mR[j])
			{
				double X, Y;
				X = mVx[i] * mMass[i] + mVx[j] * mMass[j];
				Y = mVy[i] * mMass[i] + mVy[j] * mMass[j];

				if (mMass[i] >= mMass[j]) {
					mAlive[j] = false;
					mMass[i] += mMass[j]; 
					mVx[i] = X / mMass[i];
					mVy[i] = Y / mMass[i];

				}
				else
				{
					mAlive[i] = false;
					mMass[j] += mMass[i];
					mVx[j] = X / mMass[j];
					mVy[j] = Y / mMass[j];

				}
			}
		} 
	} 

}

/*
Update the position of the objects
Steps:
1. compute the forces exerting on each object
2. compute the velocity of each object
3. compute the position of each object

Constraints:
The component of a velocity must be inside [-mMaxV, mMaxV].

The component of a position must be inside [-halfSpaceSize, halfSpaceSize].
Warp the position if it's outside of the range.
Consider a position (x,y).
If x > halfSpaceSize, set x = -halfSpaceSize;


*/
void GALAXY_SYSTEM::update()
{
	mergeObjects(); 
	for (int i = 0; i < mNumOfObjs; ++i) {
		if (mAlive[i] != true){
			for(int j=0;j<mNumOfObjs; ++j){
					mFx[j]=0;
					mFy[j]=0;
			}
		}
	}

	for (int i = 0; i < mNumOfObjs; ++i) {
		if (mAlive[i] != true) continue;			
		for (int j = i + 1; j < mNumOfObjs; ++j) {
			if (mAlive[j] != true)	continue;

			double d = sqrt(((mX[i] - mX[j])*(mX[i] - mX[j])) + ((mY[i] - mY[j])*(mY[i] - mY[j])));

			double nx = (mX[i] - mX[j]) / d; 
			double ny = (mY[i] - mY[j]) / d; 
			double mij = mMass[i] * mMass[j];


			mFx[i] -= mij*mG*nx / (d*d); 	//notice the negative sign	
			mFy[i] -= mij*mG*ny / (d*d);	//notice the negative sign

			mFx[j] += mij*mG*nx / (d*d);	//notice the positive sign
			mFy[j] += mij*mG*ny / (d*d);  //notice the positive sign
		}

	}


	for (int i = 0; i < mNumOfObjs; ++i) {
		if (mAlive[i] != true) continue;
		double m = mMass[i];

		mVx[i] = mVx[i] + (mFx[i] / m) * mTimeStep;
		mVy[i] = mVy[i] + (mFy[i] / m) * mTimeStep;

		if (mVx[i] > mMaxV) {
			mVx[i] = mMaxV;
		}
		else if (mVx[i] < -mMaxV) {
			mVx[i] = -mMaxV;
		}

		if (mVy[i] > mMaxV) {
			mVy[i] = mMaxV;
		}
		else if (mVy[i] < -mMaxV) {
			mVy[i] = -mMaxV;
		}


		mX[i] = mX[i] + mVx[i] * mTimeStep;
		mY[i] = mY[i] + mVy[i] * mTimeStep;

		if (mX[i] > (mSpaceSize / 2)) {
			mX[i] = -mSpaceSize / 2;
		}
		else if (mX[i] < -(mSpaceSize / 2)) {
			mX[i] = (mSpaceSize / 2);
		}

		if (mY[i] > (mSpaceSize / 2)) {
			mY[i] = -mSpaceSize / 2;
		}
		else if (mY[i] < -(mSpaceSize / 2)) {
			mY[i] = (mSpaceSize / 2);
		}
	}
}
	

