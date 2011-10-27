/***************************************************/
/*! \class Filter
    \brief STK filter class.

    This class implements a generic structure which
    can be used to create a wide range of filters.
    It can function independently or be subclassed
    to provide more specific controls based on a
    particular filter type.

    In particular, this class implements the standard
    difference equation:

    a[0]*y[n] = b[0]*x[n] + ... + b[nb]*x[n-nb] -
                a[1]*y[n-1] - ... - a[na]*y[n-na]

    If a[0] is not equal to 1, the filter coeffcients
    are normalized by a[0].

    The \e gain parameter is applied at the filter
    input and does not affect the coefficient values.
    The default gain value is 1.0.  This structure
    results in one extra multiply per computed sample,
    but allows easy control of the overall filter gain.

    by Perry R. Cook and Gary P. Scavone, 1995 - 2002.
*/
/***************************************************/

#if !defined(__MYFILTER_H)
#define __MYFILTER_H

#include "Stk.h"

class MyFilter : public Stk
{
public:
  //! Default constructor creates a zero-order pass-through "filter".
  MyFilter(void);

  //! Overloaded constructor which takes filter coefficients.
  /*!
    An StkError can be thrown if either \e nb or \e na is less than
    one, or if the a[0] coefficient is equal to zero.
  */
  MyFilter(int nb, StkFloat *bCoefficients, int na, StkFloat *aCoefficients);

  //! Class destructor.
  virtual ~MyFilter(void);

  //! Clears all internal states of the filter.
  void clear(void);

  //! Set filter coefficients.
  /*!
    An StkError can be thrown if either \e nb or \e na is less than
    one, or if the a[0] coefficient is equal to zero.  If a[0] is not
    equal to 1, the filter coeffcients are normalized by a[0].
  */
  void setCoefficients(int nb, StkFloat *bCoefficients, int na, StkFloat *aCoefficients);

  //! Set numerator coefficients.
  /*!
    An StkError can be thrown if \e nb is less than one.  Any
    previously set denominator coefficients are left unaffected.
    Note that the default constructor sets the single denominator
    coefficient a[0] to 1.0.
  */
  void setNumerator(int nb, StkFloat *bCoefficients);

  //! Set denominator coefficients.
  /*!
    An StkError can be thrown if \e na is less than one or if the
    a[0] coefficient is equal to zero.  Previously set numerator
    coefficients are unaffected unless a[0] is not equal to 1, in
    which case all coeffcients are normalized by a[0].  Note that the
    default constructor sets the single numerator coefficient b[0]
    to 1.0.
  */
  void setDenominator(int na, StkFloat *aCoefficients);

  //! Set the filter gain.
  /*!
    The gain is applied at the filter input and does not affect the
    coefficient values.  The default gain value is 1.0.
   */
  virtual void setGain(StkFloat theGain);

  //! Return the current filter gain.
  virtual StkFloat getGain(void) const;

  //! Return the last computed output value.
  virtual StkFloat lastOut(void) const;

  //! Input one sample to the filter and return one output.
  virtual StkFloat tick(StkFloat sample);

  //! Input \e vectorSize samples to the filter and return an equal number of outputs in \e vector.
  virtual StkFloat *tick(StkFloat *vector, unsigned int vectorSize);

protected:
  StkFloat gain;
  int     nB;
  int     nA;
  StkFloat *b;
  StkFloat *a;
  StkFloat *outputs;
  StkFloat *inputs;

};

#endif
