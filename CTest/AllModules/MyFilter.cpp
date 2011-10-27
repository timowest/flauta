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

#include "MyFilter.h"
#include <stdio.h>

MyFilter :: MyFilter()
{
  // The default constructor should setup for pass-through.
  gain = 1.0;
  nB = 1;
  nA = 1;
  b = new StkFloat[nB];
  b[0] = 1.0;
  a = new StkFloat[nA];
  a[0] = 1.0;

  inputs = new StkFloat[nB];
  outputs = new StkFloat[nA];
  this->clear();
}

MyFilter :: MyFilter(int nb, StkFloat *bCoefficients, int na, StkFloat *aCoefficients)
{
  char message[256];

  // Check the arguments.
  if ( nb < 1 || na < 1 ) {
    sprintf(message, "MyFilter: nb (%d) and na (%d) must be >= 1!", nb, na);
    handleError( message, StkError::FUNCTION_ARGUMENT );
  }

  if ( aCoefficients[0] == 0.0 ) {
    sprintf(message, "MyFilter: a[0] coefficient cannot == 0!");
    handleError( message, StkError::FUNCTION_ARGUMENT );
  }

  gain = 1.0;
  nB = nb;
  nA = na;
  b = new StkFloat[nB];
  a = new StkFloat[nA];

  inputs = new StkFloat[nB];
  outputs = new StkFloat[nA];
  this->clear();

  this->setCoefficients(nB, bCoefficients, nA, aCoefficients);
}

MyFilter :: ~MyFilter()
{
  delete [] b;
  delete [] a;
  delete [] inputs;
  delete [] outputs;
}

void MyFilter :: clear(void)
{
  int i;
  for (i=0; i<nB; i++)
    inputs[i] = 0.0;
  for (i=0; i<nA; i++)
    outputs[i] = 0.0;
}

void MyFilter :: setCoefficients(int nb, StkFloat *bCoefficients, int na, StkFloat *aCoefficients)
{
  int i;
  char message[256];

  // Check the arguments.
  if ( nb < 1 || na < 1 ) {
    sprintf(message, "MyFilter: nb (%d) and na (%d) must be >= 1!", nb, na);
    handleError( message, StkError::FUNCTION_ARGUMENT );
  }

  if ( aCoefficients[0] == 0.0 ) {
    sprintf(message, "MyFilter: a[0] coefficient cannot == 0!");
    handleError( message, StkError::FUNCTION_ARGUMENT );
  }

  if (nb != nB) {
    delete [] b;
    delete [] inputs;
    nB = nb;
    b = new StkFloat[nB];
    inputs = new StkFloat[nB];
    for (i=0; i<nB; i++) inputs[i] = 0.0;
  }

  if (na != nA) {
    delete [] a;
    delete [] outputs;
    nA = na;
    a = new StkFloat[nA];
    outputs = new StkFloat[nA];
    for (i=0; i<nA; i++) outputs[i] = 0.0;
  }

  for (i=0; i<nB; i++)
    b[i] = bCoefficients[i];
  for (i=0; i<nA; i++)
    a[i] = aCoefficients[i];

  // scale coefficients by a[0] if necessary
  if (a[0] != 1.0) {
    for (i=0; i<nB; i++)
      b[i] /= a[0];
    for (i=0; i<nA; i++)
      a[i] /= a[0];
  }
}

void MyFilter :: setNumerator(int nb, StkFloat *bCoefficients)
{
  int i;
  char message[256];

  // Check the arguments.
  if ( nb < 1 ) {
    sprintf(message, "MyFilter: nb (%d) must be >= 1!", nb);
    handleError( message, StkError::FUNCTION_ARGUMENT );
  }

  if (nb != nB) {
    delete [] b;
    delete [] inputs;
    nB = nb;
    b = new StkFloat[nB];
    inputs = new StkFloat[nB];
    for (i=0; i<nB; i++) inputs[i] = 0.0;
  }

  for (i=0; i<nB; i++)
    b[i] = bCoefficients[i];
}

void MyFilter :: setDenominator(int na, StkFloat *aCoefficients)
{
  int i;
  char message[256];

  // Check the arguments.
  if ( na < 1 ) {
    sprintf(message, "MyFilter: na (%d) must be >= 1!", na);
    handleError( message, StkError::FUNCTION_ARGUMENT );
  }

  if ( aCoefficients[0] == 0.0 ) {
    sprintf(message, "MyFilter: a[0] coefficient cannot == 0!");
    handleError( message, StkError::FUNCTION_ARGUMENT );
  }

  if (na != nA) {
    delete [] a;
    delete [] outputs;
    nA = na;
    a = new StkFloat[nA];
    outputs = new StkFloat[nA];
    for (i=0; i<nA; i++) outputs[i] = 0.0;
  }

  for (i=0; i<nA; i++)
    a[i] = aCoefficients[i];

  // scale coefficients by a[0] if necessary
  if (a[0] != 1.0) {
    for (i=0; i<nB; i++)
      b[i] /= a[0];
    for (i=0; i<nA; i++)
      a[i] /= a[0];
  }
}

void MyFilter :: setGain(StkFloat theGain)
{
  gain = theGain;
}

StkFloat MyFilter :: getGain(void) const
{
  return gain;
}

StkFloat MyFilter :: lastOut(void) const
{
  return outputs[0];
}

StkFloat MyFilter :: tick(StkFloat sample)
{
  int i;

  outputs[0] = 0.0;
  inputs[0] = gain * sample;
  for (i=nB-1; i>0; i--) {
    outputs[0] += b[i] * inputs[i];
    inputs[i] = inputs[i-1];
  }
  outputs[0] += b[0] * inputs[0];

  for (i=nA-1; i>0; i--) {
    outputs[0] += -a[i] * outputs[i];
    outputs[i] = outputs[i-1];
  }

  return outputs[0];
}

StkFloat *MyFilter :: tick(StkFloat *vector, unsigned int vectorSize)
{
  for (unsigned int i=0; i<vectorSize; i++)
    vector[i] = tick(vector[i]);

  return vector;
}
