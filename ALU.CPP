#include "alu.h"


/***************************************************************************/
//
// Methodes de la classe Alu
//
/***************************************************************************/


// Constructeur

Alu::Alu(int nb)
{

int i=0;

   N = nb;

   // Lire les puissances k de w ou w=exp(-j*2pi/N)
   // Nom du fichier : ROM

   k = new int[N*(int)(log10(N)/log10(4))]; // il y a N*n coefficients

   FILE *file_ptr;
   char *buf = "ROM";


   if( (file_ptr=fopen(buf,"rt")) == NULL)
   {
      cout << "\nErreur de lecture\n";
      exit(0);
   }

   while (fgets(buf,80,file_ptr) != NULL)
      k[i++] = atoi(buf);


   fclose(file_ptr);


}


// Destructeur

Alu::~Alu()
{

   delete k;
}


void Alu::preweighting(complex *z, complex *v)
{

int i;
complex j(0,1);


   // v = T4 * z

   v[0] = z[0]+z[1]+z[2]+z[3];
   v[1] = z[0]+j*z[1]-z[2]-j*z[3];
   v[2] = z[0]-z[1]+z[2]-z[3];
   v[3] = z[0]-j*z[1]-z[2]+j*z[3];

}


void Alu::weighting(complex *v, complex *out, int cycle)
{

int i;
complex j(0,1);



   // determiner quels coefficients appliquer selon le cycle

   for(i=0; i<4; i++)
      w[i] = exp(j* (2*M_PI* k[i+cycle] / N) );

   out[0] = v[0];

   for(i=1; i<4; i++)
      out[i] = v[i] * w[i];

}


