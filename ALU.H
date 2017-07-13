/***************************************************************************/
//
// Classe pour l'unite arithmetique
//
//
/***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

class Alu
{


   public:

      int N;
      int *k; // tableau des puissances de w
      complex w[4];

      // Constructeur
      Alu(int nb);

      // Destructeur
      ~Alu();

      // Preweighting: S(4)
      void preweighting(complex *z, complex *v);

      // Weighting: mu
      void weighting(complex *v, complex *out, int cycle);


};

