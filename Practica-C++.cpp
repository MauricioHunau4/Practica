#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;

struct pedido {
    char domicilio[30];
    int zona;
    char comercio[30];
    char rubro[30];
    float importe;
};

//Para recorrer el archivo
struct aux {
    char nombre[30];
    char domicilio[30];
    char comercio[30];
    int zona;
};

struct Nodo {
    pedido info;
    Nodo* sig;
};

//Nodo de reparto
struct NodoReparto {
    pedido info;
    char repar[30];
    NodoReparto* next;
};

struct Nodoarbol {
	pedido ped;
    Nodoarbol* izq;
    Nodoarbol* der;
};

//Elegir opciones
int menu();

//Hacer la Lista
void insertar(Nodo*& primero, pedido pedi, FILE* f);

//Ingresar por teclado
void ingresarPorTeclado(pedido &pedido);

//Eliminar de lista principal y llevar a los repartidores
void repartir(Nodo*& primero, int cantRepart, NodoReparto*& primerReparto, char nomrepar[30]);

//Copiar pedidos y pasarlos a repartos
void copiar(Nodo temp, Nodo*& primero, NodoReparto* p);

//Chequear si el nombre esta en el archivo
bool chequearNombre(char nom[30], FILE* f);

void listar(Nodoarbol* raiz);

//void insertarOrdenado(Nodoarbol*& raiz, int dato);
void mostrar(NodoReparto* primerReparto);

void insertapediord(NodoReparto* lista2, pedido pedi, char nom[30]);

void eliminaprimero(NodoReparto*& primero);

int main() {
    FILE* f;
    pedido pedi;
    int respuesta = 0, nrozona=0, cantRepart=0;
    pedi.importe = 0; pedi.zona = 0;
    char nom[30];
	Nodoarbol* raiz;
    Nodo* primero1 = NULL;
    Nodo* primero2 = NULL;
    Nodo* primero3 = NULL;
    Nodo* primero4 = NULL;
    Nodo* primero5 = NULL;
    Nodo* primero6 = NULL;

    NodoReparto* primerReparto = NULL;

    f = fopen("parrilas.dat", "rb+");
    do {
        respuesta = menu();
        if (respuesta == 1) {
            ingresarPorTeclado(pedi);
            switch (pedi.zona) {
            case 1:
                insertar(primero1, pedi, f);
                break;
            case 2:
                insertar(primero2, pedi, f);
                break;
            case 3:
                insertar(primero3, pedi, f);
                break;
            case 4:
                insertar(primero4, pedi, f);
                break;
            case 5:
                insertar(primero5, pedi, f);
                break;
            case 6:
                insertar(primero6, pedi, f);
                break;
            }
        }
        else {
            if (respuesta == 2) {
                cout << "Nombre del repartidor: " << endl;
                cin >> nom;
                if (chequearNombre(nom, f)) {
                    cout << "De que zona venis?" << endl;
                    cin >> nrozona;
                    cout << "Cuantos pedidos vas a repartir?" << endl;
                    cin >> cantRepart;
                }
                else {
                    cout << "No esta registrado en el sistema\n"; nrozona = 0;
                }
                switch (nrozona) {
                case 1:
                    repartir(primero1, cantRepart, primerReparto, nom);
                    break;
                case 2:
                    repartir(primero2, cantRepart, primerReparto, nom);
                    break;
                case 3:
                    repartir(primero3, cantRepart, primerReparto, nom);
                    break;
                case 4:
                    repartir(primero4, cantRepart, primerReparto, nom);
                    break;
                case 5:
                    repartir(primero5, cantRepart, primerReparto, nom);
                    break;
                case 6:
                    repartir(primero6, cantRepart, primerReparto, nom);
                    break;
                }
            }
            else {
                if (respuesta == 3) {
                    mostrar(primerReparto);
                }

            }
        }
    } while (respuesta!=4);
 	listar(raiz);
    return 0;
}

void insertar(Nodo*& primero, pedido pedi, FILE* f) {
    aux auxiliar;
    fseek(f, 0, SEEK_SET);
    fread(&auxiliar, sizeof(auxiliar), 1, f);
    while (!feof(f)) {
        if ((strcmp(pedi.comercio, auxiliar.comercio) == 0) && (pedi.zona == auxiliar.zona)) {
            Nodo* p, * r, * ant = NULL;
            p = new Nodo;
            p->info = pedi;
            r = primero;
            while (r != NULL) {
                ant = r;
                r = r->sig;
            }
            p->sig = r;
            if (r != primero) {
                ant->sig = p;
            }
            else {
                primero = p;
            }
            return;
        }
        fread(&auxiliar, sizeof(auxiliar), 1, f);
    }
    cout << "No concuerda con el archivo" << endl;
}

int menu() {
    int respuesta;
    cout << "Seleccionar opcion: " << endl;
    cout << "1. Hacer pedido." << endl << " 2. Asignar a repartidor." << endl << "3. Mostrar pedido" << endl << "4. Salir." << endl;
    cin >> respuesta;
    return respuesta;
}

void ingresarPorTeclado(pedido &pedido) {
    cout << "Digite el domicilio: " << endl;
    cin >> pedido.domicilio;
    cout << "Zona: " << endl;
    cin >> pedido.zona;
    cout << "Comercio: " << endl;
    cin >> pedido.comercio;
    cout << "Rubro: " << endl;
    cin >> pedido.rubro;
    cout << "Importe: " << endl;
    cin >> pedido.importe;
}

