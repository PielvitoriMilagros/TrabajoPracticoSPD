#include <LiquidCrystal.h>

LiquidCrystal lcd(7,8,9,10,11,12); //RS EN d4 d5 d6 d7
//VARIABLES DE TIEMPO
unsigned long tiempo=0;
int seg=0;
int minu=0;
int hora=0;
int boton = 5;
int estadoBoton=0;
int estadoAnterior=1;
//VARIABLES DE TEMPERATURA
int botonTemp = 6;
int estadoBotonTemp=0;
int estadoTempAnterior=0;
int pinLedA=4;
int pinLedV=3;
int pinLedR=2;

void setup() {  
  lcd.begin(16,2);
  pinMode(boton, INPUT);
  pinMode(botonTemp, INPUT);
  pinMode(pinLedA,OUTPUT);
  pinMode(pinLedV,OUTPUT);
  pinMode(pinLedR,OUTPUT);
  
}

void loop() {
  //SE LEE EL ESTADO DE LOS BOTONES
  estadoBoton = digitalRead(boton);
  estadoBotonTemp = digitalRead(botonTemp);
  
  //SE LLAMA A LA FUNCION CENTIGRADOS PARA QUE INFORME TEMPERATURA Y LEDS AUNQUE NO HAYA CAMBIADO DE HORA A TEMPERATURA
  centigrados();
  
  
  if(estadoBoton==1 && estadoAnterior==0)//SE LLAMA A LA FUNCION RELOJ SI EN UN MOMENTO PREVIO NO SE LA LLAMÓ
  {    
    lcd.clear();
    reloj();
    delay(500);
    estadoAnterior=1;     
    estadoBoton=estadoAnterior;
  }
  else if(estadoBoton==1 && estadoAnterior==1)//SI EN UN MOMENTO PREVIO SE LA LLAMÓ A LA FUNCION RELOJ, SE LLAMA A LA OTRA FUNCION TEMPERATURA
  {    
    lcd.clear();
    temperatura(estadoTempAnterior);
    delay(500);
    estadoAnterior=0;
    estadoTempAnterior=estadoBotonTemp;        
  } 
  else if(estadoBoton==0 && estadoAnterior==0)
  {
    estadoBoton = digitalRead(boton);
    if(estadoTempAnterior==1 && estadoBotonTemp==1)
    {
      estadoTempAnterior=0;        
    }
    else if(estadoTempAnterior==0 && estadoBotonTemp==1)
    {
      estadoTempAnterior=1;      
    }
    temperatura(estadoTempAnterior);    
  }
  else if(estadoBoton==0 && estadoAnterior==1)
  {
    estadoBoton = digitalRead(boton);
    reloj();
  }
  
}

void reloj(){  
  tiempo=millis();  
  seg=((tiempo/1000)%60);
  minu=((tiempo/60000)%60);
  hora=(tiempo/3600000);
  lcd.setCursor(9,0);
  lcd.print(":"); 
  
  if(seg<10){
    lcd.setCursor(10,0);
    lcd.print("0");    
    lcd.setCursor(11,0);  
    lcd.print(seg);    
  }
  else{
    lcd.setCursor(10,0);  
    lcd.print(seg);
  }
  
  if(minu<10){
    lcd.setCursor(7,0);
    lcd.print("0");
    lcd.setCursor(8,0);
    lcd.print(minu);    
  }
  else{
    lcd.setCursor(7,0); 
    lcd.print(minu);
  }
  
  lcd.setCursor(6,0);
  lcd.print(":");  
  
   
  if(hora<10){
    lcd.setCursor(4,0); 
    lcd.print("0");
    lcd.setCursor(5,0); 
    lcd.print(hora);    
  }
  else{
    lcd.setCursor(4,0); 
    lcd.print(hora);
  }  
  delay(1000); 
}

void temperatura(int estadoBotonTemp){  
  float Temp=centigrados();
  float Tempf= farenheit(Temp);
  
  if(estadoBotonTemp==0){
    lcd.setCursor(4,0);
  	lcd.print("C=");
  	lcd.setCursor(6,0);
  	lcd.print(Temp);
  }else{
    lcd.setCursor(4,0);
  	lcd.print("F=");
  	lcd.setCursor(6,0);
  	lcd.print(Tempf);
  }
  delay(500);  
}

float centigrados(){
  int dato;
  float c;
  dato = analogRead(A0);
  c = (500.0 * dato)/1023;
  if(c<20.0){
  	digitalWrite(pinLedA, HIGH);
    digitalWrite(pinLedV, LOW);
    digitalWrite(pinLedR, LOW);
  }else if(c>=20.0 && c<=25.0){
  	digitalWrite(pinLedA, LOW);
    digitalWrite(pinLedV, HIGH);
    digitalWrite(pinLedR, LOW);
  } else{
    digitalWrite(pinLedA, LOW);
    digitalWrite(pinLedV, LOW);
    digitalWrite(pinLedR, HIGH);
  }
  return(c);
}

float farenheit(float centigrados){
  float Faren;
  Faren = centigrados*1.8 + 32;
  return(Faren);
}
