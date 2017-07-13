// Travail Pratique IF-530 Richard Taillon (38724) et  Marc Missonnier (45302)
// Classe pour simulation du Radix 4 FFT computer
// Programme compile sous BORLAND C++ version 2.0

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include "q_fft.h"

//-----------------------------------------------------------------------
// Definition des methodes de la classe Queue_FFT



// Constructeur de l'objet
Queue_FFT::Queue_FFT (int taille)
		{
			n=taille;
			index_ALL_QUEUE=0;     // Empty when created
			index_QUEUE1=0;
			index_QUEUE2=n/4;
			index_QUEUE3=n/2;
			index_QUEUE4=3*n/4;
			v=new complex[n];    // Creation de l'espace requis.

			if (!v)
			   cout << "\nErreur d'initialisation du vecteur de complexes\n";
		}

// Destructeur de l'objet
Queue_FFT::~Queue_FFT()
		{
			delete v;
		}

// Retire une donnee du vecteur
int Queue_FFT::Get(int mode, complex *valeur)
		{

			int i;
			switch (mode)
			{
				case ALL_QUEUE:
					if (index_ALL_QUEUE == 0)
						return(ERROR);

					index_ALL_QUEUE--;
					*valeur = v[index_ALL_QUEUE];

					switch ((int)((4*index_ALL_QUEUE)/(int)n))
					{
						case 0:
							index_QUEUE1--;
							break;
						case 1:
							index_QUEUE2--;
							break;
						case 2:
							index_QUEUE3--;
							break;
						case 3:
							index_QUEUE4--;
							break;
						default:
							cout << "\nERREUR: Put()";
							return(ERROR);
					}

					break;

				case QUEUE1:           // Sous queue: de 0 a (n/4)-1
					if (index_QUEUE1 == 0)
						return(ERROR);

					index_QUEUE1--;
					index_ALL_QUEUE--;
					*valeur = v[index_QUEUE1];
					break;

				case QUEUE2:
					if (index_QUEUE2 == n/4)
						return(ERROR);

					index_ALL_QUEUE--;
					index_QUEUE2--;
					*valeur = v[index_QUEUE2];
					break;

				case QUEUE3:
					if (index_QUEUE3 == n/2)
						return(ERROR);

					index_ALL_QUEUE--;
					index_QUEUE3--;
					*valeur = v[index_QUEUE3];
					break;

				case QUEUE4:
					if (index_QUEUE4 == 3*n/4)
						return(ERROR);

					index_ALL_QUEUE--;
					index_QUEUE4--;
					*valeur = v[index_QUEUE4];
					break;

				default:
					return(ERROR);
					break;
			}
			return(OK);

		}

// Insere une valeur dans la Queue ou dans une sous-queue
int Queue_FFT::Put(int mode, complex valeur)
		{
			int i;
			switch (mode)
			{
				case ALL_QUEUE:
					if (index_ALL_QUEUE == n)
						return(ERROR);

					switch ((int)((4*index_ALL_QUEUE)/(int)n))
					{
						case 0:
							index_QUEUE1++;
							break;
						case 1:
							index_QUEUE2++;
							break;
						case 2:
							index_QUEUE3++;
							break;
						case 3:
							index_QUEUE4++;
							break;
						default:
							cout << "\nERREUR: Put()";
							return(ERROR);
					}

					for (i=index_ALL_QUEUE; i>0 ;i--)
						v[i] = v[i-1];
					v[0]=valeur;
					index_ALL_QUEUE++;
					break;

/* NON utilise
				case QUEUE1:           // Sous queue: de 0 a (n/4)-1
					if (index_QUEUE1 == n/4)
						return(ERROR);

					for (i=index_QUEUE1; i>0 ;i--)
						v[i] = v[i-1];
					v[0]=valeur;
					index_QUEUE1++;
					break;

				case QUEUE2:
					if (index_QUEUE2 == n/2)
						return(ERROR);

					for (i=index_QUEUE2; i>n/4 ;i--)
						v[i] = v[i-1];
					v[n/4]=valeur;
					index_QUEUE2++;
					break;

				case QUEUE3:
					if (index_QUEUE3 == 3*n/4)
						return(ERROR);

					for (i=index_QUEUE3; i>n/2 ;i--)
						v[i] = v[i-1];
					v[n/2]=valeur;
					index_QUEUE3++;
					break;

				case QUEUE4:
					if (index_QUEUE4 == n)
						return(ERROR);

					for (i=index_QUEUE4; i>3*n/4 ;i--)
						v[i] = v[i-1];
					v[3*n/4]=valeur;
					index_QUEUE4++;
					break;
*/
				default:
					return(ERROR);
					break;
			}
			return(OK);

		}

// Retourne le nombre d'elements de la file
int Queue_FFT::get_n()
		{
			return (n);
		}


// Donne le nombre d'element dans chaque queue
void Queue_FFT::Status()
		{

		  cout <<"\nALL->" << index_ALL_QUEUE <<"  Q1->" << index_QUEUE1 <<"  Q2->" << index_QUEUE2
		  <<"  Q3->" << index_QUEUE3 <<"  Q4->" << index_QUEUE4 ;


		}

// Affiche un vecteur a l'ecran
void Queue_FFT::Show_SM(int mode)
		{
			int i;
			cout << "\n";

			switch (mode)
			{
				case ALL_QUEUE:
					for (i=0;i<index_ALL_QUEUE;i++)
					{
					  if(i%(n/4)==0)
					     cout << "\n----------------------------";
					  cout << "\n" << v[(index_ALL_QUEUE-1)-i];
					}
					break;

				case QUEUE1:
					for (i=0;i<index_QUEUE1;i++)
						cout << "\nSub-ALL_QUEUE #1 index[" << i << "] = " << v[i];
					break;

				case QUEUE2:
					for (i=n/4;i<index_QUEUE2;i++)
						cout << "\nSub-ALL_QUEUE #2 index[" << i << "] = " << v[i];
					break;

				case QUEUE3:
					for (i=n/2;i<index_QUEUE3;i++)
						cout << "\nSub-ALL_QUEUE #3 index[" << i << "] = " << v[i];
					break;

				case QUEUE4:
					for (i=3*n/4;i<index_QUEUE4;i++)
						cout << "\nSub-ALL_QUEUE #4 index[" << i << "] = " << v[i];
					break;

				default:
					cout << "\nMode non supporte.\n";
					break;
			}

		}

