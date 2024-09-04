#include <IRremote.h>
const byte ir_kumanda_pini=2;
const byte OUT1=5;
const byte OUT2=6;
const byte OUT3=7;
const byte OUT4=8;
const byte motor_kontrol_1=9;
const byte motor_kontrol_2=10;
const byte echoPin=11;
const byte trigPin=12;

int hiz=160; //default hız (0-255)

IRrecv ir_alicim(ir_kumanda_pini);
decode_results results;

#define yukari_ok 6166 //İleri git
#define asagi_ok 6167  //Geri git
#define sol_ok 6163    //Sola git
#define sag_ok 6162    //Sağa git
#define p_asagi 6177   //Hızı azalt
#define p_yukari 6176  //Hızı artır
#define durdur 6179    //Durdurur

void setup() {
  pinMode(OUT1,OUTPUT);
  pinMode(OUT2,OUTPUT);
  pinMode(OUT3,OUTPUT);
  pinMode(OUT4,OUTPUT);
  pinMode(motor_kontrol_1,OUTPUT);
  pinMode(motor_kontrol_2,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);

  digitalWrite(motor_kontrol_1,LOW);
  digitalWrite(motor_kontrol_2,LOW);
  digitalWrite(OUT1,LOW);
  digitalWrite(OUT2,LOW);
  digitalWrite(OUT3,LOW);
  digitalWrite(OUT4,LOW);

  ir_alicim.enableIRIn();
  
}

void loop() {
  int mesafe=mesafe_olcumu();
  if(mesafe>70)
  {
    if(ir_alicim.decode(&results))
    {
      switch(results.value)
      {
        case p_yukari:
        if(hiz<255)
        hiz+=5;break;
        
        case p_asagi:
        if(hiz>80)
        hiz-=5;break;
        
        case yukari_ok:
        motor_hareketleri(1,0,0,1,hiz); //OUT1,OUT2,OUT3,OUT4
        break;

        case asagi_ok:
        motor_hareketleri(0,1,1,0,hiz);
        break;
      
        case sol_ok:
        motor_hareketleri(1,0,1,0,hiz);
        break;
     
        case sag_ok:
        motor_hareketleri(0,1,0,1,hiz);
        break;
    
        case durdur:
        motor_hareketleri(0,0,0,0,hiz);
        break;       
        }
        ir_alicim.resume();
    }
  } 
  else
  {
    motor_hareketleri(0,1,1,0,hiz);
    delay(500);
    motor_hareketleri(0,0,0,0,0); //hız değişkenine ne yazarsak yazalım motor çalıştığı sürece önemsizdir.
    }
}

int mesafe_olcumu()
{
  long sure,mesafe;
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  sure=pulseIn(echoPin,HIGH);
  mesafe=sure/29.1/2;
  delay(50);
  return(mesafe);
  }

void motor_hareketleri(int deger1,int deger2, int deger3,int deger4,int hiz)
{
  digitalWrite(OUT1,deger1);
  digitalWrite(OUT2,deger2);
  digitalWrite(OUT3,deger3);
  digitalWrite(OUT4,deger4);
  analogWrite(motor_kontrol_1,hiz);
  analogWrite(motor_kontrol_2,hiz);
  
  }
