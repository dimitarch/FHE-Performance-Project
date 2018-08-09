import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import statistics as st

name = "D:\Informatics\\testGates\\testData\\testORYN_ALL.txt"
with open(name) as f:
    lines = f.readlines()

data = [float(e.strip()) for e in lines]
t = np.arange(1, 129, 1)

print(np.std(data))
print(st.mean(data))

name = "D:\Informatics\\testGates\\gatesData.txt"
gateData = open(name, "a+")
gateData.write("ORYN:\r\n")
gateData.write("Average time per gate: %.9f\r\n" %(st.mean(data)/100))
gateData.write("Standard deviation: %.9f\r\n" %(np.std(data)/100))

plt.plot(t, data)

plt.ylabel("Time in seconds")
plt.xlabel("Trial №")
plt.savefig("TFHE_ORYN.png")
#plt.show()
