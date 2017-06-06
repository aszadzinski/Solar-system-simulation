/*
 * File:    main.cpp
 *
 * Author: Albert Szadzinski
 *
 * Date:    04.06.17
 *
 * Description:
 *          This file is part of solar-system project.
 *
 * INTRODUCTION:
 *   File contains numerical method to predicting planets positions,
 * velocities, accelerations and centres of mass for planetary system.
 *
 * In each loop of calculation, program takes all forces for each planets 
 * and sets acceleration 'a(t)' from Newton's law. Then updates velocities
 * and positions according to:
 *
 *                    V(t+dt) = V(t) + a(t)*dt
 *                    r(t+dt) = r(t) + V(t)*dt
 * 
 * On the occasion of calculate positions, program sets centre mass
 * according to pattern:
 *
 *                    r' = \Sigma_k m_k*r_k / \Sigma_k m_k
 * 
 * All steps of simulation is calculate by division total time 'sym_time'
 * per 'dt'.
 *   Program saves data to positions.data file in real time. 
 * First line contains number of object (planets + star) and second 
 * informations about underlines file structure, e.g.:
 *
 *                     Objects: 2
 *                     time|xpos|ypos|zpos|xcentremass|yc.|zc.
 *                     0 0 0 0 1 1 1           <-  
 *                     0 10 10 10 1 1 1        <-first step
 *                     1 -1 -1 -1 0.5 0.5 0.5  <-
 *                     1 9 9 9 0.5 0.5 0.5     <-second step
 *                     . . . .  .   .   .      <-
 *                     . . . .  .   .   .      <-third step etc..
 *                     . . . .  .   .   .
 *
 * After calculation positions.data can be useed in other
 * programs (/scripts/visualization.py)
 *
 *           */

#include <iostream>
#include "headers/functions.h"
#include <fstream>

using namespace std;

//Param
double m[] = {1.988e+30, 3.33e+23, 4.867e+24, 5.972e+24, 6.419e+23, 1.899e+27, 5.685e+26, 8.683e+25, 1.024e+26, 1.303e+22};
double x[] = {0.0, 44298940342.88921, -38771618878.07003, -6236464504.7840395, -91012988825.44585, -204660431642.82706, 384463142779.51276, 2888690206431.14, -4088556114803.3574, -2173083661579.4548};
double y[] = {0.0, 21297719707.598797, 100223387191.79993, 147008104396.6694, 224473673163.16885, 748926781573.0776, -1450975713568.3884, 784067789928.9556, 1906381388382.157, 5751573433990.57};
double z[] = {0.0, -2336004505.362556, 3590745674.292698, 23184221.872275274, 6946893629.049697, 1523922466.6546347, 10210718209.14562, -34607676970.168495, 54946384201.40566, 12749929732.582664};
double vx[] = {0.0, -30590.785480014223, -32781.165043521665, -30257.074568077922, -21524.398824847143, -12784.372994687013, 8805.192434113536, -1844.4530054564236, -2337.7372000345777, -3542.4431150496075};
double vy[] = {0.0, 46079.712911132985, -12831.574116476206, -1380.8343816152183, -7053.204791541545, -2838.0386333186125, 2442.0795221173776, 6254.455262101803, -4894.1688250676625, -2533.4956336896735};
double vz[] = {0.0, 6573.240034994432, 1721.1341004295036, -1.110216758581626, 384.6523547194473, 298.23915153533306, -392.8298399831066, 47.252611616251684, 154.9670434745729, 1283.243138001364};


double ax[] = {0,0,0,0,0,0,0,0,0};
double ay[] = {0,0,0,0,0,0,0,0,0};
double az[] = {0,0,0,0,0,0,0,0,0};

double c_mass[] = {0,0,0};//mass center


int dim = 3;
int objects = 10;//num_of planet

double dt = 25000;
double sym_time = 1892160000;


void save_pos(double objects, double *x, double *y, double *z);


int main()
{
	double max_iter = sym_time/dt;
	
	fstream file;
	file.open("positions.data", ios::out);
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


