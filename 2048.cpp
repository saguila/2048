#include<iostream>
#include<ctime>
#include<string>
#include<Windows.h>
#include<fstream>
#include<iomanip>
#include<conio.h>

using namespace std;

const int DIM = 4;
const char extremo_superior_derecho = 191;
const char extremo_superior_izquierdo = 218;
const char extremo_inferior_derecho = 217;
const char extremo_inferior_izquierdo = 192;
const char separador_T_superior = 194;
const char separador_T_inferior = 193;
const char separador_T_izquierdo = 195;
const char separador_T_derecho = 180;
const char cruz = 197;
const char barra_vertical = 179;
const char barra_horizontal = 196;

const int ANCHO_CELDA = 6;
const int ALTO_CELDA = 3;


const int tecla_abajo = 80;
const int tecla_arriba = 72;
const int tecla_der = 77;
const int tecla_izq = 75;
const int tecla_esc = 27;



typedef int tTablero[DIM][DIM];

typedef enum {Arriba, Abajo, Izquierda, Derecha,Salir} tAccion;

void carga(tTablero tablero, int &puntos, bool &ok);
int generarNumeroAleatorio();
int casillaInicio();
int log2(int num);

void visualiza(const tTablero tablero, int puntos, int total);
void inicializarCasilla(tTablero tablero);
void setBackgroudColor(int color);
void inicio();
void imprimeCasilla(int numero);
void parteSuperior();
void filaVacia(const tTablero tablero, int f);
void filaSinNumero();
void filaconFicha(const tTablero tablero, int f);
void parteInferior();
void filaMedio();
void borrarTablero(tTablero tablero);

tAccion leeAccion();
void mueveFichas(tTablero tablero,tAccion accion,int &puntos);
void moverDerecha(tTablero tablero,int &puntos);
void moverIzquierda(tTablero tablero, int &puntos);
void moverArriba(tTablero tablero, int &puntos);
void moverAbajo(tTablero tablero, int &puntos);
void generarFicha(tTablero tablero, int &puntos);
int mayor(const tTablero tablero);
bool lleno(const tTablero tablero);
void combinaFichas(tTablero tablero, tAccion accion, int &puntos);
void combinaArriba(tTablero tablero, int &puntos);
void combinaAbajo(tTablero tablero, int &puntos);
void combinaDerecha(tTablero tablero, int &puntos);
void combinaIzquierda(tTablero tablero, int &puntos);


int main(){
	bool ok = false,fin = false;
	int puntos = 0,total = 0;
	srand(time(NULL));
	tTablero tablero;
	tAccion accion;
	carga(tablero, puntos, ok);
	do{
		visualiza(tablero, puntos, total);
		cout << "Use las flechas o la tecla ESC" << endl;
		accion = leeAccion();
		puntos = 0;
		if (accion != Salir){
		mueveFichas(tablero, accion, puntos);
		total = total + puntos;
		if (lleno(tablero)){
			visualiza(tablero, puntos, total);
			cout << "El juego ha terminado,no te quedan mas movimientos" << endl;
			fin = true;
		}
		if (mayor(tablero) == 2048){
			visualiza(tablero, puntos, total);
			cout << "Enhorabuena has ganado el juego" << endl;
			fin = true;
		}
	}
	else{
		cout << "Saliendo del juego ... ";
		fin = true;
	}
	} while (!fin);
	do{ cout << "Pulse intro para continuar..."; } while (!cin.get());
	return 0;
}


int generarNumeroAleatorio()
{
	int numero, numero_aleatorio;

	numero_aleatorio = (rand() % 101);

	if (numero_aleatorio <= 95){
		numero = 2;
	}
	else {
		numero = 4;
	}

	return numero;
}



int casillaInicio(){ return (rand() % 16); }



int casillaInicio(int anterior){
	int numero;
	while (numero = casillaInicio(), numero == anterior);
	return numero;
}



void visualiza(const tTablero tablero, int puntos, int total){ // Muestra el tablero completo
	system("cls");
	cout << setw(6) << puntos << setw(12)<< "Total:" << setw(8) << total << endl;
	parteSuperior();
	for (int f = 0; f < DIM; f++){
		filaVacia(tablero, f);
		filaconFicha(tablero, f);
		filaVacia(tablero, f);
		if (f != DIM - 1)	filaMedio();
	}
	parteInferior();
}


