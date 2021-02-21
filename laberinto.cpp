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

int pasos = 0;

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
int esAccesible (char labArray[M][N], int x, int y) {
    int n = 100;
    int m = 25;
    return labArray[x][y] != ROCA && labArray[x][y] != CAMINO && x >= 0 && y >= 0 && x < m && y < n;
}

/*
    Función que comprueba si la casilla seleccionada es o no el final
*/
int esFinal (char labArray[M][N], int x, int y) {
    return labArray[x][y] == FIN;
}

/*
    Se mueve desde la posición (x,y) a todas las casillas adyacentes posibles
*/
int mueve (char labArray[M][N], int x, int y) {

    if (esFinal(labArray,x,y)) {
        cout << pasos << endl;
        return 1; 
    }
    else if (!esAccesible(labArray,x,y) ) {
        return 0;
    } 
    else {
        // --- Marcamos que hemos pasado por la casilla
        labArray[x][y] = CAMINO;

        // --- Si alguna de las casillas está en el camino de salida, hemos acertado
        if (mueve(labArray, x+1, y) ||
            mueve(labArray, x, y+1) ||
            mueve(labArray, x-1, y) ||
            mueve(labArray, x, y-1)) {
                //cout << "En la posición número" << pasos <<", se pasa por el punto: (" << x << "," << y << ")" << endl;
                pasos++;
                return 1;
        } else {
            labArray[x][y] = HUECO;
            //pasos--;
            return 0;
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
    
    while(m<M){
        if (labArray[m][inicio[1]] == INICIO) inicio[0] = m;
        if (labArray[m][fin[1]] == FIN) fin[0] = m;
        m++;
    }

    cout << "Inicio : " << inicio[0]+1 << "," << inicio[1]+1 << endl;
    cout << "Fin : " << fin[0]+1 << "," << fin[1]+1 << endl;

    int i = inicio[0];
    int j = inicio[1];

    // --- Desde la posición inicial, se mueve
    if(mueve (labArray,i,j)) {
        cout << "Victoria" << endl;
        return 1;
    } else {
        cout << "Derrota" << endl;
        return 0;
    }
}

/* Main */
int main (char argc, char * argv[]) {
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

    ///* SACAR LABERINTO POR PANTALLA
    for (int i=0; i<M; i++){
        for (int j=0; j<N; j++){
            cout << laberinto[i][j];
        }
        cout << endl;
    }
    
   return 0;

}