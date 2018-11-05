/*
HOW TO USE

Install on Blink
Connect Serial to Blink
To enter a new hue, type and send a 3-digit byte value (0-255)
You MUST type all three digits, including 0s (001, 010, etc.)
The monitor will print your current sent value (ignore the two, often unusual values above it)
Type A, B, or C (must be uppercase) and send it to assign that hue to that portion of the Blink
Doing this successfully will set the Blink to "orderly" mode where all three hues are displayed evenly on the face
Single-click the blink to reassign those hues randomly to all faces
*/

#include "Serial.h"
ServicePortSerial sp;

byte hues[3] = {0, 128, 196};
char inputReceived;
byte numbersReceived[3];
byte fullNumber;

void setup() {
  // put your setup code here, to run once:
  sp.begin();
  orderlyColor();
}

void loop() {
  // put your main code here, to run repeatedly:
  //listen for serial commands
  inputReceived = sp.read();

  //print received serial input
  switch (inputReceived) {
    case 'A':
      sp.println("assigning A ");
      sp.print(fullNumber);
      hues[0] = fullNumber;
      orderlyColor();
      break;
    case 'B':
      sp.println("assigning B ");
      sp.print(fullNumber);
      hues[1] = fullNumber;
      orderlyColor();
      break;
    case 'C':
      sp.println("assigning C ");
      sp.print(fullNumber);
      hues[2] = fullNumber;
      orderlyColor();
      break;
    case '0':
      appendNumber(0);
      break;
    case '1':
      appendNumber(1);
      break;
    case '2':
      appendNumber(2);
      break;
    case '3':
      appendNumber(3);
      break;
    case '4':
      appendNumber(4);
      break;
    case '5':
      appendNumber(5);
      break;
    case '6':
      appendNumber(6);
      break;
    case '7':
      appendNumber(7);
      break;
    case '8':
      appendNumber(8);
      break;
    case '9':
      appendNumber(9);
      break;
  }

  if (buttonSingleClicked()) {
    randomlyColor();
  }
}

void randomlyColor() {
  setColor(OFF);
  FOREACH_FACE(f) {
    if (rand(2) > 0) {
      setColorOnFace(makeColorHSB(hues[rand(2)], 255, 255), f);
    }
  }
}

void orderlyColor() {
  setColorOnFace(makeColorHSB(hues[0], 255, 255), 0);
  setColorOnFace(makeColorHSB(hues[0], 255, 255), 1);
  setColorOnFace(makeColorHSB(hues[1], 255, 255), 2);
  setColorOnFace(makeColorHSB(hues[1], 255, 255), 3);
  setColorOnFace(makeColorHSB(hues[2], 255, 255), 4);
  setColorOnFace(makeColorHSB(hues[2], 255, 255), 5);
}

void appendNumber (byte num) {
  numbersReceived[0] = numbersReceived[1];
  numbersReceived[1] = numbersReceived[2];
  numbersReceived[2] = num;
  fullNumber = numbersReceived[0] * 100 + numbersReceived[1] * 10 + numbersReceived[2];
  sp.println(fullNumber);
}