void parteSuperior(){ // Dibuja la parte superior del tablero
	cout << extremo_superior_izquierdo;
	for (int f = 0; f < DIM; f++)
	{
		for (int i = 0; i < ANCHO_CELDA; i++)
			cout << barra_horizontal;

		if (f != DIM - 1)
			cout << separador_T_superior;
	}

	cout << extremo_superior_derecho << endl;
}


void filaVacia(const tTablero tablero, int f)// Dibuja la fila que no tiene número
{

	int resultado;

	cout << barra_vertical;

	for (int c = 0; c < DIM; c++)
	{
		resultado = log2(tablero[f][c]);
		setBackgroudColor(resultado);
		cout << setw(6) << " ";
		setBackgroudColor(0);
		cout << barra_vertical;
	}

	cout << endl;
}


/* la f es la fila para sacar la ficha */
void filaconFicha(const tTablero tablero, int f)
{
	int resultado;

	cout << barra_vertical;

	for (int c = 0; c < DIM; c++)
	{
		resultado = log2(tablero[f][c]);
		setBackgroudColor(resultado);
		imprimeCasilla(tablero[f][c]);
		setBackgroudColor(0);
		cout << barra_vertical;
	}
	cout << endl;
}

/* Fila que divide las celdas. */
void filaMedio()
{
	cout << separador_T_izquierdo;

	for (int f = 0; f < DIM; f++)
	{
		for (int i = 0; i < 6; i++)
			cout << barra_horizontal;

		if (f != DIM - 1)
			cout << cruz;
	}

	cout << separador_T_derecho;
	cout << endl;
}

/* Ultima fila pintada. */
void parteInferior()
{
	cout << extremo_inferior_izquierdo;

	for (int f = 0; f < DIM; f++)
	{
		for (int e = 0; e < 6; e++)
			cout << barra_horizontal;

		if (f != DIM - 1)
			cout << separador_T_inferior;
	}

	cout << extremo_inferior_derecho;

	cout << endl;
}

void borrarTablero(tTablero tablero){
	for (int f = 0; f < DIM; f++){
		for (int c = 0; c < DIM; c++){
			tablero[f][c] = 1;
		}
	}
}

void inicializarCasilla(tTablero tablero){
	int pos1 = (rand() % DIM);
	int pos2 = (rand() % DIM);
	int numero = generarNumeroAleatorio();
	tablero[pos1][pos2] = numero;
	pos2 = pos1;
	while(pos1 = (rand() % DIM),pos1 == pos2);
	pos2 = (rand() % DIM);
	if (numero == 4) numero = 2;
	else numero = generarNumeroAleatorio();
	tablero[pos1][pos2] = numero;
}


void setBackgroudColor(int color){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}


int log2(int num){
	int resultado = 0;
	while (num = num / 2, num > 0) resultado++;
	return resultado;
}


void imprimeCasilla(int numero){
	if (numero == 1) cout << setw(6) << " ";
	else cout << setw(6) << numero;
}


void carga(tTablero tablero, int &puntos, bool &ok){
	int aux;
	string nombre;
	cout << "Desea cargar una partida? [Pulse S/N] :";
	cin.sync();
	if (toupper(cin.get()) == 'S'){
		ifstream entrada;
		cout << "Introduce nombre de archivo:";
		cin >> nombre;
		entrada.open(nombre);
		if (entrada.is_open()){
			entrada >> aux; // Sacamos la Dimension
			if (aux == DIM){ // Comprobamos que sea correcta respecto a la indicada en el archivo
				/* Sacamos los datos de las tablas */
				for (int f = 0; f < DIM; f++){
					for (int c = 0; c < DIM; c++){
						entrada >> aux;
						tablero[f][c] = aux;
					}
				}
				entrada >> puntos;
				ok = true;
				cout << "Tablero cargado correctamente." << endl;
			}
			else cout << "Hay un error con la dimension del archivo" << endl;
		}
		else cout << nombre << " no existe,iniciando tablero" << endl;
		entrada.close();
	}
		if(!ok){
			cin.sync();
			do{ cout << "Pulse intro para continuar..."; } while (!cin.get());
			borrarTablero(tablero);
			inicializarCasilla(tablero);
			puntos = 0;
		}
}


