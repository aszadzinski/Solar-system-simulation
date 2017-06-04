#include <iostream>
#include "headers/functions.h"
#include <fstream>

using namespace std;

//Param
double m[] = {1.988e30,3.33e23,4.867e24,5.972e24,6.419e23,1.899e27,5.685e26,8.683e25,1.024e26};
double x[] = {1,5.791e10,1.082e11,1.496e11,2.279e11,7.784e11,14.267e11,28.709e11,44.98e11};
double y[] = {10,-30,20,12,13,12,14,15,15};
double z[] = {10,-30,20,10,3,7,9,11,32};
double vx[] = {-3,30,5,4,4,1,3,1,1,1};
double vy[] = {1,47600,34800,29600,24000,13000,9600,6800,5400};
double vz[] = {10,-3,-4,2,1,1,1,1,1};
double ax[] = {0,0,0,0,0,0,0,0,0};
double ay[] = {0,0,0,0,0,0,0,0,0};
double az[] = {0,0,0,0,0,0,0,0,0};

double c_mass[] = {0,0,0};//mass center


int dim = 3;
int objects = 9;//num_of planet

double dt = 25000;
double sym_time = 1892160000;


void save_pos(double objects, double *x, double *y, double *z);


int main()
{
	double max_iter = sym_time/dt;
	
	fstream file;
	file.open("data/positions.data", ios::out);
	file<<"Objects: "<<objects<<"\ntime|x-pos|y-pos|z-pos \n";	
	
	//main loop
	for(int step=0; step<max_iter; step++)
	{
		for(int planet=0; planet<objects; planet++)
		{	//SAVING DATA t|x|y|z|mass center xyz
			file<<dt*step<<" "<<*(x+planet)/1.496e11<<" "<<*(y+planet)/1.496e11<<" "<<*(z+planet)/1.496e11<<" "<<c_mass[0]<<" "<<c_mass[1]<<" "<<c_mass[2]<<endl;
		}
		
		//updating v & r
		update_v(objects, &m[0], &x[0], &y[0], &z[0], &vx[0], &vy[0], &vz[0], dt);
		
		update_r(objects, &x[0], &y[0], &z[0], &vx[0], &vy[0], &vz[0], dt, &c_mass[0],&m[0]);
		
	}
	
	file.close();	
	return 0;
}

