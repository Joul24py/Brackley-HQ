// Implementacion de arboles Buddy System

/*
Tamaños (TAM):
	8192	Nodos maximos de 32Kb(256)		Niveles 10
	4096	Nodos maximos de 32Kb(128)		Niveles 8
	1024	Nodos maximos de 32Kb(32)		Niveles 6
*/


#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#define TAM 1024
#define NIVEL 8// depende del tamaño maximo de memoria (TAM)
#define CUANTO 2

using namespace std;

//definicion adelantada para evitar errores
struct Proceso;
struct NodoMem;

struct Proceso//procesos entrantes en memoria
{
	int id;
	int tam;
	int cuanto;
	bool inside;
	Proceso* sig;
	NodoMem* asing;
};

struct NodoMem//arbol de memorias divididas
{
	NodoMem* der;
	Proceso* pro;
	int tam;
	NodoMem* izq;
};

//
//	DECLARACION DE FUNCIONES
//

Proceso* creaPro();
NodoMem* creaMem();

void eliminaPro(Proceso*);
void eliminaMem(NodoMem*);

void eliminaInfP(Proceso*);
void eliminaInfM(NodoMem*);

Proceso* agregaPro(Proceso*,int);
void mostrarMem(NodoMem*);
void mostrarPros(Proceso*);

Proceso* buddySystem(NodoMem*,Proceso*);
Proceso* ejecutaPros(Proceso*);

NodoMem* creaParticiones(NodoMem*,Proceso*);
void unirParticiones(NodoMem*);
void asignaMem(NodoMem*,Proceso*);

bool condens;

//
//	MAIN
//

int main()
{
	Proceso* pross=NULL;
	NodoMem* raiz=creaMem();//cabecera del arbol
	raiz->der=NULL;
	raiz->izq=NULL;
	raiz->pro=NULL;
	raiz->tam=TAM;
	int numPros=1;//Contador para los Id de los procesos
	
	srand(time(NULL));
	
	bool flag=true;
	char key='0';
	float vel=1;

	cout << "Controles: " << endl ;
	cout << "Para detener la simulacion                     P" << endl ;
	cout << "Para aumentar la velocidad de simulacion       +" << endl ;
	cout << "Para disminuir la velocidad de simulacion      -" << endl ;
	
	system("pause");
	while(flag)
	{
		system("cls");
		cout<<"Memoria:"<<endl;
		mostrarMem(raiz);
		
		if(rand()%4 == 0)//if para generar procesos aleatoriamente
		{
			pross=agregaPro(pross,numPros++);
		}
		
		cout<<endl<<endl<<"Procesos:"<<endl;
		mostrarPros(pross);
		
		pross = buddySystem(raiz,pross);

		cout<<endl<<endl<<"Procesos:"<<endl;
		mostrarPros(pross);

		if (_kbhit()) //detecta el input de una tecla
		{
            // Obtiene la tecla presionada
            key = _getch();

            if (key == 'P' || key == 'p') //si la tecla se presiona es p sale de ejecucion
			{
				cout << endl;
                break; 
                key = '0';
            }

            if (key == '+') //si es + aumenta la velocidad disminuyendo el valor de vel
			{
                if(vel >= 0.0625)
                {
                    vel /= 2;
                }
                key = '0';
            }

            if (key == '-') //si es - disminuye la velocidad aumentando el valor de vel
			{
                if(vel <= 16)
                {
                    vel *= 2;
                }
                key = '0';
            }
            
        }

		cout << endl << endl << endl << "\tVelocidad: " << (vel)*100 <<"ms";

		Sleep(100*vel);//modificador de tiempo entre pantallas
	}
	
	eliminaInfP(pross);
	eliminaInfM(raiz);
	system("pause");
	return 0;
}

//
//	DEFINICION DE FUNCIONES
//

Proceso* creaPro()//Crea dinámicamente procesos
{
	return (new Proceso);
}