tAccion leeAccion(){
tAccion accion;
cin.sync();
int key;
key = _getch();
if (key == 0xe0){
	key = _getch();
	switch (key){
	case tecla_abajo: accion = Abajo; break;
	case tecla_arriba: accion = Arriba; break;
	case tecla_der: accion = Derecha; break;
	case tecla_izq: accion = Izquierda; break;
	}
}
else if (key == tecla_esc) accion = Salir;
return accion;
}

void mueveFichas(tTablero tablero, tAccion accion, int &puntos){ 
	switch (accion){
	case (Arriba) : moverArriba(tablero,puntos); break;
	case (Abajo) : moverAbajo(tablero,puntos); break;
	case (Derecha) : moverDerecha(tablero,puntos); break;
	case (Izquierda) : moverIzquierda(tablero,puntos); break;
	}
}

void moverDerecha(tTablero tablero,int &puntos) { 
	int aux;
	for (int f = 0; f < DIM; f++){
		for (int c = DIM - 2; c + 1 > 0 ; c--){ // el -2 porque no vamos a mirar en la ultima posicion.
			if (tablero[f][c] != 1){ // si no es un 1 es un numero,hay que hecharlo a la derecha tantos huecos como podamos
				aux = c;
				while (aux < DIM - 1 && tablero[f][aux + 1] == 1) aux++; //posicionamos aux en la ultima columna con un uno
				if (c != aux){
					tablero[f][aux] = tablero[f][c];
					tablero[f][c] = 1;
				}
			}
		}
	}
	combinaFichas(tablero, Derecha, puntos);
	generarFicha(tablero, puntos);
}

void moverIzquierda(tTablero tablero, int &puntos){
	int aux;
	for (int f = 0; f < DIM; f++){
		for (int c = 1; c < DIM; c++){ // el 1 porque no vamos a mirar en la primera posicion.
			if (tablero[f][c] != 1){ // si no es un 1 es un numero,hay que hecharlo a la derecha tantos huecos como podamos
				aux = c;
				while (aux > 0 && tablero[f][aux - 1] == 1) aux--; //posicionamos aux en la ultima columna con un uno
				if (c != aux){
					tablero[f][aux] = tablero[f][c];
					tablero[f][c] = 1;
				}
			}
		}
	}
	combinaFichas(tablero, Izquierda, puntos);
	generarFicha(tablero, puntos);
}

void moverArriba(tTablero tablero, int &puntos){
	int aux;
	for (int c = 0; c < DIM; c++){
		for (int f = 1; f < DIM; f++){ // el 1 porque no vamos a mirar en la primera posicion.
			if (tablero[f][c] != 1){ // si no es un 1 es un numero,hay que hecharlo a la derecha tantos huecos como podamos
				aux = f;
				while (aux > 0 && tablero[aux - 1][c] == 1) aux--; //posicionamos aux en la ultima columna con un uno
				if (f != aux){
					tablero[aux][c] = tablero[f][c];
					tablero[f][c] = 1;
				}
			}
		}
	}
	combinaFichas(tablero, Arriba, puntos);
	generarFicha(tablero, puntos);
}

void moverAbajo(tTablero tablero, int &puntos){
	int aux;
	for (int c = 0; c < DIM; c++){
		for (int f = DIM - 2; f + 1 > 0; f--){ // el -2 porque no vamos a mirar en la ultima posicion.
			if (tablero[f][c] != 1){ // si no es un 1 es un numero,hay que hecharlo a la derecha tantos huecos como podamos
				aux = f;
				while (aux < DIM - 1 && tablero[aux + 1][c] == 1) aux++; //posicionamos aux en la ultima columna con un uno
				if (f != aux){
					tablero[aux][c] = tablero[f][c];
					tablero[f][c] = 1;
				}
			}
		}
	}
	combinaFichas(tablero, Abajo, puntos);
	generarFicha(tablero, puntos);
}

