#include <TM1629a.h>

//choose digital pins compatibles with your board
#define STB 7 // Strobe digital pin
#define CLK 9 // clock digital pin
#define DIO 8 // data digital pin

TM1629a tm(CLK,DIO,STB);
volatile unsigned int numero1 = 173;
volatile unsigned int numero2 = 5;

void setup() {

  tm.reset();
  tm.displaySetBrightness(PULSE14_16);
  //tm.test();

}

void escribirDisplay(unsigned int numero, bool displaySuperior){
  const uint8_t textoNum[] = {
    numero/10000 % 10,
    numero/1000 % 10,
    numero/100 % 10,
    numero/10 % 10,
    numero % 10
  };

  if(displaySuperior){
    for (uint8_t i=0;i<sizeof(textoNum);i++){
      tm.displayValTest(14-i, textoNum[i]);

    }
  }
  else{
    for (uint8_t i=0;i<sizeof(textoNum);i++){
      tm.displayValTest(14-i-5, textoNum[i]);
    }
  }

}

void delayMillis(int ms) {
  unsigned long t = millis();
  while (millis() < t + ms);
}

void loop() {


  escribirDisplay(numero1,true);
  escribirDisplay(numero2,false);

  delayMillis(10);
  
  numero1+=11;
  numero2+=11;
  if(numero1>=25000){
    numero1=0;
  }
  if(numero2>=25000){
    numero2=0;
  }
}