//***************************************************************************
//
//
//                     --------- Module Principal --------
//
//
//  Description :
//
//  Programme qui simule le fonctionnement du processeur parallele a base 4
//  qui produit la transformee de Fourier directe et inverse d'un signal.
//  L'algorithme est base sur l'article suivant :
//
//  "A PARALLEL RADIX-4 FAST FOURIER TRANSFORM COMPUTER"
//  par Michael J. Corinthios, Kenneth C. Smith, et Jui L. Yen
//  IEEE transactions on computers, Vol. c-24, no.1, january 1975
//
//
//  En entree : -le programme discretise une fonction en N points.
//              -un fichier ROM contenant les exposants Mu
//
//  En sortie : -deux fichiers: un contenant la partie reele, et l'autre la
//               partie imaginaire de la FFT.("FFT_ima" et "FFT_re")
//              -affiche la phase et l'amplitude
//		-a chacune des iteration affiche le contenu des sous-memoires
//
//
//  Langage : Borland C++ 2.0
//
//
//  Date    : le 17 avril 1993
//
//
//  Auteurs : Marc Missonnier, 45302
//            Richard Taillon, 38724
//
//
//
//***************************************************************************



#include "alu.h"
#include "q_fft.h"

void sauve(int n, complex *F);

main()
{

   int i,j,k;
   int compteur=0;    // indique le nombre de fois acceder une sous-memoire
   int sub_mem=0;     // indique a quelle sous memoire on accede
   int sink=1,
   input=0;           // flags pour indiquer le SINK MODE
   int N=64;          // nb de points
   int n;             // nb d'iterations
   int iteration = 0; // iteration courante
   int clock = 0;     // donne le nb de cycle dans une iteration

   complex in[4],v[4],// in  : 4 valeurs a l'entree de l'alu
   out[4];            // out : 4 valeurs a la sortie de l'alu
   complex *f;        // f   : signal d'entree
   complex *F;	      // F   : signal de sortie

   Alu alu(N);

   // 2 memoires MEM1 et MEM2 avec 4 Sous memoires
   // Chaque sous-memoire comporte N/4 elements
   Queue_FFT MEM[4][2]={N/4,N/4,N/4,N/4,N/4,N/4,N/4,N/4};

   // calcule le nb d'iterations
   n = (int) (log10(N) / log10(4));


   // Alloue la memoire pour le signal d'entree f et de sortie F
   f = new complex[N];
   F = new complex[N];

   // Mise en memoire du signal
   for(i=0; i < N; i++)
      f[i] = i;

   // pour N/4 points par sous memoire
   // et pour toutes les SM de 0 a 3 de MEM1
   for(k=0; k < N/4; k++)
      for(i=0; i < 4; i++)
	MEM[i][0].Put(ALL_QUEUE, f[i+(k*4)] );

   cout << "\nTransformee directe de Fourier ";
   cout << "d'une rampe avec N=64\n";
   cout << "\nChaque sous-memoire contient 4 sous queues dont le contenu\n";
   cout << "est affiche sequentiellement avec (a,b) = a + b*i\n\n";

   while(iteration < n) // il y a n iterations ou n= log4 N
   {

     cout << "\n\n\nA la fin de l'iteration  " << iteration << "\n";

     while(clock < (N/4)) // il y a N/4 cycles par iteration
     {

       // Premiere iteration
       if(iteration == 0)
       {

	  // pour toutes les SM de 0 a 3 de MEM1
	  for(i=0; i < 4; i++)
	     MEM[i][0].Get(ALL_QUEUE, (in+i) );


	  // calcul le resultat avec l'unite arithmetique
	  alu.preweighting(in,v);
	  alu.weighting(v,out,(clock*4+iteration*N));

	  // pour toutes les SM de 0 a 3 de MEM2
	  for(i=0; i < 4; i++)
	     MEM[i][1].Put(ALL_QUEUE, out[i] );

       }
       else
       {

	  if((iteration % 2) == 0)
	  {
	    // Iteration paire
	    // MEM2 est en SINK MODE
	    sink = 1;
	    input = 0;
	  }
	  else
	  {
	    // Iteration impaire
	    // MEM1 est en SINK MODE
	    sink = 0;
	    input = 1;
	  }

	  // Iterations suivantes

	  // pour toutes les sous queues de 1 a 4 de MEM en entree
	  for(i=0; i < 4; i++)
	     MEM[sub_mem][input].Get(5-i, in+i );

	  // calcul le resultat avec l'unite arithmetique
	  alu.preweighting(in,v);
	  alu.weighting(v,out,(clock*4+iteration*N));

	  // pour toutes les SM de 0 a 3 de MEM Sink Mode
	  for(i=0; i < 4; i++)
	     MEM[i][sink].Put(ALL_QUEUE, out[i] );

	  compteur++;

	  // On passe a la sous-memoire suivante tous les 4^(iteration-1)
	  if(compteur == pow(4,iteration-1))
	  {

	     compteur = 0;
	     sub_mem++;
	     if(sub_mem > 3)
		sub_mem = 0;
	  }

       } // else

       // on passe au cycle suivant
       clock++;

     }// while clock

     cout << "\n\n***********************************************\n\n";

     // affiche le contenu des memoires


     cout << "\n\nMEM no. " << sink+1 << "\n\n";
     for(i=0; i < 4; i++)
     {
	cout << "\n\nSous-memoire no. " << i+1+sink*4 << "\n";
	MEM[i][sink].Show_SM(ALL_QUEUE);
     }


     // on passe a l'iteration suivante
     iteration++;
     clock = 0;
     sub_mem = 0;
     compteur = 0;

   } // while iteration


   // Calcule la phase et l'amplitude
   cout << "\n*******************************************\n\n";
   cout << "\n\nAMPLITUDE et PHASE(radians)\n\n";

   for(i=0; i < 4; i++)
      for(k=0; k < N/4; k++)
      {
	 MEM[i][sink].Get(ALL_QUEUE, (F+k+(i*N/4)) );
	 cout << sqrt(norm(F[k+(i*N/4)])) << "  " << arg(F[k+(i*N/4)]) << "\n";
      }


   // Sauve sur disque la FFT du signal
   sauve(N, F);

}// main



void sauve(int n, complex *F)
{

   int i;
   FILE *file_ptr1, *file_ptr2;
   char *sp=" "; // space
   char *imagin="FFT_ima", *reel="FFT_re", str[25];


   if ( (file_ptr2=fopen(imagin,"wt")) == NULL)
   {
	printf("\nErreur d'ecriture\n");
	exit(0);
   }

   if ( (file_ptr1=fopen(reel,"wt")) == NULL)
   {
	printf("\nErreur d'ecriture\n");
	exit(0);
   }

   for(i=0; i < n; i++)
   {
      fputs(gcvt(real(F[i]),10,str),file_ptr1);
      fputs(sp, file_ptr1);

      fputs(gcvt(imag(F[i]),10,str),file_ptr2);
      fputs(sp, file_ptr2);
   }


   fclose(file_ptr1);
   fclose(file_ptr2);

}