NodoMem* creaMem()//Crea dinámicamente memoria
{
	return (new NodoMem);
}

void eliminaPro(Proceso* aux)//Elimina un proceso
{
	delete aux;
}

void eliminaMem(NodoMem* aux)//Elimina un espacio de memoria
{
	delete aux;
}

void eliminaInfP(Proceso* pross)//Elimina todos los procesos (recursivo)
{
	if(pross!=NULL)
	{
		eliminaInfP(pross->sig);
		eliminaPro(pross);
	}
}

void eliminaInfM(NodoMem* raiz)//Elimina toda la mamoria (recursivo)
{
	if(raiz!=NULL)
	{
		eliminaInfM(raiz->izq);
		eliminaInfM(raiz->der);
		eliminaMem(raiz);
	}
}

Proceso* agregaPro(Proceso* pross,int i)//Genera los procesos nuevos y los concatena en la lista de procesos
{
	Proceso* aux,* nuevo;
	if(pross == NULL)
	{
		pross = creaPro();
		
		nuevo = pross;
		
		nuevo->sig = NULL;
		nuevo->id = i;
		nuevo->inside = false;
		nuevo->asing = NULL;
	}else{
		aux = pross;
	
		while(aux->sig != NULL)
		{
			aux = aux->sig;
		}
	
		nuevo = creaPro();
		aux->sig = nuevo;
		nuevo->sig = NULL;
		nuevo->id = i;
		nuevo->inside = false;
		nuevo->asing = NULL;
	}
	/*
	cout<<endl<<endl<<"tam de memoria: ";
	cin>>nuevo->tam;
	cout<<"cuanto pros: ";
	cin>>nuevo->cuanto;
	*/
	nuevo->tam = (rand()%TAM) +1 ;
	nuevo->cuanto = (rand()% (CUANTO*10))+1;

	if(nuevo->tam >= TAM)
	{
		nuevo->tam = ((nuevo->tam) % TAM) + 1;
	}
	
	return pross;
}

void mostrarMem(NodoMem* raiz)//Muestra los espacios de memoria (recursivo)
{
	if(raiz!=NULL)
	{
		if(raiz->der==NULL&&raiz->izq==NULL)
		{
			if(raiz->pro==NULL)
			{		
				cout<<"[0,"<<raiz->tam<<",0]";
			}else{
				cout<<"["<<raiz->pro->id<<","<<raiz->pro->tam<<"("<<raiz->tam<<"),"<<raiz->pro->cuanto<<"]";
			}
		}
		mostrarMem(raiz->izq);
		mostrarMem(raiz->der);
	}
	
}

void mostrarPros(Proceso* pross)//Muestra los procesos (recursivo)
{
	Proceso* aux;
	aux = pross;
	while(aux != NULL)
	{
		cout<<"["<<aux->id <<","<< aux->tam<<","<<aux->cuanto ;
		if(aux->inside)
		{
			cout<<",EJECUTANDO";
		}else{
			cout<<",ESPERA";
		}
		cout<<"]";
		aux = aux->sig;
	}
}

Proceso* buddySystem(NodoMem* raiz,Proceso* pross)//Ejecuta las diferentes actividades de Buddy System
{
	NodoMem* auxL,* auxD;
	//Primero se particiona la memoria
	//se buscan los procesos con inside==false para meterlos a la memoria (mem.tam)/2 < pros.tam
	condens = false;

	raiz = creaParticiones(raiz,pross);
	
	cout<<endl<<endl<<"Memoria:"<<endl;
	mostrarMem(raiz);
	
	//luego se ejecuta los procesos
	//se ejecutan los procesos con inside==true 
	//hipoteticamente aqui iría roundRobin
	
	pross = ejecutaPros(pross);
	
	//luego condensa la memoria de los huecos contiguos
	for(int i=0;i<NIVEL;i++)//for que recorre los diferentes niveles del arbol para condensarlo
	{
		unirParticiones(raiz->izq);
		unirParticiones(raiz->der);
	
		auxD = raiz->der;
		auxL = raiz->izq;
		if(auxD!=NULL && auxL!=NULL)
		{
			if((auxD->pro == NULL && auxL->pro == NULL) && (auxL->izq == NULL && auxL->der == NULL) && (auxD->izq == NULL && auxD->der == NULL))
			{
				eliminaMem(auxL);
				eliminaMem(auxD);
				raiz->der = NULL;
				raiz->izq = NULL;
				condens = true;
			}
		}
	}

	if(condens)
	{
		cout<<"\nCondensando...";
	}

	return (pross);
}

