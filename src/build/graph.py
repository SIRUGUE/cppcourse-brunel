import numpy as np
import matplotlib.pyplot as plt

data1= np.genfromtxt ('test.txt', delimiter=',')
data2= np.genfromtxt ('spikes.txt', delimiter=',')

time1= data1[:,][:,0]
neuron= data1[:,][:,1]
time2= data2[:,][:,0]
spikes= data2[:,][:,1]

a=plt.subplot(2,1,1)
plt.scatter(time1, neuron, s=5, c='blue')
plt.xlim(0,100)
plt.ylim(0,100)
plt.ylabel('neuron number')
plt.xlabel('time in ms')



b=plt.subplot (2,1,2, sharex=a)
plt.plot(time2, spikes, c='blue')
plt.xlim(0,100)
plt.ylabel('number of spikes')
plt.xlabel('time in ms')
plt.show()
