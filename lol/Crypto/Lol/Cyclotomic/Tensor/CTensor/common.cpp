#include "tensorTypes.h"

hInt_t Zq::q; // see #12152

hDim_t ipow(hDim_t base, hShort_t exp)
{
	hDim_t result = 1;
  while (exp) {
    if (exp & 1) {
      result *= base;
    }
    exp >>= 1;
    base *= base;
  }
  return result;
}

// a is the field size. we are looking for reciprocal of b
hInt_t reciprocal (hInt_t a, hInt_t b)
{
	hInt_t fieldSize = a;

	hInt_t y = 1;
	hInt_t lasty = 0;
	while (b != 0) {
		hInt_t quotient = a / b;
		hInt_t tmp = a % b;
		a = b;
		b = tmp;
		tmp = y;
		y  = lasty - quotient*y;
		lasty = tmp;
	}
	ASSERT (a==1);  // if this one fails, then b is not invertible mod a

	// this actually returns EITHER the reciprocal OR reciprocal + fieldSize
	hInt_t res = lasty + fieldSize;
	return res;
}

void canonicalizeZq (Zq* y, hShort_t tupSize, hDim_t totm, hInt_t* qs) {
  for(int tupIdx = 0; tupIdx<tupSize; tupIdx++) {
    hInt_t q = qs[tupIdx];
    for(hDim_t j = 0; j < totm; j++) {
      if(y[j*tupSize+tupIdx].x<0) {
        y[j*tupSize+tupIdx].x+=q;
      }
    }
  }
}