#ifndef NEURON_HPP
#define NEURON_HPP
#include <vector>
#include <cmath>

using namespace std;

class Neuron {
	
private:
int N; // number associated to the neuron
double MembranePotential; // membrane potential 
int NbSpikes; // number of spikes 
double TimeSpikes; // time when spike occurs 
int TimeRefractory; // refractory time
double J; // potential added to others neurons when the neuron spikes 
double Iext; //input current 
double delay; // time waited by other neurons to receive J 
vector <double> buffer; // neuron buffers incoming spikes 
static constexpr double c=1.0; 
static constexpr double tau=20.0 ; 
static constexpr double Vreset=0.0;
static constexpr double Vthr=20.0;
static constexpr double h=0.1;
static constexpr double c1= exp(-h/tau);
static constexpr double c2= tau/c;



public :

Neuron (int N, double MP, int NS, double TS, int TR, double j, double i, double d);
Neuron ();
Neuron (double n, double j);
double getMembranePotential() const;
int getNbSpikes() const; 
int getTimeRefractory() const;
double getTimeSpikes() const; 
double getVreset() const;
double getVthr() const;
double getTau() const;
double geth() const;
double getJ() const;
double getDelay() const;
int getN() const;
void setMembranePotential(double MP);
void setNbSpikes(int NP);
void setTimeSpikes(double TS);
void setTimeRefractory (int TimeRefractory);
void setI (double i);
void setDelay (double d); 
void updateMembranePotential (); 
void updateMembranePotential_rand();
void write();
void updateNeuron (double tmin, double tmax, double i);
void updateNeuron1 (double i); 
void updateNeuron1_rand (double i);
void addJ(int i, double j);
~Neuron();

} ;

#endif

