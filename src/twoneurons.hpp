#ifndef TWONEURONS_HPP
#define TWONEURONS_HPP
#include "neuron.hpp"


class Neuron; 

class TwoNeurons {
	
private: 

Neuron neuron1; //first neuron
Neuron neuron2; // second neuron 
double clock; // time associated to them
const double H=0.1; // time step for the simulation

public: 
TwoNeurons ();
TwoNeurons (Neuron n1, Neuron n2, double t);
Neuron getNeuron1(); 
Neuron getNeuron2();
void setTime(double t); 
void simulationloop1(double tmin, double tmax, double i1, double i2);
void simulationloop2(double tmin, double tmax, double i1, double i2);
~TwoNeurons(); 

} ;

#endif
