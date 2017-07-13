//
// Classe pour la gestion des queues en memoire
//


#include <conio.h>
#include <string.h>
#include <alloc.h>

#define SIZE	16
#define ERROR 	-1
#define OK		0

#define ALL_QUEUE	1
#define QUEUE1		2
#define QUEUE2		3
#define QUEUE3		4
#define QUEUE4		5

//-----------------------------------------------------------------------
// Definition de la classe File
class Queue_FFT
{
	int n;		        // Nombre d'element d'une Queue_FFT
				// (DOIT etre Multiple de 4 !)

	class complex *v;	// Pointeur d'element de queue (Complexes)
	int index_ALL_QUEUE;	// index de la queue complete
	int index_QUEUE1;       // Index de la queue QUEUE1
	int index_QUEUE2;       // Index de la queue QUEUE2
	int index_QUEUE3;       // Index de la queue QUEUE3
	int index_QUEUE4;       // Index de la queue QUEUE4

	public:
		// Constructeur de l'objet
		Queue_FFT (int taille);

		// Destructeur de l'objet
		~Queue_FFT();

		// Retire une donnee du vecteur
		int Get(int mode, complex *valeur);

		// Insere une valeur dans la Queue ou dans une sous-queue
		int Put(int mode, complex valeur);

		// Retourne le nombre d'elements de la file
		int get_n();

		// Affiche un vecteur a l'ecran
		void Show_SM(int mode);


		// Donne le nombre d'element dans chaque queue
		void Status();


};
