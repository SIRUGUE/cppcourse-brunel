#include <iostream>
#include <cmath>
#include "twoneurons.hpp"

  
using namespace std; 

/// first constructor without argument
TwoNeurons :: TwoNeurons () 
		   : clock (0.0) {}
		   
 /// second constructor with some arguments
 /** @param n1: the first neuron 
  * @param n2 : the second neuron 
  * @param t : time initialized to 0.0*/  
TwoNeurons :: TwoNeurons(Neuron n1, Neuron n2, double t=0.0) 
          : clock (t), neuron1 (n1), neuron2 (n2)  {  } 
          
/// getteurs
/** @return : neuron1 */
Neuron TwoNeurons :: getNeuron1() {
	return neuron1; 
    }

///getteur 
/** @return : neuron2 */
Neuron TwoNeurons  :: getNeuron2() {
	return neuron2; 
    }
    
///setteur 
/** @param t : time affected to clock
 * @return : void */
void TwoNeurons :: setTime(double t) { 
	clock=t;
	} 
     
/// simulation loop without delay : without using the buffer
 /** @param tmin : minimum time for the simulation
 * @param tmax : maximum time for the simulation
 * @param i1 : input current for the neuron 1
 * @param i2 : input current for the neuron 2 
 * @return : void */     
void TwoNeurons :: simulationloop1(double tmin, double tmax, double i1, double i2) {
	clock=tmin;
	while (clock<tmax){
	neuron1.updateNeuron(tmin, tmax, i1);
    if (neuron1.getMembranePotential() >20) { 
		neuron2.setMembranePotential(neuron2.getMembranePotential()+neuron1.getJ()); 
		//if neuron1 spkies, he gives the value J to the membrane potential of neuron2
	} 
    neuron2.updateNeuron(tmin,tmax, i2);
	if (neuron2.getMembranePotential()<20) {
		neuron1.setMembranePotential(neuron1.getMembranePotential()+neuron2.getJ());
		//if neuron2 spkies, he gives the value J to the membrane potential of neuron1
		 } 	
	
	clock = clock + neuron1.geth() ; //we advance the clock to go to the next step
		  } 
 }

/// simulation loop with delay : using buffer
 /** @param tmin : minimum time
 * @param tmax : maximum time
 * @param i1 : input current for the neuron 1
 * @param i2 : input current the neuron 2
 * @return: void */ 
void TwoNeurons:: simulationloop2(double tmin, double tmax, double i1, double i2) {
	clock=tmin;
	
	while (clock<tmax){
	int n1 (floor((clock + neuron1.getDelay())/H)) ;
	int m1 (n1%16) ; // find the position in the buffer of neuron 2 associated to this time
	int n2 = floor (((clock+neuron2.getDelay())/H));
	int m2 (n2%16) ; // find the position in the buffer of neuron 1 associated to this time

	neuron1.updateNeuron1(i1);
    if (neuron1.getMembranePotential()>20) { 
		neuron2.addJ(m1, neuron1.getJ());
		 // if neuron 1 spikes : add J in the right position of the buffer of neuron 2
	     } 
    neuron2.updateNeuron1(i2);
	if (neuron2.getMembranePotential()>20) {
		neuron1.addJ(m2, neuron2.getJ());
		 // if neuron 2 spikes : add J in the right position of the buffer of neuron 1
		 } 	
	
	clock = clock + H ; //we advance the clock to go to the next step
		  } 
 }
               
/// Destructor
TwoNeurons ::  ~TwoNeurons ()   {
	 } 
          
