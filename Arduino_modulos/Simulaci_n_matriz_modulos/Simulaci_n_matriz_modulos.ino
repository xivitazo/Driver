#include <Filters.h>

const float filterFrequency = 15.0 ;
const float pi = 3.14159265358979323846;
const int diff = 5;
const int lowestPin = 2;
const int highestPin = 15;


typedef struct
{
  int pos[2], pin;
  int var, varLP, varLP_new;
  FilterOnePole lowpass;
  void procesar ()
  {
    var=analogRead(pin);
    lowpass.input(var);
    varLP_new=lowpass.output();
    if (varLP_new - varLP>=diff || varLP_new-varLP<=-diff)
    {
      printValue();
      varLP=varLP_new;
    }
  }
  void printValue()
  {
    Serial.print(pos[1]);
    Serial.print(" ");
    Serial.print(pos[2]);
    Serial.print(",");
    Serial.println(varLP_new);
  }
}modulo;
modulo modulos[highestPin+1];


/*void procesar (int pin)
{
  modulos[pin].var=analogRead(pin);
  modulos[pin].lowpass.input(modulos[pin].var);
  modulos[pin].varLP_new=modulo[pin].lowpass.output();
  if (abs(modulos[pin].varLP_new - modulos[pin].varLP)>=diff)
  {
    Serial.println(modulos[pin].pos[1] + " " + modulos[pin].pos[2] + "," + (float)(modulos[pin].varLP_new/1023));
    modulos[pin].varLP=modulos[pin].varLP_new;
  }
}*/

void inicializarPosiciones()
{
  modulos[2].pos[1] = 4;
  modulos[2].pos[2]=6;
  modulos[3].pos[1] = 4;
  modulos[3].pos[2] = 5;
  //modulos[4].pos = {};
  modulos[5].pos[1] = 3;
  modulos[5].pos[2] = 6;
  modulos[6].pos[1] = 3;
  modulos[6].pos[2] = 5;
  modulos[7].pos[1] = 3;
  modulos[7].pos[2] = 4;
  modulos[8].pos[1] = 3;
  modulos[8].pos[2] = 3;
  modulos[9].pos[1] = 3;
  modulos[9].pos[2] = 2;
  modulos[10].pos[1] = 2;
  modulos[10].pos[2] = 1;
  modulos[11].pos[1] = 1;
  modulos[11].pos[2] = 2;
  modulos[12].pos[1] = 1;
  modulos[12].pos[2] = 3;
  modulos[13].pos[1] = 1;
  modulos[13].pos[2] = 4;
  modulos[14].pos[1] = 1;
  modulos[14].pos[2] = 5;
  modulos[15].pos[1] = 1;
  modulos[15].pos[2] = 6;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  for (int thisPin = lowestPin; thisPin <= highestPin; thisPin++) {
    modulos[thisPin].var=0;
    modulos[thisPin].varLP=0;
    modulos[thisPin].varLP_new=0;
    modulos[thisPin].pin=thisPin;
    modulos[thisPin].lowpass.setFilter(LOWPASS, 1/(2*pi/filterFrequency),0.0);
    pinMode(thisPin, INPUT);
  }
  inicializarPosiciones();
  /*for (int i=lowestPin; i<highestPin+1; i++)
    {
      if (i==4)
        continue;
      modulos[i].procesar();
    }*/
}

void loop() {
  // put your main code here, to run repeatedly:
    for (int i=lowestPin; i<highestPin+1; i++)
    {
      if (i==4)
        continue;
      modulos[i].procesar();
    }
    delay (10);
}
