/***************************************************/
/*! \class Table
    \brief STK table lookup class.

    This class loads a table of floating-point
    StkFloats, which are assumed to be in big-endian
    format.  Linear interpolation is performed for
    fractional lookup indexes.

    An StkError will be thrown if the table file
    is not found.

    by Perry R. Cook and Gary P. Scavone, 1995 - 2002.
*/
/***************************************************/

#if !defined(__TANH_TABLE_H)
#define __TANH_TABLE_H

#include "Stk.h"
#include <math.h>
class Tanh_table : public Stk
{
public:
  //! Constructor loads the data from \e fileName.
  Tanh_table(StkFloat  min_value_tanh_table,StkFloat max_value_tanh_table,StkFloat step_tanh_table );

  //! Class destructor.
  ~Tanh_table();

  //! Return the number of elements in the table.
  long getLength() const;

  //! Return the last output value.
  StkFloat lastOut() const;

  //! Return the table value at position \e index.
  /*!
    Linear interpolation is performed if \e index is
    fractional.
   */
  StkFloat tick(StkFloat index);

  //! Take \e vectorSize index positions and return the corresponding table values in \e vector.
  StkFloat *tick(StkFloat *vector, unsigned int vectorSize);

protected:  
  long length;
  StkFloat *data;
  StkFloat lastOutput;

};

#endif // defined(__TANH_TABLE_H)
