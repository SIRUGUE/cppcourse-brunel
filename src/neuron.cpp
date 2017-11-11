#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <cassert>
#include "neuron.hpp"

using namespace std; 

///CONSTRUCTOR
/** @param n :neuron number 
 * @param MP : membrane potential 
 * @param NS : number of spikes 
 * @param TS : time spikes
 * @param TR : time refractory 
 * @param j : value given to other neurons when the neuron spikes
 * @param i : Input current  
 * @param d : delay 
 *   */
Neuron::Neuron ()
		: N(1), MembranePotential(0.0), NbSpikes(0), TimeSpikes(0.0), TimeRefractory(0), J(0.1), Iext (0.0), delay (1.5), buffer (16, 0.0) { } 

///CONSTRUCTOR
/** @param n :neuron number 
 * @param MP : membrane potential 
 * @param NS : number of spikes 
 * @param TS : time spikes
 * @param TR : time refractory 
 * @param j : value given to other neurons when the neuron spikes
 * @param i : Input current  
 * @param d : delay 
 *   */
Neuron:: Neuron (int n=1, double MP =0.0, int NS=0, double TS=0.0, int TR=0, double j=0.1, double i=0.0, double d=1.5 ) 
         : N (n), MembranePotential(MP), NbSpikes(NS), TimeSpikes(TS), TimeRefractory(TR), J(j), Iext (i), delay (d), buffer (16, 0.0) { } 

///CONSTRUCTOR
/** @param n :neuron number 
 * @param j : value given to other neurons when the neuron spikes */         
Neuron:: Neuron (double n, double j) 
		 : N(n), MembranePotential(0.0), NbSpikes(0.0), TimeSpikes(0.0), TimeRefractory(0.0), J(j), Iext(0.0), delay(1.5), buffer (16, 0.0) {}
 
/// GETTER 
/** @return : MembranePotential */
double Neuron:: getMembranePotential() const {
	return MembranePotential; 
     }

/// GETTER 
/** @return : NbSpikes */
int Neuron:: getNbSpikes() const {
	return NbSpikes; 
     }

/// GETTER 
/** @return : TimeSpikes */
double Neuron:: getTimeSpikes() const {
	return TimeSpikes; 
     }

/// GETTER 
/** @return : TimeRefractory */
int Neuron:: getTimeRefractory() const  {
	return TimeRefractory; 
	}

/// GETTER 
/** @return : Vreset */	
double Neuron:: getVreset() const {
	return Vreset; 
	}
	
/// GETTER 
/** @return : Vthr */
double Neuron:: getVthr() const {
	return Vthr; 
	}
	
/// GETTER 
/** @return : tau */	
double Neuron:: getTau() const {
	return tau; 
	}
	
/// GETTER 
/** @return : h */
double Neuron:: geth() const {
	return h; 
	}

/// GETTER 
/** @return : J */
double Neuron :: getJ() const {
	return J;
	}

/// GETTER 
/** @return : delay */
double Neuron :: getDelay() const {
	return delay;
    }

/// GETTER 
/** @return : N */
int Neuron :: getN() const {
	return N;
	}
 
/// SETTEUR
/** @param MB : value affected to MembranePotential */
void Neuron:: setMembranePotential(double MB){
	MembranePotential = MB; 
    }
    
/// SETTEUR
/** @param NS : value affected to NbSpikes */   
void Neuron:: setNbSpikes(int NS){
	NbSpikes = NS; 
    }
    
/// SETTEUR
/** @param TS : value affected to TimeSpikes */    
void Neuron:: setTimeSpikes (double TS){
	TimeSpikes = TS; 
    }

/// SETTEUR
/** @param TR : value affected to TimeRefractory */   
void Neuron:: setTimeRefractory (int TR){
	TimeRefractory = TR; 
    }

/// SETTEUR
/** @param i : value affected to Iext */
void Neuron :: setI (double i) {
	Iext = i ;
	}

/// SETTEUR
/** @param d : value affected to delay */
void Neuron :: setDelay (double d) {
	delay = d; 
	}
 
  
