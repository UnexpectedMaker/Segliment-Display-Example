// ---------------------------------------------------------------------------
// Created by Seon Rozenblum - seon@unexpectedmaker.com
// Copyright 2018 License: GNU GPL v3 http://www.gnu.org/licenses/gpl-3.0.html
//
// Required libraries
// Adafruit_MCP23017
// ---------------------------------------------------------------------------

#include <Wire.h>
#include "Adafruit_MCP23017.h"

typedef struct 
{
  char id;
  uint16_t leds;
} CharacterX;

// Available characters the segliment display can show            
const byte ARRAY_SIZE = 49;

CharacterX characters_led[ ARRAY_SIZE ] {
  { ' ', 0b0000000000000000 },
  { '0', 0b0000000000111111 }, 
  { '1', 0b0000000010000110 },
  { '2', 0b0000000001011011 },
  { '3', 0b0000000001001111 },
  { '4', 0b0000000001100110 },
  { '5', 0b0000000001101101 },
  { '6', 0b0000000001111100 },
  { '7', 0b0001000010000001 },
  { '8', 0b0000000001111111 },
  { '9', 0b0000000001100111 },
  { 'a', 0b0000000001110111 },
  { 'b', 0b0001100001001111 },
  { 'c', 0b0000000000111001 },
  { 'd', 0b0001100000001111 },
  { 'e', 0b0000000001111001 },
  { 'f', 0b0000000001110001 },
  { 'g', 0b0000010000111001 },
  { 'h', 0b0000000001110110 },
  { 'i', 0b0001100000001001 },
  { 'j', 0b0000000000011110 },
  {'k', 0b0000010010110000 },
  {'l', 0b0000000000111000},
  {'m', 0b0000000110110110},
  {'n', 0b0000010100110110},
  {'o', 0b0000000000111111},
  {'p', 0b0000000001110011},
  {'q', 0b0000010000111111},
  {'r', 0b0000010010110001},
  {'s', 0b0000000101001101},
  {'t', 0b0001100000000001},
  {'u', 0b0000000000111110},
  {'v', 0b0000001010110000},
  {'w', 0b0000011000110110},
  {'x', 0b0000011110000000},
  {'y', 0b0001000110000000},
  {'z', 0b0000001010001001},
  {'*', 0b0001111110000000},
  {'+', 0b0001100001000000},
  {'-', 0b0000000001000000},
  {'/', 0b0000001010000000},
  {'<', 0b0000010010000000},
  {'>', 0b0000001100000000},
  {'|', 0b0001100000000000},
  {'$', 0b0001100001101101},
  {'[', 0b0000000000111001},
  {']', 0b0000000000001111},
  {'=', 0b0000000001001000},
  {'_', 0b0000000000001000},
};

// Create a reference for each display
Adafruit_MCP23017 mcp[1];
  
void setup()
{ 
  // Initialise each display with it's I2C address
  mcp[0].begin(1);      

  // Set each IO on the display to be outputs
  for ( int i = 0; i < 15; i++ )
    mcp[0].pinMode(i, OUTPUT);

  // clear the display
  ClearDisplay(0);

  // show some characters
  ShowCharacter( 0, 'h' );
  delay(500);
  ShowCharacter( 0, 'e' );
  delay(500);
  ShowCharacter( 0, 'l' );
  delay(500);
  ShowCharacter( 0, 'l' );
  delay(500);
  ShowCharacter( 0, 'o' );
  delay(500);

  // clear the display
  ClearDisplay(0);
}

// show a character on a display
void ShowCharacter( byte disp, byte c )
{
  ShowBytes( 0, FindCharacterX( c ).leds );
}

// set bytes directly on a display
void ShowBytes( byte disp, uint16_t bytes )
{
  for (int i = 0; i < 15; i++ )
  {
    mcp[disp].digitalWrite(i, ( bitRead( bytes, i) == 1 ) ? HIGH : LOW );
  }
}

// clear the display
void ClearDisplay( byte disp )
{
  for ( int i = 0; i < 15; i++ )
  {
    mcp[disp].digitalWrite(i, LOW);
  }
}

void loop() 
{

  // go through every character in the array and show it on display 0
  for ( int i = 0; i < ARRAY_SIZE; i++ )
  {
      ShowBytes( 0, characters_led[i].leds );
      delay(500);
  }
}

// find the bytes for a character in the array
CharacterX FindCharacterX( byte c )
{
  for ( int i = 0; i < ARRAY_SIZE; i++ )
  {
    if ( characters_led[i].id == c )
      return characters_led[i];
  }

  return characters_led[0];
}




