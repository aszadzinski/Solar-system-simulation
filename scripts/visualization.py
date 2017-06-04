import turtle as t
import time
import visual as vis
import os
from visual import materials, color
from sys import argv	
		
class Simulation():
	def __init__(self):
		self.ob = [] #list on the planet
		self.objects = 0 #num of objects
		self.labels= []#list on labels for planets
		self.names = ["Slonce",'merkury','wenus','ziemia','mars','jowisz','saturn','uran','neptun']
		self.steps = 0 # num of simulation frames
		self.positions = [] #list on positions for self.ob 

	def add_planet(self,x,y,z):
		"""
		Adding new planet to self.ob
		"""
		self.ob.append(vis.sphere(x=x, y=y, z=z, radius = 0.1))

	def get_data(self,path):
		"""
		Loading data from path
		"""
		with open(path,'r') as file:
			data = file.readlines()
			self.objects = int(data[0].split()[1])#getting num of object
			data = data[2:]#Cutting header lines from data file
			self.positions = [[] for i in range(self.objects)]#creating array, each row represents all positions for agiven planet
			self.steps = int((len(data))/self.objects)#Cal steps
			self.center = [[] for i in range(self.objects)]
			print "steps = ", self.steps
			print  "objects = ",self.objects 
			print(self.steps)
			for el in range(self.objects):#iterator = all planets
				for step in range(self.steps):#iterator = all simulation frames
					temp_data = data[step*self.objects+el].split()#Separating t x y z from data lines
					temp_data2 = [float(i) for i in temp_data[1:4]]#converting to float without t parameter
					temp_center = [float(i) for i in temp_data[4:]]
					#print temp_center
					self.positions[el].append(temp_data2)#adding to self.positions list
					self.center[el].append(temp_center)
				
				self.add_planet(self.positions[el][0][0], self.positions[el][0][1], self.positions[el][0][2])#Inicialization planet with intial positions
			self.p = vis.points(pos=tuple(self.center[0][0]), size=1)#mass center 
			self.p2 = vis.points(pos=(0,0,0),size=1)#sun center
				
	def start_simulation(self):
		"""
		Beginning simulation.
		Moving planet from self.ob to positions from self.positions list for each simulation frames
		"""

		if self.objects==9:#Adding colors for planet
			self.col_planet()
			
		for step in range(self.steps-1):#iterator=all simulation steps
			vis.rate(600)#frames per sec
			i=0
			os.system('clear')
			print "=================\nsteps = ", self.steps
			print  "objects = ",self.objects ,"\n=================\n"
			for planet in self.ob:# iterator = all planets and sun
				x,y,z = (self.positions[i][step+1][0], self.positions[i][step+1][1], self.positions[i][step+1][2])
				planet.pos = (x,y,z)#updating positions
				r = ((self.positions[0][step+1][0]-x)**2 + (self.positions[0][step+1][1]-y)**2 + (self.positions[0][step+1][2]-z)**2)**0.5#lenght from sun
				print self.names[i], "=", r,"AU"
				i += 1
				self.p2.pos = (self.positions[0][step+1][0], self.positions[0][step+1][1], self.positions[0][step+1][2])#moving sun center
				self.p.pos = (self.center[0][step+1][0], self.center[0][step+1][1], self.center[0][step+1][2])#moving solar system mass center
				
	def col_planet(self):#colors and overlays for planets
		self.ob[0].material = materials.emissive 
		self.ob[0].radius = 0.0047
		self.ob[0].opacity = 0.1
		
		self.ob[1].color = color.orange
		self.ob[1].radius = 0.04
		
		self.ob[2].material = materials.marble
		self.ob[2].color = color.orange
		self.ob[2].radius = 0.1
		
		self.ob[3].material = materials.earth 
		self.ob[3].radius = 0.1
		
		self.ob[4].color = color.red 
		self.ob[4].radius = 0.09
		
		self.ob[5].color = color.yellow
		self.ob[5].material = materials.marble 
		self.ob[5].radius = 0.18
		
		self.ob[6].color = color.orange
		self.ob[6].material = materials.marble 
		self.ob[6].radius = 0.15
		
		self.ob[7].color = color.cyan
		self.ob[7].radius = 0.12
		
		self.ob[8].color = color.blue  
		self.ob[8].radius = 0.12
		
if __name__ == "__main__":
	simulation = Simulation()
	simulation.get_data(argv[1])#getting data from positions.data
	simulation.start_simulation()#start
