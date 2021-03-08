#include <iostream>

/*
Generate a random numbe 
between x0 and x1 (inclusive).
*/
double getRandDouble(double x0, double x1)
{
    int r = rand()%RAND_MAX;
    double f = r/(double)RAND_MAX;
    return x0 + f*(x1-x0);
}