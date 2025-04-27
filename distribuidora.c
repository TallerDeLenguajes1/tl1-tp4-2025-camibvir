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
void pedirTarea(Nodo **start);
void insertarNodoAlFinal(Nodo **start, Tarea nuevaTarea);
int buscarNodo (Nodo **start, int id, Nodo **startListaNueva);
void eliminarNodo (Nodo **start, int id);
void mostrarLista(Nodo **start);
void liberarLista(Nodo *lista);
int buscarPorId(Nodo **start, Nodo **startListaNueva, int idBuscar);
int buscarPorPalabra(Nodo **start, Nodo **startListaNueva, char palabra[100]);



int main (){
    
    Nodo *startTareasPend = crearListaVacia();
    Nodo *startTareasRealiz = crearListaVacia();
    int opcion;
    pedirTarea(&startTareasPend);
    printf("\n¿Qué operación desea realizar?\n");
    printf("1- Ingresar nueva tarea pendiente\n");
    printf("2- Mover tarea pendiente a realizadas\n");
    printf("3- Mostrar listas\n");
    scanf("%d", &opcion);
    do{
        switch (opcion)
        {
    case 1:
        pedirTarea(&startTareasPend);
        break;
    case 2:
        int idBuscar;    
        do{
            printf("Ingrese el id de la tarea a transferir (id mayor que 1000): \n");
            scanf("%d", &idBuscar);
            if(buscarNodo(&startTareasPend, idBuscar, &startTareasRealiz)){
                eliminarNodo(&startTareasPend, idBuscar);
            }else{
                break;
            }
        }while(idBuscar < 1000);
        break;
    case 3:
        printf("Tareas pendientes: ");
        printf("\n");
        mostrarLista(&startTareasPend);
        printf("\n");
        printf("Tareas realizadas: ");
        printf("\n");
        mostrarLista(&startTareasRealiz);
        break;
    
    default:
        break;
        }
    }while(opcion == 0);
    
    // Nodo *listaTareasRealizadas = crearNodo();
    
    
    liberarLista(startTareasRealiz);
    liberarLista(startTareasPend);
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


void pedirTarea(Nodo **start) {
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
        
        insertarNodoAlFinal(start, nuevaTarea);        
        printf("Si quiere agregar otra tarea (1: Sí, 0: No): ");
        scanf("%d", &respuesta);
        
    } while (respuesta != 0);
}

void insertarNodoAlFinal (Nodo **start, Tarea nuevaTarea)
{
    Nodo *nuevoNodo = crearNodo(nuevaTarea);
    
    if (*start == NULL) {
        *start = nuevoNodo;
    } else {
        Nodo *actual = *start;
        while (actual->Siguiente) {
            actual = actual->Siguiente;
        }
        actual->Siguiente = nuevoNodo;
    }
}

void liberarLista(Nodo *start) {
    Nodo *actual = start;
    while (actual != NULL) {
        Nodo *temp = actual;
        actual = actual->Siguiente;
        free(temp->T.Descripcion);
        free(temp);
    }
}

int buscarNodo(Nodo **start, int id, Nodo **startListaNueva){
    Nodo * Aux = *start;
    while(Aux && Aux->T.TareaID != id)
    {
    Aux = Aux -> Siguiente;
    }
    if(Aux){
        Tarea tareaTrans = Aux->T;
        insertarNodoAlFinal(startListaNueva, tareaTrans);
        return 1;
    }else{
        printf("Id no encontrado");
        return 0;
    }
    
}

void eliminarNodo (Nodo **start, int id){
    Nodo *nodoAux = (*start);
    Nodo *nodoAnt = NULL;
    while (nodoAux != NULL && nodoAux->T.TareaID != id){
        nodoAnt = nodoAux;
        nodoAux = nodoAux->Siguiente;
    }
    if (nodoAux != NULL){
        if (nodoAux == (*start)){
            (*start) = nodoAux->Siguiente;
        }
        else{
        nodoAnt->Siguiente = nodoAux->Siguiente;
        }
        nodoAux->Siguiente = NULL;
        free(nodoAux->T.Descripcion);
        free(nodoAux);
        }
    }

    void mostrarLista(Nodo **start){
        Nodo *nodoAux = (*start);
        while(nodoAux != NULL){
            printf("Id: %d\n", nodoAux->T.TareaID);
            printf("Descripcion: %s\n", nodoAux->T.Descripcion);
            printf("Duracion: %d\n\n", nodoAux->T.Duracion);
            nodoAux = nodoAux->Siguiente;
        }
    }