void generarFicha(tTablero tablero,int &puntos){
	int c = (rand() % DIM), f = (rand() % DIM);
	while (tablero[f][c] != 1){
		c = (rand() % DIM);
		f = (rand() % DIM);
	}
	tablero[f][c] = generarNumeroAleatorio();
	puntos = puntos + tablero[f][c];
}

int mayor(const tTablero tablero){
	int mayor = tablero[0][0];
	for (int c = 0; c < DIM; c++){
		for (int f = 0; f < DIM; f++){
			if (tablero[f][c] > mayor) mayor = tablero[f][c];
		}
	}
	return mayor;
}

bool lleno(const tTablero tablero){
	bool lleno = true;
	for (int c = 0; c < DIM; c++){
		for (int f = 0; f < DIM; f++){
			if (tablero[f][c] == 1) lleno = false;
		}
	}
	return lleno;
}

void combinaFichas(tTablero tablero, tAccion accion, int &puntos){
	switch (accion){
	case (Arriba) :combinaArriba(tablero, puntos); break;
	case (Abajo) : combinaAbajo(tablero, puntos); break;
	case (Derecha) : combinaDerecha(tablero, puntos); break;
	case (Izquierda) : combinaIzquierda(tablero, puntos); break;
	}
}

void combinaArriba(tTablero tablero, int &puntos){
	int aux;
	for (int c = 0; c < DIM; c++){
		for (int f = 0; f < DIM - 1; f++){
			if (tablero[f][c] != 1 && tablero[f][c] == tablero[f + 1][c]){ //Si el la posicion esta llena y el siguiente es igual que el actual
				aux = tablero[f][c] + tablero[f + 1][c]; // los sumo
				tablero[f][c] = aux;
				puntos = puntos + aux;
				for (int i = f + 1; i < DIM - 1; i++){ if (tablero[i][c] != 1) tablero[i][c] = tablero[i + 1][c]; } // apartir de la posicion actual + 1 
				tablero[DIM - 1][c] = 1; // al sumar combinamos dos cuadros dejamos una libre,la del final.
			}
			}
		}
}

void combinaAbajo(tTablero tablero, int &puntos){
	int aux;
	for (int c = 0; c < DIM; c++){
		for (int f = DIM - 1; f > 0; f--){
			if (tablero[f][c] != 1 && tablero[f][c] == tablero[f - 1][c]){ //Si el la posicion esta llena y el siguiente es igual que el actual
				aux = tablero[f][c] + tablero[f - 1][c]; // los sumo
				tablero[f][c] = aux;
				puntos = puntos + aux;
				for (int i = f - 1; i > 0; i--){ if (tablero[i][c] != 1) tablero[i][c] = tablero[i - 1][c]; } // apartir de la posicion actual + 1 
				tablero[0][c] = 1; // al sumar combinamos dos cuadros dejamos una libre,la del final.
			}
		}
	}
}

void combinaDerecha(tTablero tablero, int &puntos){
	int aux;
	for (int f = 0; f < DIM; f++){
		for (int c = DIM - 1; c > 0; c--){
			if (tablero[f][c] != 1 && tablero[f][c] == tablero[f][c - 1]){
				aux = tablero[f][c] + tablero[f][c - 1];
				tablero[f][c] = aux;
				puntos = puntos + aux;
				for (int i = c - 1; i > 0; i--){ if (tablero[f][i] != 1) tablero[f][i] = tablero[f][i - 1]; }
				tablero[f][0] = 1;
			}
		}
	}


}

void combinaIzquierda(tTablero tablero, int &puntos){
	int aux;
	for (int f = 0; f < DIM; f++){
		for (int c = 0; c < DIM - 1; c++){
			if (tablero[f][c] != 1 && tablero[f][c] == tablero[f][c + 1]){ //Si el la posicion esta llena y el siguiente es igual que el actual
				aux = tablero[f][c] + tablero[f][c + 1]; // los sumo
				tablero[f][c] = aux;
				puntos = puntos + aux;
				for (int i = c + 1; i < DIM - 1; i++){ if (tablero[f][i] != 1) tablero[f][i] = tablero[f][i + 1]; } // apartir de la posicion actual + 1 
				tablero[f][DIM - 1] = 1; // al sumar combinamos dos cuadros dejamos una libre,la del final.
			}
		}
	}
}
