# include <thread>
# include <iostream>
using namespace std;

# define N 100

/*
    Función para leer el archivo txt 
    Devuelve un puntero a la matriz del laberinto
*/
void cargaLaberinto (char *labFile, char labArray[N][N]) {

}

/*
    Función que crea resuelve el laberinto con hilos
*/
int juega (char labArray[N][N]) {

}

/* Main */
int main (char argc, char * argv[]) {
    /* Matriz que almacena el laberinto */
    char laberinto[N][N];
    
    if (!argc) {
        cout << "¡Se necesita cargar un laberinto para empezar!" << endl;
    } else {
        cargaLaberinto (argv[2], laberinto);

    }
}