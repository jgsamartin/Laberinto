# include <thread>
# include <iostream>
using namespace std;

# define N 100          // Tamaño máximo del laberinto
# define roca '#'        // Símbolo de la roca
# define inicio 'I'      // Carácter de inicio
# define fin 'O'         // Carácter de fin
# define camino 'C'      // Carácter para indicar si se ha pasado por ahí

/*
    Función para leer el archivo txt 
    Devuelve un puntero a la matriz del laberinto
*/
void cargaLaberinto (char *labFile, char labArray[N][N]) {

}

/*
    Función que comprueba si la casilla seleccionada es o no accesible
*/
int esAccesible (char labArray[N][N], int x, int y, int n, int m) {
    return labArray[x][y] != roca && labArray[x][y] != inicio && labArray[x][y] != camino && x >= 0 && y >= 0 && x < n && y < m;
}

/*
    Función que comprueba si la casilla seleccionada es o no el final
*/
int esFinal (char labArray[N][N], int x, int y) {
    return labArray[x][y] == fin;
}

/*
    Se mueve desde la posición (x,y) a todas las casillas adyacentes posibles
*/
int mueve (int x, int y) {

}

/*
    Función que resuelve el laberinto
*/
int juega (char labArray[N][N]) {
    int inicio[2] = {21, 0};
    int fin[2] = {5, 99};

    int i = inicio[0];
    int j = inicio[1];

    // --- Desde la posición inicial, se mueve
    mueve (i,j);
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