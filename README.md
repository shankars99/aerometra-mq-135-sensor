# aerometra-mq-135-sensor
IOT gas quality detector using Arduino and an MQ-135 sensor

`/others` contains the theory used in the project to arrive at the equations obtained 

`/code` contains two files 
  1. The arduino sketch  
  
  2. Python script 
  
  
# Python script:

  1. During callibration (frequency and timings set by user) the python script is run to note the quality of air based on the resistance of the SnO2 filament in the MQ-135 sensor, as this data varies over the day. 
    
  2. The callibration is required as it sets a rough estimate that can be used to compare the quality of air at a given moment with respect to the initial readings
    
  3. Since different MQ-135(s) have different resistance readings as output due to the different readings of the potentiometer, displaying the quality as relative with an absolute reading of Co2 index for purity was chosen as it is most convenient
    
  4. For more hardcore users that understand the workings, with some tinkering with the potentiometer readings, individual readings of Gases can be obtained, as was done to generate the graph [ attached in /others ] 
  	
    
# Arduino Sketch:

  1. The script contains the data ( header [ needs to be copy pasted from the python script as it is ], the display, the processing, and the run )

  2. The Display is the LED display based on the absolute value of CO2 present in the air 

  3. The processing results with a relative change in the amount of gas present in the air which is used to obtain the absolute values of gases

  4. The run contains the conversion of the resistance read into the SI unit of ( ohms )
  	
{ also read the text file in /others for a simplified overview of the theory used for this project }
