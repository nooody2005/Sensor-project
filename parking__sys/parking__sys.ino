#include <Servo.h>
#include<LiquidCrystal.h>
#define trig 7
#define echo 6
Servo myservo;
int  rs=13 ,en=12, d4=11,d5=10,d6=9,d7=8;
LiquidCrystal lcd (rs,en,d4,d5,d6,d7);
int counter=4 ; 
float dis =0,dur=0;
int SensorPin = 4;
int led1 =3 ; 
int led2 =2 ; 
int led_for_test =1; 
//===================================================================
void setup() 
{                        
  // put your setup code here, to run once:
lcd.begin(16,2); 
Serial.begin(9600);
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);
myservo.attach(5); 
pinMode(SensorPin, INPUT); // for ir sensor 
myservo.write(0); 
pinMode(A0, INPUT); //  for  ldr  sensor 
pinMode(led1,OUTPUT);  // for the led  1 
pinMode(led2,OUTPUT);  // for the led  2
lcd.print(" places: 4");
pinMode(A5,OUTPUT); 
}
// //====================================================================
void l_c_d(int counter)
{  
             // test passed but we need to  make it again  on the real  maket 
  lcd.clear();
  lcd.setCursor(1, 0); 

  if(counter>0)
  {
    lcd.print(" places:");
    lcd.setCursor(0, 1); 
    lcd.print(counter); 
  }
   
   else
  {    
    lcd.clear();
    lcd.print("Sorry no space ");
  }
}
// ======================================================================

float ultra_sonic()
{       //  test passed  
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,HIGH);
  dur=pulseIn(echo,HIGH);
  dis=(dur*.0343)/2;
  // Serial.print(dis);
  // Serial.print("\n");
  delay(100);
  return dis; 
}
//=============================================================================
//  best code for servo  motor to save it from burnning  
void open_servomotor()          // still need to test  
{ 
  for(int i=0 ;i<=90;i++)
  { 
    myservo.write(i);
    delay(15); 
  }

delay(500); 
}
//================================================================================
void close_servomotor()          // still need to test  
{ 
 
  for(int i=90 ;i>0;i--)
  { 
    myservo.write(i);
    delay(15); 
  }

delay(500); 
}

//================================================================================


void controlling_light()
{
  if (analogRead(A0)>=220)
  {   //  modifiy it on the maket 
  // turn on the led 
    digitalWrite(3,HIGH); 
    digitalWrite(2,HIGH);                         /// this part of code to  control the light of the parking depend on (ldr reading) 
                                               //(morning or night)
  }
  else  
  {    //  turn off the led 
    digitalWrite(3,0); 
    digitalWrite(2,0); 
  }
}

//===============================================================================

// bool ir()
// {    ================================== get rid of=============================
// int SensorValue = digitalRead(SensorPin);
// return SensorValue;
// }
// //=================================================================================




void loop() 
{

  controlling_light(); 

//============================================================
  digitalWrite(A5,0); 
  delay(1000);  // just   for  indication
 //===========================================================
  if(ultra_sonic()<=20 && counter>0) /////       modifiy this on the maket 
  {                    /// this part of code in  case of the car Entre the parking 
    open_servomotor(); 
    while(1)  
    {
      if(digitalRead(SensorPin)==0)
      {
        close_servomotor(); 
        counter--;
        l_c_d(counter);
        break; 
      }
    }        
  }

// ================================================================
  else if (digitalRead(SensorPin)==0)                     /// this part of code in  case of the car leave  the parking 
  {
    open_servomotor(); 
    // modifiy on the maket
    while(1)  
    {
      if(ultra_sonic()<=20)
      {
        close_servomotor();
        counter++;
        l_c_d(counter);
        break;
      }  
    }
  }
   
//  Serial.println(digitalRead(SensorPin));     just for testing 
// Serial.println(ultra_sonic()); 
digitalWrite(A5,1); 
delay(1000); 
}