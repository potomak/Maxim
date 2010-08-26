/*
  Maxim.cpp - Maxim library
  Copyright (C) 2010 Giovanni Cappellotto. All rights reserved.
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/

//******************************************************************************
//* Includes
//******************************************************************************

#include "WProgram.h"
#include "HardwareSerial.h"
#include "Maxim.h"

extern "C" {
#include <string.h>
#include <stdlib.h>
}

//******************************************************************************
//* Constructors
//******************************************************************************

MaximClass::MaximClass() {}

//******************************************************************************
//* Public Methods
//******************************************************************************

void MaximClass::setup(int dataIn_, int load_, int clock_, int maxInUse_)
{
  dataIn   = dataIn_;
  load     = load_;
  clock    = clock_;
  maxInUse = maxInUse_;
  
  pinMode(dataIn, OUTPUT);
  pinMode(clock,  OUTPUT);
  pinMode(load,   OUTPUT);
  
  //initiation of the max 7219
  all(MAX7219_REG_SCANLIMIT, 0x07);      
  all(MAX7219_REG_DECODEMODE, 0x00);  // using an led matrix (not digits)
  all(MAX7219_REG_SHUTDOWN, 0x01);    // not in shutdown mode
  all(MAX7219_REG_DISPLAYTEST, 0x00); // no display test
  for(int e = 1; e <= 8; e++)
  { // empty registers, turn all LEDs off 
    all(e,0);
  }
  all(MAX7219_REG_INTENSITY, 0x0f & 0x0f);    // the first 0x0f is the value you can set
                                              // range: 0x00 to 0x0f
}

//maxSingle is the "easy" function to use for a single max7219
void MaximClass::single(byte reg, byte col)
{
  digitalWrite(load, LOW);       // begin     
  putByte(reg);                  // specify register
  putByte(col);//((data & 0x01) * 256) + data >> 1); // put data   
  digitalWrite(load, LOW);       // and load da shit
  digitalWrite(load,HIGH);
}

// initialize  all  MAX7219's in the system
void MaximClass::all(byte reg, byte col)
{
  digitalWrite(load, LOW);  // begin
  for(int c = 1; c <= maxInUse; c++)
  {
    putByte(reg);  // specify register
    putByte(col);  //((data & 0x01) * 256) + data >> 1); // put data
  }
  digitalWrite(load, LOW);
  digitalWrite(load,HIGH);
}

// maxOne is for adressing different MAX7219's,
// while having a couple of them cascaded
void MaximClass::one(byte maxNr, byte reg, byte col)
{
  digitalWrite(load, LOW);  // begin

  for (int c = maxInUse; c > maxNr; c--)
  {
    putByte(0); // means no operation
    putByte(0); // means no operation
  }

  putByte(reg);  // specify register
  putByte(col);  //((data & 0x01) * 256) + data >> 1); // put data 

  for (int c = maxNr-1; c >= 1; c--)
  {
    putByte(0); // means no operation
    putByte(0); // means no operation
  }

  digitalWrite(load, LOW); // and load da shit
  digitalWrite(load,HIGH);
}

//******************************************************************************
//* Private Methods
//******************************************************************************

void MaximClass::putByte(byte data)
{
  byte i = 8;
  byte mask;
  while(i > 0)
  {
    mask = 0x01 << (i - 1);            // get bitmask
    digitalWrite(clock, LOW);     // tick
    if (data & mask) {                 // choose bit
      digitalWrite(dataIn, HIGH); // send 1
    } else {
      digitalWrite(dataIn, LOW);  // send 0
    }
    digitalWrite(clock, HIGH);    // tock
    --i;                               // move to lesser bit
  }
}

// make one instance for the user to use
MaximClass Maxim;

