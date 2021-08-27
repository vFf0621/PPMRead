#define channumber 8 //How many channels have your radio???
#define filter 10 // Glitch Filter
int channel[channumber]; //read Channel values
int estimation[channumber]; //read Channel values
int lastReadChannel[channumber]; //Last  values readed
int conta=0; //couter
#include <SimpleKalmanFilter.h>
SimpleKalmanFilter Thro(0.001, 0.001, 0.000001);
SimpleKalmanFilter Yaw(0.001, 0.001, 0.000001);
SimpleKalmanFilter Pitch(0.001, 0.001, 0.000001);
SimpleKalmanFilter Roll(0.001, 0.001, 0.000001);



void setup()
{
  Serial.begin(2000000); //Serial Begin
  pinMode(4, INPUT); //Pin 4 as input

}

void loop()
{
   float x1 = Roll.updateEstimate(float(map(channel[0], 694, 1531, 1099, 1939)));
   float x2 = Pitch.updateEstimate(float(map(channel[1], 694, 1531, 1099, 1939)));
   float x3 = Thro.updateEstimate(float(map(channel[2], 694, 1531, 1099, 1939)));
   float x4 = Yaw.updateEstimate(float(map(channel[3], 694, 1531, 1099, 1939)));
    Serial.println(channel[0]);

  if(pulseIn(4, HIGH) > 3000) //If pulse > 3000 useconds, continues
  {
    for(int i = 0; i <= channumber-1; i++) //Read the pulses of the channels
    {
 channel[i]=pulseIn(4, HIGH);
 
    }
    for(int i = 0; i <= channumber-1; i++) //Average the pulses     { 
    if((channel[i] > 2000) || (channel[i] <100))//If channel > max range, chage the value to the last pulse
 {
  channel[i]= lastReadChannel[i];
 }
 else
 {
 conta++; //increment counter
 
 }

    }
    if(conta > filter)//If counter is > than filter, then prints values
    {


 for(int i = 0; i <= channumber-1; i++) //Cycle to print values
 {

   lastReadChannel[i]=channel[i];
 }

 conta=0;//Restart counter.
    }
  } 