Proceso* ejecutaPros(Proceso* pross)//Ejecutador genérico de procesos (Cada proceso en memoria reduce cuantos)
{
	Proceso* aux,* ancla,* elimina;
	NodoMem* memAsign;
	
	aux = pross;
	
	while(aux != NULL)
	{
		if(aux->inside)
		{
			aux->cuanto -= CUANTO;
		}
		if(aux->cuanto <= 0)
		{
			elimina = aux;
			if(aux==pross)
			{
				pross = pross->sig;
				aux = pross;
			}else{
				aux = aux->sig;
				ancla->sig = aux;
			}
			
			memAsign = elimina->asing;
			memAsign->pro = NULL;
			
			eliminaPro(elimina);
		}else{
			ancla = aux;
			aux = aux->sig;
		}
	}
	
	return (pross);
			
}

NodoMem* creaParticiones(NodoMem* raiz,Proceso* pross)//Busca en donde poner el proceso en la memoria, se apoya de asigna()
{
	Proceso* auxP;
	NodoMem* auxM;
	auxP = pross;
	
	while(auxP != NULL)
	{
		if(auxP->inside == false)
		{
			auxM = raiz;
			asignaMem(auxM,auxP);
		}
		
		auxP = auxP->sig;
	}
	
	return raiz;
}

void unirParticiones(NodoMem* nodo)//Condensa los huecos consiguos de memoria
{
	NodoMem* auxL,* auxD;
	if(nodo!=NULL)
	{
		if((nodo->pro == NULL))
		{
			if ((nodo->der != NULL) && (nodo->izq != NULL))
			{
				auxL = nodo->izq;
				auxD = nodo->der;
				if((auxD->pro == NULL && auxL->pro == NULL) && (auxL->izq == NULL && auxL->der == NULL) && (auxD->izq == NULL && auxD->der == NULL))
				{
					eliminaMem(auxL);
					eliminaMem(auxD);
				
					nodo->izq = NULL;
					nodo->der = NULL;
					condens = true;
				}
			}
			unirParticiones(nodo->izq);
			unirParticiones(nodo->der);
		}
	}
}

void asignaMem(NodoMem* nodo, Proceso* pros)//Asigna los procesos en la memoria correspondiente
{
	NodoMem* auxL,* auxD;
	if(pros->inside==false)
	{
		if((nodo->pro == NULL))
		{
			if(((nodo->tam/2 < pros->tam) || (nodo->tam == 32)))
			{
				if ((nodo->der == NULL) && (nodo->izq == NULL))
				{
					nodo->pro = pros;
					pros->asing = nodo;
					pros->inside = true;
				}	
			}else{
				if((nodo->der == NULL) && (nodo->izq == NULL) && (nodo->tam != 32))
				{
					auxL = creaMem();
					auxD = creaMem();
				
					auxL->der = NULL;
					auxL->izq = NULL;
					auxL->pro = NULL;
					auxL->tam = nodo->tam/2;
				
					auxD->der = NULL;
					auxD->izq = NULL;
					auxD->pro = NULL;
					auxD->tam = nodo->tam/2;
				
					nodo->izq = auxL;
					nodo->der = auxD;
				}
				asignaMem(nodo->izq,pros);
				asignaMem(nodo->der,pros);
			}
		}
	}
}
