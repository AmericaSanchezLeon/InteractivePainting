
#include <Servo.h>

//------ LEDS ------//
//leds para ajos
int LEDajo1 = 2;
int LEDajo2 = 3;
int LEDajo3 = 4;
int randomNumber = 0;

//int ledprueba = 12;

//Led horno
int LEDhorno = 8;

//------ SENSOR DE MOVIMIENTO ------//
int sensorMov = A0;
int sensorValor = 0;

//------ SERVOMOTORES ------//

//Servo buey
Servo servobuey; 
int posbuey = 0;

//Servo cuchillo
Servo servoCuchi;
int poscuchillo = 0;

//Servo Cazo
Servo servoCazo;
int poscazo = 0;

//Servo Maiz
Servo servoMaiz;
int posmaiz = 0;

//------ SET UP ------//
void setup() {

  //Inicializar el puerto serial
  Serial.begin(9600);
  
  //Inicializar leds
  pinMode (LEDajo1, OUTPUT);
  pinMode (LEDajo2, OUTPUT);
  pinMode (LEDajo3, OUTPUT);
  pinMode (LEDhorno, OUTPUT);

  //Inicializar sensor de movimiento
  pinMode (sensorMov, INPUT); 
  
  //Inicializar los servos
  servobuey.attach(9);
  servoCuchi.attach(6); //cinta rojo 
  servoCazo.attach(5); // cinta verde
  servoMaiz.attach(7); // cinta amarilla

  //Semilla para ajos random
  randomSeed(analogRead(A1));
}

//------ FUNCIONES LEDS------//
void prendeAjos()
{
  randomNumber = random(2,5); //genera número aleatorio entre 2 y 5 (los pines+1)

  digitalWrite(randomNumber, HIGH);
  delay (500);
  digitalWrite(randomNumber, LOW); 
  delay (100);
}

void prendeHorno()
{
  digitalWrite (LEDhorno, HIGH);
  delay(1000);
}

void apagaHorno()
{
  digitalWrite (LEDhorno, LOW);
  delay(1000);
}

//----- FUNCIONES SERVOMOTORES -----//

void entraBuey()
{
  //for (posbuey = 0; posbuey <=90; posbuey +5)
  //{
    servobuey.write(90);
    delay (1000);
  //}
}

void saleBuey()
{
  //for (posbuey = 90; posbuey>0; posbuey -5)
  //{
    servobuey.write(0);
    delay (1000);
  //}
}

void moverCuchillo()
{
   for (poscuchillo = 0; poscuchillo <=90; poscuchillo ++)
   {
    servoCuchi.write(poscuchillo); 
    delay (15);
   }
  
  for (poscuchillo = 90; poscuchillo>0; poscuchillo --)
  {
    servoCuchi.write(poscuchillo); 
    delay (15);
  }
}

void moverManoCazo()
{
   for (poscazo = 0; poscazo <=180; poscazo ++)
   {
    servoCazo.write(poscazo); 
    delay (15);
   }
  
  for (poscazo = 180; poscazo>0; poscazo--)
  {
    servoCazo.write(poscazo); 
    delay (15);
  }
}

void molerMaiz()
{
  for (posmaiz = 0; posmaiz <=180; posmaiz ++)
  {
    servoMaiz.write(posmaiz); 
    delay (15);
  }
  
  for (posmaiz = 180; posmaiz>0; posmaiz--)
  {
    servoMaiz.write(posmaiz); 
    delay (15);
  }
}

//------ FUNCION LOOP ------//
void loop() {
  
 //Acciones para el sensor de movimiento
 //Compara contra LOW para infrarrojo y para sensor de movimiento con HIGH
 sensorValor = digitalRead(sensorMov);
  if (sensorValor == LOW)
  {
    prendeHorno();
    entraBuey();
  }
  else
  {
    apagaHorno();
    saleBuey();
  }
  
 //Acciones para el puerto serial
 
 if (Serial.available() > 0)
  {
    char option = Serial.read();

    if ( option == '1') //pimiento
    {
      prendeAjos();
    }
    else
    {
      if ( option == '2') //Limon/calabaza verde
      {
        molerMaiz();
      }
      else
      {
        if ( option == '3')//manzana
        {
          //no hace nada
          prendeAjos();
        }
        else
        {
          if ( option == '4') //cebolla
          {
            moverCuchillo();
          }
          else
          {
            if ( option == '5') //chile
            {
              //no hace nada 
            }
            else
            {
              if ( option == '6') //palita
              {
                moverManoCazo();
              }
            }
          }
        }
      }
      
    }
    
  }//fin Serial.avaliable
 
}
