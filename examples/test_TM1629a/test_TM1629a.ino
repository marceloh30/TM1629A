#include <TM1629a.h>

//choose digital pins compatibles with your board
#define STB 7 // Strobe digital pin
#define CLK 9 // clock digital pin
#define DIO 8 // data digital pin

TM1629a tm(CLK,DIO,STB);

//numbers just to test the display
volatile unsigned int number1 = 173;
volatile unsigned int number2 = 5;

void setup() {

  tm.reset();
  tm.displaySetBrightness(PULSE14_16);
  //tm.test();

}

void writeDisplays(unsigned int number, bool isSuperiorDisplay){
  const uint8_t numbers[] = {
    number/10000 % 10,
    number/1000 % 10,
    number/100 % 10,
    number/10 % 10,
    number % 10
  };

  if(isSuperiorDisplay){
    for (uint8_t i=0;i<sizeof(numbers);i++){
      tm.displayVal(14-i, numbers[i]);

    }
  }
  else{
    for (uint8_t i=0;i<sizeof(numbers);i++){
      tm.displayVal(14-i-5, numbers[i]);
    }
  }

}

void delayMillis(int ms) {
  unsigned long t = millis();
  while (millis() < t + ms);
}

void loop() {


  writeDisplays(number1,true);
  writeDisplays(number2,false);

  delayMillis(10);
  
  number1+=11;
  number2+=11;
  if(number1>=25000){
    number1=0;
  }
  if(number2>=25000){
    number2=0;
  }
}