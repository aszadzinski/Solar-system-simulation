#include <math.h>
#include <fstream>
#include <iostream>

using namespace std;

void update_v(int objects, double *m, double *x, double *y, double *z,double *vx, double *vy, double *vz, double dt)
{
	double dx, dy, dz, r, acc;
	
	
	for(int planet=0; planet<objects; planet++)
	{
		double temp_acc[]={0,0,0};
		for(int planet2=0; planet2<objects; planet2++)
		{
			if(planet != planet2)
			{	//len between 
				dx = x[planet2] - x[planet];
				dy = y[planet2] - y[planet];
				dz = z[planet2] - z[planet];
				
				r = sqrt(dx*dx + dy*dy + dz*dz);//calc lenght between objects
				
				acc = 6.674e-11*m[planet2]/(r*r);//calc a between objects
				
				temp_acc[0] += dx*acc/r;//incrementing temporary a
				temp_acc[1] += dy*acc/r;
				temp_acc[2] += dz*acc/r;		
			}
		}
		//updating v
		*(vx + planet) += temp_acc[0]*dt;
		*(vy + planet) += temp_acc[1]*dt;
		*(vz + planet) += temp_acc[2]*dt;
	}
}

void update_r(int objects, double *x, double *y, double *z,double *vx, double *vy, double *vz, double dt, double *c_mass, double *m)
{
	for(int planet=0; planet<objects; planet++)
	{
		//updating r
		*(x + planet) += *(vx + planet)*dt;
		*(y + planet) += *(vy + planet)*dt;
		*(z + planet) += *(vz + planet)*dt;
		
	}
	
	

	//calc mass center	
	double mr[] = {0,0,0};
	double mm[] = {0,0,0};
	
	for(int mass=0; mass<objects; mass++)
	{

		mr[0] += *(m+mass)**(x+mass);
		mm[0] += *(m+mass);
		
		mr[1] += *(m+mass)**(y+mass);
		mm[1] += *(m+mass);
		
		mr[2] += *(m+mass)**(z+mass);
		mm[2] += *(m+mass);
	}
	*(c_mass) = mr[0]/(mm[0]*1.496e11);
	*(c_mass+1) = mr[1]/(mm[1]*1.496e11);
	*(c_mass+2) = mr[2]/(mm[2]*1.496e11);
}

