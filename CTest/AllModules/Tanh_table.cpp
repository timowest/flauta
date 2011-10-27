/***************************************************/
/*! \class Tanh_table
    \brief STK table lookup class.

    This class loads a table of floating-point
    StkFloats, which are assumed to be in big-endian
    format.  Linear interpolation is performed for
    fractional lookup indexes.

    An StkError will be thrown if the table file
    is not found.

    by Perry R. Cook and Gary P. Scavone, 1995 - 2002.
    modified by pdelac 2002                         
*/
/***************************************************/

#include "Tanh_table.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
using namespace std;


Tanh_table :: Tanh_table(StkFloat  min_value_tanh_table,StkFloat max_value_tanh_table,StkFloat step_tanh_table )
{
  StkFloat  inv_step_tanh_table = 1.0/step_tanh_table;
  length = (int)(((max_value_tanh_table - min_value_tanh_table)*
		       inv_step_tanh_table) + 1);
 
  data = (StkFloat *) new StkFloat[length];

  StkFloat  argument = min_value_tanh_table;
  for(int i = 0; i < length; i++){
    data[i] = (StkFloat)tanh(argument);
    argument += step_tanh_table;
  }

  lastOutput = 0.0;
}

Tanh_table :: ~Tanh_table()
{
  delete [ ] data;
}

long Tanh_table :: getLength() const
{
  return length;
}

StkFloat Tanh_table :: lastOut() const
{
  return lastOutput;
}

StkFloat Tanh_table :: tick(StkFloat index)
{
  StkFloat alpha;
  long temp;

  if (index > length-1) {
    //std::cerr << "Tanh_table: Index (" << index << ") exceeds table length ... sticking at end!" << std::endl;
    index = length-1;
  }
  else if (index < 0.0) {
    //std::cerr << "Tanh_table: Index (" << index << ") is less than zero ... setting to zero!" << std::endl;
    index = 0.0;
  }

  // Index in range 0 to length-1
  temp = (long) index;                   // Integer part of index
  alpha = index - (StkFloat) temp;      // Fractional part of index
  if (alpha > 0.0) {                    // Do linear interpolation
    lastOutput = data[temp];
    lastOutput += (alpha*(data[temp+1] - lastOutput));
  }
  else lastOutput = data[temp];

  return lastOutput;
}

StkFloat *Tanh_table :: tick(StkFloat *vector, unsigned int vectorSize)
{
  for (unsigned int i=0; i<vectorSize; i++)
    vector[i] = tick(vector[i]);

  return vector;
}
