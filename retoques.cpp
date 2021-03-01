# include <thread>
# include <string>
# include <iostream>
# include <fstream>
# include <cstring>
# define M 25       // Filas del laberinto
# define N 100      // Columnas del laberinto
# define ROCA '#'
# define INICIO 'I'
# define FIN 'O'
# define CAMINO 'C' // Relleno del camino a seguir
# define HUECO ' '  // Espacio libre o accesible en el laberinto

using namespace std;

int inicio[2], fin[2];  // Coordenadas de inicio y final
int nThreads = 0;       // número total de hilos
int start[20];          // vector con todas las coordenadas de inicio de los hilos
int endPos[20];         // vector con todas las coordenadas de final de los hilos
int pasos[10];          // vector con todos los pasos de los distintos hilos
int minPasos = 0;       // mínimo número de pasos para resolver el laberinto

// Lectura del laberinto del archivo de texto
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

// Devuelve un 1 si el espacio es accesible (hueco) o un 0 si no lo es (roca, camino ocupado o fuera del laberinto)
inline int esAccesible (char labArray[M][N], int x, int y) {
    return labArray[x][y] != ROCA && labArray[x][y] != CAMINO && x >= 0 && y >= 0 && x < M && y < N;
}

// Devuelve un 1 si el espacio es el final del laberinto o un 0 si no lo es
inline int esFinal (char labArray[M][N], int x, int y) {
    return labArray[x][y] == FIN;
}

// Movimiento recursivo a los espacios contiguos accesibles
void mueve (char labArray[M][N], int x, int y, int* success, int nHilo) {
    
    if (esFinal(labArray,x,y)) {
        minPasos++;
        *success = 1;
        endPos[2*nHilo]=x;
        endPos[2*nHilo+1]=y;
    }
    else if (!esAccesible(labArray,x,y)) {
        *success = 0;
    } 
    else {
        labArray[x][y] = CAMINO;    // Paso por el espacio accesible
        pasos[nHilo]++;

        thread threads[2];  // Vector de 2 hilos (máximo de hilos creados en trifurcaciones)
        int s1 = 0, s2 = 0, s3 = 0, s4 = 0;
        int nT = 0; // número de hilos en una sola bi o trifurcación
        
        // Creación de hilos y recursividad SOLO en bi o trifurcaciones
        if (esAccesible(labArray,x+1,y)) {
            mueve (labArray, x+1, y, &s1, nHilo);
            if (esAccesible(labArray,x,y+1)) {
                threads[nT] = thread (mueve, labArray, x, y+1, &s2, nThreads);
                start[2*nThreads]=x;
                start[2*nThreads+1]=y+1;
                nThreads++;
                nT++;
            }
            if (esAccesible(labArray,x-1,y)) {
                threads[nT] = thread (mueve, labArray, x-1, y, &s3, nThreads);
                start[2*nThreads]=x-1;
                start[2*nThreads+1]=y;                
                nThreads++;
                nT++;
            }
            if (esAccesible(labArray,x,y-1)) {
                threads[nT] = thread (mueve, labArray, x, y-1, &s4, nThreads);
                start[2*nThreads]=x;
                start[2*nThreads+1]=y-1;                
                nThreads++;
                nT++;
            }
        }
        
        else if (esAccesible(labArray,x,y+1)) {
            mueve (labArray, x, y+1, &s2, nHilo);
            if (esAccesible(labArray,x-1,y)) {
                threads[nT] = thread (mueve, labArray, x-1, y, &s3, nThreads);
                start[2*nThreads]=x-1;
                start[2*nThreads+1]=y;                
                nThreads++;
                nT++;
            }
            if (esAccesible(labArray,x,y-1)) {
                threads[nT] = thread (mueve, labArray, x, y-1, &s4, nThreads);
                start[2*nThreads]=x;
                start[2*nThreads+1]=y-1;                
                nThreads++;
                nT++;
            }
        }
        
        else if (esAccesible(labArray,x-1,y)) {
            mueve (labArray, x-1, y, &s3, nHilo);
            if (esAccesible(labArray,x,y-1)) {
                threads[nT] = thread (mueve, labArray, x, y-1, &s4, nThreads);
                start[2*nThreads]=x;
                start[2*nThreads+1]=y-1;                
                nThreads++;
                nT++;
            }
        }
        
        else if (esAccesible(labArray,x,y-1)) mueve (labArray, x, y-1, &s4, nHilo);

        else { 
            endPos[2*nHilo]=x;
            endPos[2*nHilo+1]=y;
        }

        for (int i = 0; i<nT; i++) { // Destrucción (join) de threads
            threads[i].join();
        }

        if (s1 || s2 || s3 || s4) {     // Si alguno de los espacios llegará al final, ese es el camino
                minPasos++;
                *success = 1;
        } else {
            labArray[x][y] = HUECO;
            *success = 0;
        }

    }
}

// Inicio y final y resolución del laberinto
void juega (char labArray[M][N]) {

    int m = 0;
    inicio[1] = 0;
    fin[1] = N-1;
    
    while(m<M){
        if (labArray[m][inicio[1]] == INICIO) inicio[0] = m;
        if (labArray[m][fin[1]] == FIN) fin[0] = m;
        m++;
    }

    int result = 0;
    mueve (labArray,inicio[0],inicio[1], &result, 9); // Rastreo y resolución del laberinto

}

int main (int argc, char * argv[]) {

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

    for (int i=0; i<M; i++){
        for (int j=0; j<N; j++){
            cout << laberinto[i][j];
        }
        cout << endl;
    }

    cout << endl;

    cout << "In coordinates : " << inicio[0]+1 << "," << inicio[1]+1 << endl;
    cout << "Out coordinates : " << fin[0]+1 << "," << fin[1]+1 << endl;
    cout << "Número de hilos creados : "<< nThreads << endl;
    for (int i = 0; i<nThreads; i++) cout << "Hilo " << i+1 << " :: start position:" << start[2*i]+1 << "," << start[2*i+1]+1 << " end position:" << endPos[2*i]+1 << "," << endPos[2*i+1]+1 << " no.steps:" << pasos[i] << endl;
    cout << "Número mínimo de pasos : "<< minPasos << endl;

   return 0;

}