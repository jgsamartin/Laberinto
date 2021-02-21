# include <thread>
# include <string>
# include <iostream>
# include <fstream>
# include <cstring>
using namespace std;

# define M 25
# define N 100
# define ROCA '#'        // Símbolo de la roca
# define INICIO 'I'      // Carácter de inicio
# define FIN 'O'         // Carácter de fin
# define CAMINO 'C'      // Carácter para indicar si se ha pasado por ahí
# define HUECO ' '       // Carácter para indicar que esa casilla tiene un hueco (se puede pasar por ella)
# define DIM 2           // Número de dimensiones del juego

int pasos = 0;
int nThreads = 0;
int pasosTotales = 0;

/*
    Función para leer el archivo txt 
    Devuelve un puntero a la matriz del laberinto
*/
void cargaLaberinto (char *labFile, char labArray[M][N]) {

    ifstream inFile;
    inFile.open(labFile);    
    int cont = 0;
    string linea;

    if (inFile.is_open()){
        while (!inFile.eof()){
            getline(inFile,linea);
            strcpy(labArray[cont],linea.c_str());
            cont++;
        }
    }
    else {
        cout << "No existe" << endl;
    }

}

/*
    Función que comprueba si la casilla seleccionada es o no accesible
*/
inline int esAccesible (char labArray[M][N], int x, int y) {
    return labArray[x][y] != ROCA && labArray[x][y] != CAMINO && x >= 0 && y >= 0 && x < M && y < N;
}

/*
    Función que comprueba si la casilla seleccionada es o no el final
*/
inline int esFinal (char labArray[M][N], int x, int y) {
    return labArray[x][y] == FIN;
}

/*
    Se mueve desde la posición (x,y) a todas las casillas adyacentes posibles
*/
void mueve (char labArray[M][N], int x, int y, int* success) {
    
    if (esFinal(labArray,x,y)) {
        pasos++;
        *success = 1; 
    }
    else if (!esAccesible(labArray,x,y) ) {
        *success = 0;
    } 
    else {
        // --- Marcamos que hemos pasado por la casilla
        labArray[x][y] = CAMINO;

        // --- Nos metemos recursivamente en alguna de las cuatro casillas adyacentes
        thread threads[2*DIM];
        int r1, r2, r3, r4;
        threads[0] = thread (mueve, labArray, x+1, y, &r1);
        threads[1] = thread (mueve, labArray, x, y+1, &r2);
        threads[2] = thread (mueve, labArray, x-1, y, &r3);
        threads[3] = thread (mueve, labArray, x, y-1, &r4);

        pasosTotales++;
        nThreads += 4;

        // --- Juntamos tods los threads
        for (int i = 0; i<2*DIM; i++) {
            threads[i].join();
        }

        // --- Si alguna de las casillas está en el camino de salida, hemos acertado
        if (r1 || r2 || r3 || r4) {
                pasos++;
                *success = 1;
        } else {
            labArray[x][y] = HUECO;
            *success = 0;
        }
    }
}

/*
    Función que resuelve el laberinto
*/
int juega (char labArray[M][N]) {

    int m = 0, inicio[2], fin[2];
    inicio[1] = 0;
    fin[1] = N-1;
    
    // --- Busca la posición inicial
    while(m<M){
        if (labArray[m][inicio[1]] == INICIO) inicio[0] = m;
        if (labArray[m][fin[1]] == FIN) fin[0] = m;
        m++;
    }

    cout << "Inicio : " << inicio[0]+1 << "," << inicio[1]+1 << endl;
    cout << "Fin : " << fin[0]+1 << "," << fin[1]+1 << endl;

    cout << "Coordenada inicial : " << inicio[0]+1 << "," << inicio[1]+1 << endl;
    cout << "Coordenada final : " << fin[0]+1 << "," << fin[1]+1 << endl;

    int i = inicio[0];
    int j = inicio[1];

    // --- Para imprimir "Victoria" o "Derrota"
    //string estados[2] = {"Derrota", "Victoria"};
    int result = 0;

    // --- Desde la posición inicial, se mueve
    mueve (labArray,i,j, &result);

    // --- Imprimir resultado por pantalla
    //cout << estados[result] << endl;
    return result;
}

/* Main */
int main (int argc, char * argv[]) {
    /* Matriz que almacena el laberinto */
    char laberinto[M][N];

    if (argc<2) {
        cout << "¡Se necesita cargar un laberinto para empezar!" << endl;
    }
    else {
        char name[15];
        strcpy(name, argv[1]);
        cargaLaberinto (name, laberinto);
    }

    juega(laberinto);

    cout << "Número total de pasos recorridos : "<< pasosTotales << endl;
    cout << "Número de hilos creados : "<< nThreads << endl;
    cout << "Número mínimo de pasos : "<< pasos << endl;

    /* SACAR LABERINTO POR PANTALLA
    for (int i=0; i<M; i++){
        for (int j=0; j<N; j++){
            cout << laberinto[i][j];
        }
        cout << endl;
    }*/
    
   return 0;

}