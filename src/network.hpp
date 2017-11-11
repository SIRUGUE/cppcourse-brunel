#ifndef NETWORK_HPP
#define NETWORK_HPP
#include "neuron.hpp"
#include <vector>

using namespace std;

class Neuron;

class Network {
	
private: 	
vector <Neuron*> inhibitors;  // vector of 2500 inhibatory neurons
vector <Neuron*> excitators; // vector of 10000 excitatory neurons
vector <vector <int>> connexions;  // a matrix of size 12500x12500 to establish connections between all neurons
double H; // time step used for the simulation
double clock; // time


public: 
Network(); 
int getConnexions(int i, int j);
void setConnexions(int i, int j, int n);
void NeuronConnexions(); 
void simulationLoop(double tmin, double tmax); 
~Network();




};

#endif
