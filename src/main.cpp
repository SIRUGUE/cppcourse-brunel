#include <iostream>
#include <fstream>
#include "neuron.hpp"
#include "twoneurons.hpp"
#include "network.hpp"

using namespace std;

int main ()

{
Network network;
network.NeuronConnexions();
remove ("spikes.txt"); //delete the existent file 
remove ("test.txt") ;
network.simulationLoop(0.0, 100.0);

return 0;
} 
