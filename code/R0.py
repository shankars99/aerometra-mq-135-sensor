AQI = 90
R = (1024./AQI * 5 - 1) * 10

scaleFac = [662.9382, 116.6020682, 75.3103, 102.694, 43.7748, 33.1197]
expVal = [4.0241, 2.769034857, 3.1459, 2.48818, 3.42936, 3.36587]
atm = [1, 412.57, 22.5, 2.7841, 0.0035, 0.00739]

ppm = []
R0 = []

for i in range(len(atm)):
    R0.append(( R * pow( (atm[i]/scaleFac[i]), (1./expVal[i])) ))

print("#define r0CO " + str(R0[0]) +
    "\n#define r0CO2 " + str(R0[1]) +
    "\n#define r0Ethanol " + str(R0[2]) +
    "\n#define r0NH4 " + str(R0[3]) +
    "\n#define r0Toluene " + str(R0[4]) +
    "\n#define r0Acetone " + str(R0[5]))

'''
AQI = 320
R = (1024./AQI * 5 - 1) * 10
for i in range(len(atm)):
    ppm.append( scaleFac[i] * pow( (R/R0[i]), -expVal[i] ))

print(ppm)
'''
