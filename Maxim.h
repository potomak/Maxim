/*
  Maxim.h - Maxim library
  Copyright (C) 2010 Giovanni Cappellotto. All rights reserved.
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/

#ifndef Maxim_h
#define Maxim_h

#include <WProgram.h>
#include <inttypes.h>


/* Version numbers for the protocol.  The protocol is still changing, so these
 * version numbers are important.  This number can be queried so that host
 * software can test whether it will be compatible with the currently
 * installed firmware. */
#define MAXIM_MAJOR_VERSION   0 // for non-compatible changes
#define MAXIM_MINOR_VERSION   1 // for backwards compatible changes

// define max7219 registers
#define MAX7219_REG_NOOP         0x00
#define MAX7219_REG_DIGIT0       0x01
#define MAX7219_REG_DIGIT1       0x02
#define MAX7219_REG_DIGIT2       0x03
#define MAX7219_REG_DIGIT3       0x04
#define MAX7219_REG_DIGIT4       0x05
#define MAX7219_REG_DIGIT5       0x06
#define MAX7219_REG_DIGIT6       0x07
#define MAX7219_REG_DIGIT7       0x08
#define MAX7219_REG_DECODEMODE   0x09
#define MAX7219_REG_INTENSITY    0x0a
#define MAX7219_REG_SCANLIMIT    0x0b
#define MAX7219_REG_SHUTDOWN     0x0c
#define MAX7219_REG_DISPLAYTEST  0x0f


// TODO make it a subclass of a generic Serial/Stream base class
class MaximClass
{
  int dataIn;
  int load;
  int clock;
  
  int maxInUse;
  
public:
  /* MaximClass constructor */
  MaximClass();
  
  void setup(int, int, int, int);
  
  void single(byte, byte);
  void all(byte, byte);
  void one(byte, byte, byte);

private:
  void putByte(byte);
};

extern MaximClass Maxim;

#endif /* Maxim_h */

