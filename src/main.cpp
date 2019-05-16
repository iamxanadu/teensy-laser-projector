#include <Arduino.h>

#include <SPI.h>
#include <PacketSerial.h>

#define X_OUT A21
#define Y_OUT A22

PacketSerial ps;

float xpos = 0;
float ypos = 0;

void onPacketReceived(const uint8_t *buffer, size_t size);

// Moves the laser to the extremes of its movement area to see how big the display will be.
void testSquare()
{
  analogWrite(X_OUT, 255);
  analogWrite(Y_OUT, 255);

  delay(1500);

  analogWrite(X_OUT, 255);
  analogWrite(Y_OUT, 0);

  delay(1500);

  analogWrite(X_OUT, 0);
  analogWrite(Y_OUT, 0);

  delay(1500);

  analogWrite(X_OUT, 0);
  analogWrite(Y_OUT, 255);

  delay(1500);

}

void setup()
{
  ps.begin(230400);
  ps.setPacketHandler(&onPacketReceived);

  pinMode(X_OUT, OUTPUT);
  pinMode(Y_OUT, OUTPUT);
}

void loop()
{
  //testSquare();

  int x = map(xpos, -1.0, 1.0, 0, 255);
  int y = map(ypos, -1.0, 1.0, 0, 255);

  analogWrite(X_OUT, x);
  analogWrite(Y_OUT, y);

  ps.update();
}

// PacketSerial Callback Function
void onPacketReceived(const uint8_t *buffer, size_t size)
{
  
  if(size > 7){
    // update coordinates
    memcpy(&xpos, buffer, 4);
    memcpy(&ypos, buffer + 4, 4);
  }

}