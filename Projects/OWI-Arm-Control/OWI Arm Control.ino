/*
inertial Measurement Unit calibration code by Tamojit Saha & Sandeepan Sengupta
*/


#include<Wire.h>
const int MPU=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp;
int16_t GyX,GyY,GyZ;
int in1=2,in2=3;      //FOR MPU6050
int in3=4,in4=5;      //FOR MPU6050
int g1=7;            //gripper motor
int g2=8;
int m1=9;
int m2=10;
int a0=0;            //flex sensor 1 analog input to PIN A0
int a1=1;            //flex sensor 2 analog input to PIN A1

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(g1,OUTPUT);
pinMode(g2,OUTPUT);
  pinMode(m1,OUTPUT);
pinMode(m2,OUTPUT);
pinMode(a0,INPUT);

  Serial.begin(9600);
  while (!Serial) {
    ; // waiting for available serial port (COM#) to connect.
  }
}
void loop()
  {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  GyX=Wire.read()<<8|Wire.read();
  GyY=Wire.read()<<8|Wire.read();
  GyZ=Wire.read()<<8|Wire.read();
 
  AcX=map(AcX,-15999,15999,-255,255);
  AcY=map(AcY,-15999,15999,-255,255);
  AcZ=map(AcZ,-15999,15999,-255,255);
  
  int a=analogRead(a0);
int b=map(a,400,700,0,120);
 int c=analogRead(a1);
int d=map(c,400,700,0,120);

//.......Flex sensor-1 Motor Control 1.......[GRIPPER]
//Code for MOTOR 1

if(b>0 && b<=30){

digitalWrite(g1,HIGH);
digitalWrite(g2,LOW);

}

else if(b>=95)

{
digitalWrite(g1,LOW);
digitalWrite(g2,HIGH);
}

else
{
digitalWrite(g1,LOW);
digitalWrite(g2,LOW);
}




//.......Flex Sensor-2 Motor Control 2

//Code for MOTOR 2
if(d>0 && d<=30){

digitalWrite(m1,HIGH);
digitalWrite(m2,LOW);

}

else if(d>=95)

{
digitalWrite(m1,LOW);
digitalWrite(m2,HIGH);
}

else
{
digitalWrite(m1,LOW);
digitalWrite(m2,LOW);
}



   //........MPU6050 Motor Control............
  //Code for MOTOR 3&4.................
   if(AcX>140)
     {
       digitalWrite(in1,HIGH);
       digitalWrite(in2,LOW); 
       
     
     }
    
    else if((AcX>=-80 && AcX<=50) && (AcY>=-80 && AcY<=80))
      {
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW); 
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW); 
      }
   
    else if(AcX<=-165)  
      {
       digitalWrite(in1,LOW);
       digitalWrite(in2,HIGH);
      }
  
   
   
   else if(AcY>230)
     {
       digitalWrite(in3,HIGH);
        digitalWrite(in4,LOW); 
     
     }
    
    else if((AcY>=-80 && AcY<=100)&&(AcX>=-80 && AcX<=50))
      {
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW); 
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW); 
      }
   
    else if(AcY<=-170)  
      {
       digitalWrite(in3,LOW);
       digitalWrite(in4,HIGH);
      }
      
     
      
 
  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  Serial.print("    AcX = "); Serial.print(AcX);
  Serial.print("    AcY = "); Serial.print(AcY);
  Serial.print("    AcZ = "); Serial.print(AcZ);

  Serial.print("\n");
 
 Serial.print("Flex Reading:");
Serial.print(b);
Serial.print("\n");
 Serial.print("\n");
  
  delay(80); // Deley is for debugging only

  }

