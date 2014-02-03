# gameoflife

**gameoflife** is a Conway's game of life implementation for Arduino and a MAX7219 controlled 8x8 led matrix.

It has been developed in a single day and doesn't have any fancy options. *It just works*

## How to use it

It's easy to get it working. Connect your led matrix to the apropiate pins on Arduino and load the sketch on it.

The program starts with a glider crossing the screen. After that, the grid is initializated with random values that develop until:

 * all cells die.
 * system is frozen.
 * or has grown for 50 generations.

Then a new random matrix is generated and the cycle begins again.

## Licence

```
Copyright (C) 2014  Rafael Bailón-Ruiz <rafaelbailon "en" ieee "punto" org>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
```
