#include <Filters.h>
#include <PID_v1.h>

const float filterFrequency = 1.0 ;
const float pi = 3.14159265358979323846;
const int diff = 5;
const int lowestPin = 2;
const int highestPin = 15;
double kp=2;
double ki=4;
double kd=4;



class Modulo
{
  public:
  Modulo():
  miPID(&in, &out, &out_new, kp, ki, kd, DIRECT)
  {
      miPID.SetMode(AUTOMATIC);
  }
  int pos[2];
 double in, out;
 double out_new=0;
 PID miPID;
  void procesar (double val)
  {
    in=val-out_new;
    miPID.Compute();
    if(abs(out-out_new)>diff)
    {
      out_new=out;
      printValue();
    }
  }
  void printValue()
  {
    Serial.print(pos[0]);
    Serial.print(" ");
    Serial.print(pos[1]);
    Serial.print(",");
    Serial.println(out);
  }
};


Modulo modulos[highestPin+1];


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
  modulos[2].pos[0] = 4;
  modulos[2].pos[1]=6;
  modulos[3].pos[0] = 4;
  modulos[3].pos[1] = 5;
  //modulos[4].pos = {};
  modulos[5].pos[0] = 3;
  modulos[5].pos[1] = 6;
  modulos[6].pos[0] = 3;
  modulos[6].pos[1] = 5;
  modulos[7].pos[0] = 3;
  modulos[7].pos[1] = 4;
  modulos[8].pos[0] = 3;
  modulos[8].pos[1] = 3;
  modulos[9].pos[0] = 3;
  modulos[9].pos[1] = 2;
  modulos[10].pos[0] = 2;
  modulos[10].pos[1] = 1;
  modulos[11].pos[0] = 1;
  modulos[11].pos[1] = 2;
  modulos[12].pos[0] = 1;
  modulos[12].pos[1] = 3;
  modulos[13].pos[0] = 1;
  modulos[13].pos[1] = 4;
  modulos[14].pos[0] = 1;
  modulos[14].pos[1] = 5;
  modulos[15].pos[0] = 1;
  modulos[15].pos[1] = 6;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  for (int thisPin = lowestPin; thisPin <= highestPin; thisPin++) {
   
    //modulos[thisPin].setup();
    pinMode(thisPin, INPUT);
    //modulos[thisPin].lowpass.test();
   
  }
  inicializarPosiciones();
  //delay(1500);
  
  /*for (int i=lowestPin; i<highestPin+1; i++)
    {
      if (i==4)
        continue;
      modulos[i].procesar();
    }*/
}

void loop() {
  // put your main code here, to run repeatedly:
  double var;
    for (int i=lowestPin; i<highestPin+1; i++)
    {
      if (i==4){
        continue;
      }
      var=analogRead(i);
      modulos[i].procesar(var);
      //modulos[i].lowpass.print();
      //delay (10);
    }
    
}
