#include "QuasiRandomNumber.hpp"


/**
 * Returns a quasi-random number in the range (0,1) based on the hamilton sequence.
 * Note: Will repeat when index > max(unsinged long) most likely around 1.8 * 10^19
 */
float hamiltonQNR(unsigned long index, unsigned int base)
{
   float result = 0.0f;
   float f = 1.0f / float(base);
   unsigned long i = index;

   while (i > 0)
   {
      result = result + f * (i % base);
      i = (unsigned long)(float(i) / float(base));
      f /= base; 
   }

   index++;
   return result;
}

// int main(int argc, char const *argv[])
// {
//    for (int i = 0; i < 10; ++i)
//    {
//       printf("(%f, %f)\n", hamiltonQNR(i+1,2), hamiltonQNR(i+1,3));
//    }

//    printf("%lu\n", sizeof(long));

//    return 0;
// }