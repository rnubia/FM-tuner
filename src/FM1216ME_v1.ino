#include "FM1216.h"

FM1216 tuner;
int tune_val;
uint32_t radio_freq;

void setup()
{
  pinMode(A1, INPUT);
  tune_val = analogRead(A1);
  tuner.init();
  tuner.setStereo(true); 
  radio_freq = 87500 + tune_val * 20;
  radio_freq = (radio_freq / 100) * 100;
  tuner.setFreq(radio_freq);
  Serial.begin(19200);
}

void loop()
{
  int tune_val_tmp = analogRead(A1);
  uint32_t radio_freq_tmp = radio_freq;
  if (abs(tune_val - tune_val_tmp) > 1)
  {
    tune_val = tune_val_tmp;
    radio_freq_tmp = 87500 + tune_val_tmp * 20;
    radio_freq_tmp = (radio_freq_tmp / 100) * 100;
    if (radio_freq != radio_freq_tmp)
    {
      radio_freq = radio_freq_tmp;
      tuner.setFreq(radio_freq);
    }
  }
	Serial.print("Tune value: ");
	Serial.println(tune_val);  
	Serial.print("Radio frequency: ");
	Serial.println(radio_freq);
  delay(100);  // delay in between reads for stability
}





