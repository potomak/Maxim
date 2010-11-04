/* code for max 7219 from maxim, 
reduced and optimised for useing more then one 7219 in a row,
______________________________________

 Code History:
 --------------

The orginal code was written for the Wiring board by:
 * Nicholas Zambetti and Dave Mellis /Interaction Design Institute Ivrea /Dec 2004
 * http://www.potemkin.org/uploads/Wiring/MAX7219.txt

First modification by:
 * Marcus Hannerstig/  K3, malmÔøΩ hÔøΩgskola /2006
 * http://www.xlab.se | http://arduino.berlios.de

This version is by:
 * tomek ness /FH-Potsdam / Feb 2007
 * http://design.fh-potsdam.de/ 

 * @acknowledgements: eric f. 

-----------------------------------

General notes: 


-if you are only using one max7219, then use the function maxSingle to control
 the little guy ---maxSingle(register (1-8), collum (0-255))

-if you are using more then one max7219, and they all should work the same, 
then use the function maxAll ---maxAll(register (1-8), collum (0-255))

-if you are using more than one max7219 and just want to change something
at one little guy, then use the function maxOne
---maxOne(Max you wane controll (1== the first one), register (1-8), 
collum (0-255))

/* During initiation, be sure to send every part to every max7219 and then
 upload it.
For example, if you have five max7219's, you have to send the scanLimit 5 times
before you load it-- other wise not every max7219 will get the data. the
function maxInUse  keeps track of this, just tell it how many max7219 you are
using.
*/
#include <Maxim.h>

boolean debug_led = true;

int vel = 100;

int dataIn = 10;
int load = 9;
int clock = 8;

int maxInUse = 1;    //change this variable to set how many MAX7219's you'll use

Maxim maxim(dataIn, load, clock, maxInUse);

void setup () {
  //beginSerial(9600);
  Serial.begin(9600);
  //digitalWrite(13, HIGH);
}  

void loop () {
  //if you use more then one max7219 the second one should look like this
  int my_max_num = 1;
  int values[] = {1, 2, 4, 8, 16, 32, 64, 128};

  if(debug_led) {
    Serial.print("\n\n");
    Serial.print("max, reg, col:\n");
  }
  for(int my_delta = 0; my_delta < vel; my_delta += 5) {
    for(int my_reg = 1; my_reg < 5; my_reg++){
      for(int my_col_pow = 7; my_col_pow >= 0; my_col_pow--){
        if(debug_led) {
          Serial.print("\n");
          Serial.print(my_max_num);
          Serial.print(", ");
          Serial.print(my_reg);
          Serial.print(", ");
          Serial.print(values[my_col_pow]);
        }
        maxim.one(my_max_num, my_reg, values[my_col_pow]);
        delay(vel-my_delta);
      }
      maxim.one(my_max_num,my_reg,0);
    }
    debug_led = false;
  }
}

