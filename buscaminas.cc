#include <iostream>
#include <time.h>		//funcion time(), time(NULL) == hora actual (Para generar numeros aleatorios diferentes en cada ejecución
#include <stdlib.h>		//funcion rand() srand(unsigned int seed)
#include <vector>
using namespace std;

const int DIM = 10;

typedef vector<char> Fila;
typedef vector<Fila> Tablero;

typedef vector<bool> Row;
typedef vector<Row> Control;

void azar() {
	srand((unsigned)time(NULL));
}

void dibuja_tablero(const Tablero &tabla, const Control &booleano) {
	cout << "0 1 2 3 4 5 6 7 8 9" << endl;
	cout << "- - - - - - - - - -" << endl;
	for (int i = 0; i < DIM; ++i) {
		for (int j = 0; j < DIM; ++j) {
			if (booleano[i][j]) cout << tabla[i][j] << " ";
			else cout << "? ";
		}
		cout << "| " << i << endl;
	}
	cout << endl;
}

void jugada(const Tablero &tabla, Control &booleano, int x, int y, bool &gameover, bool &victoria) {
	if (booleano[x][y]) cout << "Casilla ya visitada" << endl << endl;
	else if (tabla[x][y] == '$') {
		gameover = true;
		for (int i = 0; i < DIM; ++i) {
			for (int j = 0; j < DIM; ++j) {
				booleano[i][j] = true;
			}
		}
	}
	else if (tabla[x][y] != '0') {
		booleano[x][y] = true;
		int a, b;
		victoria = true;
		a = b = 0;
		while (a < DIM and victoria) {
			while (b < DIM and victoria) {
				if (tabla[a][b] != '$' and not booleano[a][b]) victoria = false;
				++b;
			}
			++a;
		}
		if (victoria) {
			for (int p = 0; p < DIM; ++p) {
				for (int q = 0; q < DIM; ++q) {
					booleano[p][q] = true;
				}
			}
		}
	}
	else {
		booleano[x][y] = true;
		if (x-1 >= 0 and y-1 >= 0 and not booleano[x-1][y-1]) jugada(tabla, booleano, x-1, y-1, gameover,victoria);
		if (x-1 >= 0 and not booleano[x-1][y]) jugada(tabla, booleano, x-1, y, gameover,victoria);
		if (x-1 >= 0 and y+1 < DIM and not booleano[x-1][y+1]) jugada(tabla, booleano, x-1, y+1, gameover,victoria);
		if (y-1 >= 0 and not booleano[x][y-1]) jugada(tabla, booleano, x, y-1, gameover,victoria);
		if (y+1 < DIM and not booleano[x][y+1]) jugada(tabla, booleano, x, y+1, gameover,victoria);
		if (x+1 < DIM and y-1 >= 0 and not booleano[x+1][y-1]) jugada(tabla, booleano, x+1, y-1, gameover,victoria);
		if (x+1 < DIM and not booleano[x+1][y]) jugada(tabla, booleano, x+1, y, gameover,victoria);
		if (x+1 < DIM and y+1 < DIM and not booleano[x+1][y+1]) jugada(tabla, booleano, x+1, y+1, gameover,victoria);
	}
}

void rellena_tablero(Tablero &tabla) {
	int euros;
	for (int i = 0; i < DIM; ++i) {
		for (int j = 0; j < DIM; ++j) {
			euros = 0;
			if (tabla[i][j] != '$') {
				if (i+1 < DIM and j+1 < DIM and tabla[i+1][j+1] == '$') ++euros;
				if (i-1 >= 0 and j-1 >= 0 and tabla[i-1][j-1] == '$') ++euros;
				if (i+1 < DIM and j-1 >= 0 and tabla[i+1][j-1] == '$') ++euros;
				if (i-1 >= 0 and j+1 < DIM and tabla[i-1][j+1] == '$') ++euros;
				if (j+1 < DIM and tabla[i][j+1] == '$') ++euros;
				if (j-1 >= 0 and tabla[i][j-1] == '$') ++euros;
				if (i+1 < DIM and tabla[i+1][j] == '$') ++euros;
				if (i-1 >= 0 and tabla[i-1][j] == '$') ++euros;
				tabla[i][j] = (char)(euros + 48);
			}
		}
	}
}

void genera_minas(Tablero &tabla, Control &booleano) {
	int i = 0;
	int a, b;
	while (i < 15) {
		a = (rand()%DIM);
		b = (rand()%DIM);
		if (not booleano[a][b]) {
			tabla[a][b] = '$';
			booleano[a][b] = true;
			++i;
		}
	}
	for (int j = 0; j < DIM; ++j) {
		for (int k = 0; k < DIM; ++k) {
			booleano[j][k] = false;
		}
	}
}

int main() {
	azar(); // inicializamos generacion numeros aleatorios
	Tablero tabla(DIM, Fila(DIM,'0'));
	Control booleano(DIM, Row(DIM,false));
	genera_minas(tabla, booleano);
	rellena_tablero(tabla);
	int x, y;
	bool victoria = false;
	bool gameover = false;
	while (not gameover and not victoria) {
		cout << "Introduce las coordenadas de la casilla: " << endl;
		cin >> x >> y;
		cout << endl;
		jugada(tabla, booleano, x, y, gameover, victoria);
		dibuja_tablero(tabla,booleano);
	}
	if (victoria) cout << "Enhorabuena y gracias por jugar!" << endl;
	else if (gameover) cout << "Vaya has perdido.. Suerte en la proxima!" << endl;
}
