#include <iostream>
#include "neuron.hpp"
#include "twoneurons.hpp"
#include "gtest/gtest.h"

TEST (NeuronTest, MembranePotential) {
Neuron neuron; 
neuron.setI(1.0);
neuron.updateMembranePotential();

EXPECT_EQ(20.0*(1.0- std::exp(-0.1/20.0)), neuron.getMembranePotential());
}

TEST (NeuronTest, SpikeTimes) {
// We know that the spikes times are at 92.4 ms, 186.8 ms, 281.2ms, 375.6ms
//Waiting for the first spike
Neuron neuron; 
neuron.setI(1.01);
neuron.updateNeuron(0, 92.2, 1.01);
EXPECT_EQ(0, neuron.getNbSpikes());
neuron.updateNeuron(92.2, 92.4, 1.01);
EXPECT_EQ(1, neuron.getNbSpikes());
EXPECT_NEAR(0.0, neuron.getMembranePotential(), 1e-3);


//Waiting for the second spike

neuron.updateNeuron(0, 186.6, 1.01);
EXPECT_EQ(1, neuron.getNbSpikes());
neuron.updateNeuron(186.6, 186.8, 1.01);
EXPECT_EQ(2, neuron.getNbSpikes());
EXPECT_NEAR(0.0, neuron.getMembranePotential(), 1e-3);


}

TEST (NeuronTest, NegativeInput) {
Neuron neuron; 
neuron.setI(-1.0); 

//First update test
neuron.updateNeuron (0.0, 0.1, -1.0);
EXPECT_NEAR((-20.0*(1.0- std::exp(-0.1/20.0))), neuron.getMembranePotential(), 1e-3);

//Test after numerous updates 
neuron.updateNeuron (0.0, 1000.0, -1.0); 
EXPECT_GT(1e-3, std::fabs(-19.999 -neuron.getMembranePotential())); 

} 

TEST (NeuronTest, NulInput) {
//The membrane potential should tend naturally to zero 
Neuron neuron;
neuron.setI(0.0); 
//We wait 10*tau ms, should be enough
neuron.updateNeuron(0.0, 200.0, 0.0); 
EXPECT_NEAR(0, neuron.getMembranePotential(), 1e-3);

}

TEST (NeuronTest, StandaloneStimulation) {
Neuron neuron; 
neuron.setI(1.01); 
// We know that the spikes times are at 92.4 ms, 186.8 ms, 281.2ms, 375.6ms
neuron.updateNeuron(0.0, 400.0, 1.01) ;
EXPECT_EQ(4, neuron.getNbSpikes());
}

TEST (TwoNeuronsTest, NoPSSpike) {
TwoNeurons twoneurons;  
twoneurons.getNeuron1().setDelay(1.5);
twoneurons.getNeuron1().setI(1.01);
//	We wait for the first spike and wait see the impact on neuron 2
//we look the different values at time_spike+delay = 92.3+1.5 = 93.8
twoneurons.simulationloop2(0.0, (93.8), 1.01, 0.0) ;
EXPECT_EQ(0.0, twoneurons.getNeuron1().getMembranePotential());
EXPECT_EQ(0.1, twoneurons.getNeuron2().getMembranePotential());
}

TEST (TwoNeuronsTest, WithPSSpike) {
TwoNeurons twoneurons;
twoneurons.getNeuron1().setDelay(1.5);
twoneurons.getNeuron1().setI(1.01);
twoneurons.getNeuron2().setI(1.00);
//We wait for the second spike of neuron 1 to see neuron2 spike
//because neuron1 did not have time to reach the threshold
twoneurons.simulationloop2(0.0, 188.1, 1.01, 1.0) ;
EXPECT_EQ(0.0, twoneurons.getNeuron1().getMembranePotential());
//Just before neuron 2 spike
EXPECT_EQ(0, twoneurons.getNeuron2().getNbSpikes());
twoneurons.simulationloop2(188.2, 188.4, 1.01, 1.0);
EXPECT_EQ(0, twoneurons.getNeuron2().getMembranePotential());
EXPECT_EQ(1, twoneurons.getNeuron2().getNbSpikes());
}


int main (int argc, char **argv) {
	::testing :: InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS(); 
	}