/// UPDATE MEMBRANE POTENTIAL WITHOUT BACKGROUND NOISE
/** @return : void */
void Neuron:: updateMembranePotential (){
	int n= static_cast<int> (TimeSpikes/h) ;
	int m (n%16);
	MembranePotential = c1*MembranePotential +Iext*c2*(1-c1) + buffer [m];
    buffer [m] =0.0 ; // after having taking the value in the right buffer position, we reset it to zero
	
 }
 
/// UPDATE MEMBRANE POTENTIAL WITH BACKGROUND NOISE 
/** @return : void */
void Neuron:: updateMembranePotential_rand (){
	int n= static_cast<int> (TimeSpikes/h) ;
	int m (n%16);
	random_device rd;
	mt19937 gen(rd());
	poisson_distribution<> d(2); //to generate rand spikes for the rest of the brain
	MembranePotential = c1*MembranePotential +Iext*c2*(1-c1) + buffer [m] + 0.1*d(gen) ;
    buffer [m] =0.0 ; // after having taken the value in the right buffer position, we reset it to zero
	
 }
 

   
/// WRITE ON THE FILE TEST.TXT TIMES SPIKES AND NEURON NUMBER TO CREATE GRAPHS
/** @return : void */
void Neuron :: write() {
	ofstream sortie;
	sortie.open("test.txt", ios::out | ios:: app );
	sortie << TimeSpikes << "," << N << endl;
	sortie.close(); 
	}


/// UPDATE NEURON BETWEN TMIN AND TMAX 
/** @param tmin : min time to update neuron
 * @param tmax : max time to update neuron
 * @param i : inpute current of neuron
 *  */
void Neuron :: updateNeuron (double tmin, double tmax, double i) {
   
Iext=i; 
while ((TimeSpikes < tmax) and (TimeSpikes >= tmin)) {
	    if (TimeRefractory>0) {
	    TimeRefractory=TimeRefractory-1 ;
	    MembranePotential=Vreset;
	    }
	    
	     else       {
			  updateMembranePotential();
			  if(MembranePotential>Vthr)  {
	          write ();
	          TimeRefractory = 20; // after the spike of the neuron, it is refractory during 20 ms
	          NbSpikes=NbSpikes+1; 
	         
	         
	          }
	         }

TimeSpikes +=h ; // we advance the time to go to the next step

}
      
}


/// UPDATE NEURON ONLY ONE TIME (ONE STEP) USING UPDATEMEMBRANEPOTENTIAL
/** @param i : input current
 * @return : void */
void Neuron :: updateNeuron1 (double i) {
Iext = i ;

	    if (TimeRefractory>0) {
	    TimeRefractory=TimeRefractory-1 ;
	    MembranePotential=Vreset;
	    }
	    
	     else       {
			  updateMembranePotential();
			  if(MembranePotential>Vthr)  {
	          write ();
	          TimeRefractory = 20; 
	          NbSpikes=NbSpikes+1; 
	         
	         
	          }
	         }

TimeSpikes +=h ;

} 

/// UPDATE ONLY ONE TIME (ONE STEP) USING UPDATEMEMBRANEPOTENTIAL_RAND 
/** @param i : input current
 * @return : void */
void Neuron :: updateNeuron1_rand (double i) {
Iext = i ;

	    if (TimeRefractory>0) {
	    TimeRefractory=TimeRefractory-1 ;
	    MembranePotential=Vreset;
	    }
	    
	     else       {
			  updateMembranePotential_rand();
			  if(MembranePotential>Vthr)  {
	          write ();
	          TimeRefractory = 20; 
	          NbSpikes=NbSpikes+1; 
	         
	         
	          }
	         }

TimeSpikes +=h ;

} 

/// ADD J AT THE POSITION i OF THE BUFFER
/** @param i : position in the buffer
 * @param  j : value to add in the right position of buffer 
 * @return : void */
void Neuron :: addJ(int i,double j) { 
	buffer[i] += j ;
	assert(i>=0);
	assert (i<=15);
	}

///DESTRUCTOR
Neuron:: ~Neuron() {
    }
     

 
