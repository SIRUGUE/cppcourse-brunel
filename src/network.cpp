#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <random>
#include <cassert>
#include "network.hpp"

using namespace std; 

///CONSTRUCTOR 
/** we create 10000 excitatory neurons & 25000 inhibitory neurons
and we create a tab (size 12500x12500) representing our neurons connexions */
Network :: Network () 
		   : connexions (12500, vector <int> (12500)), H(0.1), clock(0.0){ 
	for ( int i(0); i<2500; ++i) {
		Neuron neuron_inhib((i+10000), -0.5); 	// inhibitors are characterized by J = -O.5
												// neuron number is i+10000 as the first 10000 are the excitators
		inhibitors.push_back (new Neuron(neuron_inhib));
	}
	for ( int i(0); i<10000; ++i) {
		Neuron neuron_excit(i, 0.1);  // excitators are characterized by J= 0.1
		excitators.push_back (new Neuron(neuron_excit));
	}
	
}


///GETTEUR 
/** @param i : line number
 * @param j : colcolumn number
 * @return : value of table connexions at position (i;j) */ 
int Network :: getConnexions (int i, int j) {
	return connexions[i][j]; 
}

///SETTEUR : 
/** it gives the values n to the tab connexions at the position (i;j)
 * @param i : line position
 * @param j : column position
 * @param n : value given to the position (i;j)
 * @return : void */ 
void Network :: setConnexions (int i, int j, int n) {
	connexions[i][j] = n ; 
	assert (i>=0);
	assert (i<12500);
	assert (j>=0);
	assert (j<12500);
}
	
	
/// complete connexions table randomly in order to connect each neuron 
/// with 1000 excitatory neurons and 250 inhibitory neurons 
 /** @return : void  */
void Network:: NeuronConnexions () {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis_e (0, 9999);  // connexions with excitatory neurons : give a number between 0 and 9999
	uniform_int_distribution<int> dis_i ( 10000, 12499); // connexions with inhibatory neurons : give a number betwen 10000 and 12499
	
	for (int i(0); i<12500; ++i) {
		int n_e (1000);  // we have to make 1000 connexions with excitatory neurons
		while (n_e>0) {
			if ( (getConnexions(i, dis_e(gen)) == 0)) {
				setConnexions(i, dis_e(gen), 1) ;  // we produce an excitatory connexion if it was inexistent before
				n_e = n_e-1 ; 
			}
		}
		int n_i (250); // we have to make 250 connexions with inhibitory neurons
		while (n_i>0) { 
			if ( (getConnexions(i, dis_i(gen)) ==0)) {
				setConnexions(i, dis_i(gen), 1);  // we produce an inhibitory connexion if it was inexistent before
				n_i = n_i-1; 
			}
	    }
    }
}


 ///update the network betwen tmin and tmax 
 /** @param tmin : minimum time for simulation
 * @param tmax : maximum time for simulation
 * @return : void */
void Network :: simulationLoop(double tmin, double tmax) {
clock = tmin; 
int n_spikes(0); // to account the total number of spikes of all neurons

	while (clock<tmax) {
		for (auto& element : excitators) {
			int n (floor((clock + element->getDelay())/H)) ;
	        int m (n%16) ;
			element->updateNeuron1_rand(0.0); // we update one time the neuron
			if (element->getMembranePotential()>20) {
				n_spikes +=1;
				cout << clock << "spike du neuron " << element->getN()<< endl;
				for(int i(0); i<12500; ++i) {
					if (getConnexions(element->getN(),i) ==1) {
						if (i<10000) {  
							excitators[i]->addJ(m, 0.1); // the neuron spikes so he gives J to neurons connected to it
							assert (i>=0);
							assert (i<=9999);
							 }
						else {
							inhibitors[i-10000]->addJ(m, 0.1);  // the neuron spikes so he gives J to neurons connected to it
							assert ((i-10000)>=0);
							assert ((i-10000)<=2499);
						}
					}
				}
			}
		}
						
			for (auto& element : inhibitors) {
			int n (floor((clock + element->getDelay())/H)) ;
	        int m (n%16) ;
			element->updateNeuron1_rand(0.0); 
			if (element->getMembranePotential()>20) {
				n_spikes +=1;
				 cout << clock << " spike du neuron" << element->getN()<< endl;
				for(int i(0); i<12500; ++i) {
					if (getConnexions(element->getN(),i) ==1) {
						if (i<10000) { 
							excitators[i]->addJ(m, -0.5);
							assert (i>=0);
							assert (i<=9999);
							 }
						else {
							inhibitors[i-10000]->addJ(m, -0.5);
							assert ((i-10000)>=0);
							assert ((i-10000)<=2499);
						}
			
							
				}
			}
		}
	}
	ofstream sorti;  // to write in a file the number total of spikes at each step
	sorti.open("spikes.txt", ios::out | ios:: app);
	sorti << clock << "," << n_spikes << endl;
	sorti.close(); 
    clock= clock+H; // advance the clock to move to the next step
    n_spikes =0; 
    
}
}

///DESTRUCTOR
Network :: ~Network() {
}
					
			
