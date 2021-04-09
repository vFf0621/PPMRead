#define channumber 8 //number of channels
#define filter 10 // Glitch Filter
int channel[channumber]; //read Channel values
int lastReadChannel[channumber]; //Last  values readed
int counter=0; //couter


void setup()
{
  Serial.begin(2000000); //Serial Begin
  pinMode(4, INPUT); //Pin 4 as input
  pinMode(13, OUTPUT); // Led pin 13
}

void loop()
{
    Serial.println(String(map(channel[0], 695, 1532, 1095, 1935)) + ' ' + String(map(channel[1], 695, 1532, 1095, 1935)) + ' ' + String(map(channel[2], 695, 1532, 1095, 1935)) + ' ' + String(map(channel[3], 695, 1532, 1095, 1935)));

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
 channel[i]=(lastReadChannel[i]+channel[i])/2; //Average the last pulse eith the current pulse
 counter++; //increment counter
 }

    }
    if(counter > filter)
    {


 for(int i = 0; i <= channumber-1; i++) //Cycle to print values
 {

   lastReadChannel[i]=channel[i];
 }
 if(channel[4] > 1000) //If channel 5 is > than 500 turn on the led
 {
   digitalWrite(13, HIGH);
 }
 else
 {
   digitalWrite(13, LOW);//If not turn it off
 }
 counter=0;//Restart counter.
    }
  } 