void repartir(Nodo*& primero, int cantRepart, NodoReparto*& primerReparto, char nomrepar[30]) {
    Nodo temp; temp.info.importe = 0; temp.info.zona = 0;
    //temp para guardar los datos temporalmente
    //if(primero!=NULL){
    NodoReparto* p=NULL, * q=NULL, * ant = NULL;

    for (int i = 0; i < cantRepart; i++) {
        //Copiar el pedido en un nodo temporal
        copiar(temp, primero, p);
        strcpy(p->repar, nomrepar);
        q = primerReparto;
        q = q->next;
        p->next = q;

        if (q != primerReparto)
            ant->next = p;
        else
            primerReparto = p;

        Nodo* w = primero;
        primero = primero->sig;
        delete w;
    }
}

void copiar(Nodo temp, Nodo*& primero, NodoReparto* p) {
    //Copiar el pedido en un nodo temporal
    strcpy(temp.info.domicilio, primero->info.domicilio);
    strcpy(temp.info.comercio, primero->info.comercio);
    temp.info.zona = primero->info.zona;
    strcpy(temp.info.rubro, primero->info.rubro);
    temp.info.importe = primero->info.importe;

    p = new NodoReparto;

    //Pasar info de nodo temporal al nodo de reparto
    strcpy(p->info.domicilio, temp.info.domicilio);
    strcpy(p->info.comercio, temp.info.comercio);
    p->info.zona = temp.info.zona;
    strcpy(p->info.rubro, temp.info.rubro);
    p->info.importe = temp.info.importe;
}

bool chequearNombre(char nom[30], FILE* f) {
    aux auxiliar;
    fseek(f, 0, SEEK_SET);
    fread(&auxiliar, sizeof(auxiliar), 1, f);
    while (!feof(f)) {
        if (strcmp(auxiliar.nombre,nom)==0) { //Si hay coincidencia retorna true
            fseek(f, 0, SEEK_SET);
            return true;
        }
        fread(&auxiliar, sizeof(auxiliar), 1, f);
    }
    fseek(f, 0, SEEK_SET);
    return false; //Como no hubo coincidencia, retorna false
}

void eliminaprimero(NodoReparto*& primero) {
    NodoReparto* aux = primero;
    primero = primero->next;
    delete(aux);
}

void insertapediord(NodoReparto* lista2, pedido pedi, char nom[30]) {
    NodoReparto* nuevo = new NodoReparto(), *aux = lista2, *antLista = NULL , *ant = NULL;
    Nodoarbol* p, * antArbol, *raiz,* n = new Nodoarbol;
    n->ped = pedi;
    n->izq = n->der = NULL;
    p = raiz;

	   nuevo->info = pedi;
    strcpy(nuevo->repar, nom);
     while (p != NULL) //Ubico el nodo ordenado en el arbol
     {
        antArbol = p;
        if (nom < n->ped.comercio){
        	p = p->izq;
		}else{
			p = p->der;
		}
    }

     if (raiz == NULL) //Enlazo el nodo ya ordenado al arbol
        raiz = n;
     else{
        if (nom< antArbol->ped.comercio){
            antArbol->izq = n;
        }
        else{
            antArbol->der = n;
        }
    }


    if(lista2 == NULL){ //Por si la lista auxiliar aun no tiene nodos, se inserta de primero
        nuevo->next = lista2;
        lista2 = nuevo;
    }
    else {
        while ((aux!=NULL)&&(strcmp(aux->repar,nom)<0)) {//Con este while recorremos hasta que la lista acabe o que aux->repar sea mayor que el nom recibido
            NodoReparto* ant;
			ant = aux;
            aux = aux->next;
        }
         //En caso de que aux apunte a un nodo con mismo nombre de repar y el importe del pedido sea menor que el de aux...
        while ((strcmp(aux->repar, nom) == 0) && (pedi.importe<aux->info.importe)) { //Recorremos hasta que el importe del pedido sea mayor que el de aux o cambie el nombre
            antLista = aux;
            aux = aux->next;
        }
        antLista->next = nuevo; //insertamos el pedido nuevo entre ant y aux
        nuevo->next = aux;
    }
}
void mostrar(NodoReparto* primerReparto) {
    //Se recibe una lista de pedidos sin orden, y se ordena alfabeticamente por nombre de repartidor, y por importe de pedido
    NodoReparto* auxi = primerReparto, * ant = NULL, * listaordnom=NULL;
    while (auxi != NULL) {
        insertapediord(listaordnom, auxi->info, auxi->repar); //Insertamos ordenado por nombre e importe en listaordnom
    }
    auxi = listaordnom; //Ahora auxi nos sirve como auxiliar de la lista ordenada
    while (auxi != NULL) {
        ant = auxi;
        cout << "Repartidor: " << auxi->repar << " (zona " << auxi->info.zona << ")\n";
        while (ant->repar == auxi->repar) {
            cout << "Pedido a " << auxi->info.domicilio << " del comercio " << auxi->info.comercio << " (" << auxi->info.rubro << ")\n Importe: " << auxi->info.importe << "\n\n";
            auxi = auxi->next;
        }
    }
    cout << "Fin del informe\n\n";
    while (listaordnom != NULL) {
        eliminaprimero(listaordnom); //Eliminamos toda la lista ordenada
    }
}
void listar(Nodoarbol* raiz) { //Listado entreorden
    if (raiz != NULL)
    {
        listar(raiz->izq);
        cout << raiz->ped.domicilio << endl;
        cout << raiz->ped.comercio << endl;
        cout << raiz->ped.rubro << endl;
        cout << raiz->ped.zona << endl;
        cout << raiz->ped.importe << endl;
        listar(raiz->der);
    }
}
