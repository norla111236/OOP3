//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2017/03/11
//
#include "mySystemApp.h"

using namespace std;

#define STUDENT_INFO "Name : �����c   ID : 0513240"

void MY_SYSTEM_APP::showStudentInfo( ) const
{
	cout << "*******************************" << endl;
	cout << "Student ID : 0513240\t" << endl;
	cout << "Student Name : �����c\t" << endl;
	cout << "Student Email : mimi111236@gmail.com\t" << endl;
	cout << "*******************************" << endl;
}

void MY_SYSTEM_APP::showMenu( ) const
{
    cout << "Welcome to our mini-galaxy!" << endl;
    cout << "Menu----------------------" << endl;
    cout << "Key usage:" << endl;
    cout << "F1: Monte Carlo Simulation" << endl;
    cout << "F2: Galaxy" << endl;
    cout << "F3: Painter" << endl;
    cout << "F4: Visualization of Bubble Sort" << endl;
    cout << "F5: Simple File Reader" << endl;
    cout << endl;
    cout << "r: reset" << endl;

    cout << "--------------------------" << endl;

}

MY_SYSTEM_APP::MY_SYSTEM_APP( )
{

    string title = STUDENT_INFO;
    glutSetWindowTitle(title.data( ));

	mSystemType = SYSTEM_TYPE_GALAXY_SYSTEM;
    mColorPalette = new COLOR_PALETTE;

}

void MY_SYSTEM_APP::initApp( )
{
	mFlgShow_Grid = false;
    showMenu( );
}

void MY_SYSTEM_APP::update( )
{
    switch( mSystemType ) {
		case SYSTEM_TYPE_MONTE_CARLO_SIMULATION:
			mMonteCarloSystem.update( );
			break;
		case SYSTEM_TYPE_GALAXY_SYSTEM:
			mGalaxySystem.update( );
			break;
		case SYSTEM_TYPE_SIMPLE_PAINTER:
			mSimplePainter.update( );
			break;
		case SYSTEM_TYPE_SORTING_VISUALIZATION:
			mSortingVisualization.update( );
			break;
        case SYSTEM_TYPE_SIMPLE_FILE_EDITOR:
            mSimpleFileEditor.update( );
            break;
	}
}




