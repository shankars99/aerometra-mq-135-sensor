/*
CO2: ppm = 114.3544 * (rs/ro)^-2.93599
CO ppm = 662.9382 * (rs/ro)^-4.0241
Ethanol ppm = 75.3103 * (rs/ro)^-3.1456
Ammonium NH4 ppm = 102.694 * (rs/ro)^-2.48818
Toluene ppm = 43.7748 * (rs/ro)^-3.42936
Acetone ppm = 33.1197 * (rs/ro)^-3.36587
*/

/*
119.00283689406935
943.8215172796514
407.30675312888224
140.27483455301254
38.19197360704412
49.18784025704627
*/


#define RLOAD 10.0

#define r0Air 1
#define r0CO 111.219671047
#define r0CO2 882.092573749
#define r0Ethanol 380.667589788
#define r0NH4 131.100412078
#define r0Toluene 35.6940964778
#define r0Acetone 45.9707983079
#define scaleFactorCO 662.9382
#define exponentCO 4.0241

#define scaleFactorCO2 116.6020682
#define exponentCO2 2.769034857

#define scaleFactorEthanol 75.3103
#define exponentEthanol 3.1459

#define scaleFactorNH4 102.694
#define exponentNH4 2.48818

#define scaleFactorToluene 43.7748
#define exponentToluene 3.42936

#define scaleFactorAcetone 33.1197
#define exponentAcetone 3.36587


#define atmCO 1
#define atmCO2 412.57
#define atmEthanol 22.5
#define atmNH4    2.7841
#define atmToluene 0.0035
#define atmAcetone 0.00739

float R = 0;
float R_callib = 91;

float getCO(float res) {
  return scaleFactorCO * pow((res/r0CO), -exponentCO);
}
float getCO2(float res) {
  return scaleFactorCO2 * pow((res/r0CO2), -exponentCO2);
}
float getEthanol(float res) {
  return scaleFactorEthanol * pow((res/r0Ethanol), -exponentEthanol);
}
float getNH4(float res) {
  return scaleFactorNH4 * pow((res/r0NH4), -exponentNH4);
}
float getToluene(float res) {
  return scaleFactorToluene * pow((res/r0Toluene), -exponentToluene);
}
float getAcetone(float res) {
  return scaleFactorAcetone * pow((res/r0Acetone), -exponentAcetone);
}

void setup()
{
  pinMode(A1,INPUT);
  Serial.begin(9600);
}

float getResistance() {
  return (R);
}


int scale(int input){
  double frac = (280+input)/190.0;
  frac = pow(2, frac)*input;

  return((frac));
}

void showLED(int red, int blue, int green){
    analogWrite(A3, red);
    analogWrite(A4, blue);
    analogWrite(A5, green);
}

void calcLED(int aqi){
  if(aqi<350){         //green
    showLED(9,255,0);
  }
  else if(aqi<450){  //yellow
    showLED(255,255,0);
  }
  else if(aqi<550){  //orange
    showLED(255,102,0);
  }
  else if(aqi<800){  //red
    showLED(255,0,0);
  }
  else if(aqi<1400){  //purple
    showLED(153,51,153);
  }
  else{  //merune
    showLED(153,0,51);
  }
}

void disp(int aqi){
  float co      = getCO(R);
  float co2     = getCO2(R);
  float ethanol = getEthanol(R);
  float nh4     = getNH4(R);
  float toluene = getToluene(R);
  float acetone = getAcetone(R);

  Serial.print("\nAQI     = ");
  
  float diff = -100*(aqi - R_callib) / R_callib;
  Serial.print(diff);
  //Serial.print(aqi);
  if( diff > 0 ){
    Serial.print("% better");
  }else{
    Serial.print("% worse");
  }
  Serial.print("(since callibration)\nCO      = ");
  Serial.print(co);

  Serial.print("ppm \nCO2     = ");
  Serial.print(co2);

  Serial.print("ppm \nEthanol = ");
  Serial.print(ethanol);

  Serial.print("ppm \nAmmonia = ");
  Serial.print(nh4);

  Serial.print("ppm \nToluene = ");
  Serial.print(toluene);

  Serial.print("ppm \nAcetone = ");
  Serial.print(acetone);

  Serial.println("ppm\n-------------------");
  calcLED(co2);
}

void loop()
{
  int sv = analogRead(A1);
  R      = ( (1024/sv) * 5.0 - 1.0)*RLOAD;
  disp(sv);

delay(2500);
}

