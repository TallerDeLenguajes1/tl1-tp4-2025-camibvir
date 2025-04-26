#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
    }Tarea;
typedef struct Nodo{
    struct Tarea T;
    struct Nodo *Siguiente;
    }Nodo;

Nodo * crearListaVacia();
Nodo * crearNodo(Tarea nuevaTarea);
void pedirTarea(Nodo **listatareasPendientes);
void insertarNodo(Nodo **listTareasPendientes, Tarea nuevaTarea);
void liberarLista(Nodo *lista);


int main (){
    Nodo *listaTareasPendientes = crearListaVacia();
    Nodo *listaTareasRealizadas = crearListaVacia();
    pedirTarea(&listaTareasPendientes);
    liberarLista(listaTareasPendientes);
    return 0;


}

Nodo * crearListaVacia()
{
    return NULL;
}

Nodo * crearNodo(Tarea nuevaTarea)
{
    Nodo * nuevoNodo = (Nodo *) malloc (sizeof(Nodo));
    nuevoNodo->T = nuevaTarea;
    nuevoNodo->Siguiente = NULL;
    return nuevoNodo;
}


void pedirTarea(Nodo **lista) {
    int respuesta;
    static int i = 1000; 
    
    do {
        Tarea nuevaTarea;
        char buffer[100]; 
        
        printf("Ingrese la descripcion de la tarea pendiente: \n");
        getchar();//Limpia linea residual del input anterior
        gets(buffer); 
        
        nuevaTarea.Descripcion = (char *)malloc(strlen(buffer) + 1);
        strcpy(nuevaTarea.Descripcion, buffer);
        
        printf("Ingrese la duración de la tarea pendiente (10-100): \n");
        scanf("%d", &nuevaTarea.Duracion);
        
        while (nuevaTarea.Duracion < 10 || nuevaTarea.Duracion > 100) {
            printf("Duración inválida. Ingrese un valor entre 10 y 100: \n");
            scanf("%d", &nuevaTarea.Duracion);
        }
        
        nuevaTarea.TareaID = i++;
        
        insertarNodo(lista, nuevaTarea);
        
        printf("¿Desea agregar otra tarea? (1: Sí, 0: No): ");
        scanf("%d", &respuesta);
        
    } while (respuesta != 0);
}

void insertarNodo (Nodo **lista, Tarea nuevaTarea)
{
    Nodo *nuevoNodo = crearNodo(nuevaTarea);
    
    if (*lista == NULL) {
        *lista = nuevoNodo;
    } else {
        Nodo *actual = *lista;
        while (actual->Siguiente != NULL) {
            actual = actual->Siguiente;
        }
        actual->Siguiente = nuevoNodo;
    }
}

void liberarLista(Nodo *lista) {
    Nodo *actual = lista;
    while (actual != NULL) {
        Nodo *temp = actual;
        actual = actual->Siguiente;
        free(temp->T.Descripcion);
        free(temp);
    }
}








