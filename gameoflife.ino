/*
 * gameoflife. A Conway's game of life implementation for Arduino and MAX7219 
 * controlled led matrix.
 * 
 * Copyright (C) 2014  Rafael Bailón-Ruiz <rafaelbailon "en" ieee "punto" org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "LedControl.h"

/*
 pin 10 is connected to the DataIn 
 pin 8 is connected to the CLK 
 pin 9 is connected to LOAD 
 One MAX72XX.
 */
LedControl lc=LedControl(10,8,9,1);

int gen = 0;
int maxGen = 50;
unsigned long delaytime=1000;

int NUMROWS = 8;
int NUMCOLS = 8;

int gameBoard[] =  { 2, 4, 7, 0, 0, 0, 0, 0 };

int newGameBoard[] =  { 0, 0, 0, 0, 0, 0, 0, 0 };

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,5);
  /* and clear the display */
  lc.clearDisplay(0);
    
  //resetMap();
}

void resetMap()
{
  randomSeed(analogRead(0));
  for(int x = 0; x < NUMROWS; ++x)
  {
    gameBoard[x] = random(256);
  }
}

void nextGeneration() {
  int up;
  
  for(int x = 0; x < NUMROWS; ++x)
  {

    for(int y = 0; y < NUMCOLS; ++y)
    {
      int sum = sumNeighbours(gameBoard, NUMROWS, x, y);
      if(bitRead(gameBoard[x],y) == 1) //If Cell is alive
      {
        if(sum < 2 || sum > 3) //Cell dies
        {
          bitClear(newGameBoard[x],y);
        }
        else
        {
          bitSet(newGameBoard[x],y);
        }
      }
      else //If Cell is dead
      {
        if(sum == 3) //A new Cell is born
        {
          bitSet(newGameBoard[x],y);
        }
      }
    }
  }
  if(compareArray(newGameBoard, gameBoard, NUMROWS) == 0)
  {
    gen = maxGen - 1;
  }
  copyArray(newGameBoard, gameBoard, NUMROWS);
}

int sumNeighbours(int matrix[], int matrixLength, int x, int y)
{
  int sum = 0;
  
  for (int ix = -1; ix <=1; ++ix)
  {
    for (int iy = -1; iy <=1; ++iy)
    {
      if(x + ix < 0 || x + ix > matrixLength - 1 || y + iy < 0 || y + iy > 7 || (ix == 0 && iy == 0))
      {
        continue;
      }
      
      bitRead(matrix[x + ix], y + iy) == 1 ? ++sum : 0;
    }
  }
  
  return sum;
}

void copyArray(int *from, int *to, int length)
{
  for(int i = 0; i < length; ++i)
  {
    to[i] = from[i];
  }
}

/* Return 0 if they are equal, else 1 */
int compareArray(int *first, int *second, int length)
{
  for(int i = 0; i < length; ++i)
  {
    if(first[i] != second[i])
    {
      return 1;
    }
  }
  return 0;
}

void rows(boolean wait) {
  for(int row=0;row<8;row++)
  {
    lc.setRow(0,row,gameBoard[row]);
    
  }
  if(wait == true){
    delay(delaytime);
  }
}

void loop() { 
  if(gen >= maxGen)
  {
    gen = 0;
    resetMap();
    rows(true);
  }else
  {
    rows(true);
  }
  
  nextGeneration();
  gen++;
}
