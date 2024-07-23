#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <iomanip>



using namespace std;

HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
int getch();
// Variables globales
int cantidadtotal = 0;
int opcion;
int candidato;
const int MAX_CANDIDATOS = 10;
int numCandidatos = 0;

// Estructura para almacenar datos de candidatos
struct Candidato {
    int id; // Identificador único del candidato
    char nombre[50];
    int votos;
};


Candidato candidatos[MAX_CANDIDATOS];


// Estructura para almacenar datos de votantes
struct Votante {
    char nombre[50];
    // Puedes agregar más campos según sea necesario
};

const int MAX_VOTANTES = 100; // Define el máximo de votantes que puedes manejar
Votante votantes[MAX_VOTANTES]; // Arreglo para almacenar los votantes
int numVotantes = 0; // Contador para el número actual de votantes


// Prototipos de funciones
void menu();
void IngresarDatosVotante();
void Graficos();
void gotoxy(int x, int y);
void cuadro(int x1, int y1, int x2, int y2);
void IngresarDatos();

// Procedimiento para posicionar el cursor en la consola
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Procedimiento para dibujar un cuadro en la consola
void cuadro(int x1, int y1, int x2, int y2) {
    int i;
    for (i = x1; i <= x2; i++) {
        gotoxy(i, y1); printf("%c", 205);
        gotoxy(i, y2); printf("%c", 205);
    }
    for (i = y1; i <= y2; i++) {
        gotoxy(x1, i); printf("%c", 186);
        gotoxy(x2, i); printf("%c", 186);
    }
    gotoxy(x1, y1); printf("%c", 201);
    gotoxy(x1, y2); printf("%c", 200);
    gotoxy(x2, y1); printf("%c", 187);
    gotoxy(x2, y2); printf("%c", 188);
}

// Función para ingresar datos de un nuevo candidato
void IngresarDatos() {
    system("cls");
    cuadro(10, 5, 70, 15);
    SetConsoleTextAttribute(hConsoleHandle, 15);
    gotoxy(20, 8); cout << "Ingresar Datos del Nuevo Candidato" << endl;
    
    if (numCandidatos < MAX_CANDIDATOS) {
        Candidato nuevoCandidato;
        cout << "Nombre del candidato: ";
        cin >> nuevoCandidato.nombre;
        nuevoCandidato.votos = 0; // Inicialmente no tiene votos
        
        candidatos[numCandidatos++] = nuevoCandidato;
        
        cout << "Candidato agregado exitosamente.\n";
    } else {
        cout << "No se pueden agregar más candidatos. Límite alcanzado.\n";
    }
    
    cout << "\nPresione cualquier tecla para continuar...";
    std::cin.get(); // Espera a que el usuario presione una tecla
}
void IngresarDatosVotante() {
    system("cls");
    cuadro(10, 5, 70, 15);
    SetConsoleTextAttribute(hConsoleHandle, 15);
    gotoxy(20, 8); cout << "Ingresar Datos del Nuevo Votante" << endl;
    
    if (numVotantes < MAX_VOTANTES) {
        Votante nuevoVotante;
        cout << "Nombre del votante: ";
        cin.ignore(); // Para limpiar el buffer de entrada
        cin.getline(nuevoVotante.nombre, 50); // Lee el nombre del votante
        
        // Aquí puedes agregar más campos si los necesitas
        
        votantes[numVotantes++] = nuevoVotante;
        
        cout << "Votante agregado exitosamente.\n";
    } else {
        cout << "No se pueden agregar más votantes. Límite alcanzado.\n";
    }
    
    cout << "\nPresione cualquier tecla para continuar...";
    std::cin.get(); // Espera a que el usuario presione una tecla
}

// Función principal del menú
void menu() {
    char opc, conti;
    
    do {
        system("cls");
        cuadro(16, 2, 67, 6); // Primer cuadro de arriba hacia abajo
        cuadro(8, 8, 72, 22); // Cuadro grande
        cuadro(8, 23, 72, 25); // Cuadro de abajo opcion es
        cuadro(56, 19, 68, 21); // Cuadro pequeño salir

        SetConsoleTextAttribute(hConsoleHandle, 8);
        gotoxy(22, 4); printf(" UNIVERSIDAD TECNOLOGICA COSTARRICENSE ");
        SetConsoleTextAttribute(hConsoleHandle, 10);
        gotoxy(15, 9); printf("----- MENU PRINCIPAL DEL SISTEMA DE VOTACIONES-----");
        SetConsoleTextAttribute(hConsoleHandle, 15);
        gotoxy(15, 10); printf("1-  INGRESAR DATOS DEL CANDIDATO ");
        gotoxy(15, 12); printf("2-  INGRESAR DATOS DEL VOTANTE ");
        gotoxy(15, 14); printf("3-  VOTOS");
        gotoxy(15, 16); printf("4-  GRAFICOS");
        gotoxy(57, 20); printf("<5- SALIR>");
        
        SetConsoleTextAttribute(hConsoleHandle, 5);
        gotoxy(18, 24); printf("* Su opcion es: ");
        opc = std::cin.get();

        switch (opc) {
            case '1': IngresarDatos(); break;
            case '2': IngresarDatosVotante(); break; // Agrega la opción para ingresar datos de votante
            case '3': 
			system("cls");
    cuadro(10, 5, 70, 15); // Cuadro para los gráficos
    SetConsoleTextAttribute(hConsoleHandle, 10);
    gotoxy(26, 7); cout << "Lista de Candidatos" << endl; // Ajusta la posición del título

    for (int i = 0; i < numCandidatos; ++i) {
        gotoxy(20, 9 + i); // Ajusta la posición de cada línea de candidato
        cout << "[" << candidatos[i].id << "] " << candidatos[i].nombre << endl;
    }

    cout << "Ingrese el número del candidato al que desea votar: "<< endl;
    cin >> candidato;

    // Verificar si el candidato seleccionado es válido
    if (candidato >= 1 && candidato <= numCandidatos) {
        candidatos[candidato - 1].votos++; // Incrementar los votos del candidato seleccionado
        cout << "Voto registrado exitosamente.\n";
    } else {
        cout << "Opción inválida. Voto no registrado.\n";
    }

    cout << "\nPresione cualquier tecla para continuar...";
    std::cin.get(); // Espera a que el usuario presione una tecla
    std::cin.get(); // Espera a que el usuario presione una tecla
    break;
            case '4': Graficos(); break;

            case '5':
                system("cls");
                gotoxy(20, 10); printf("Estas seguro Que Deseas Salir del Sistema");
                SetConsoleTextAttribute(hConsoleHandle, 2);
                gotoxy(20, 15); printf("Desea Continuar S/N");
                conti = std::cin.get();
                if (conti == 'N' || conti == 'n') menu();
                else if (conti == 'S' || conti == 's') break;
        }
    } while (opc != '5');
}

// Función para mostrar gráficos de votación
void Graficos() {
    system("cls"); // Limpiar la consola antes de imprimir los gráficos
    
    cuadro(10, 5, 70, 15); // Dibuja el cuadro para los gráficos
    SetConsoleTextAttribute(hConsoleHandle, 10); // Establece el color de texto para los gráficos
    
    gotoxy(26, 7); cout << "Resultados de la Votación" << endl; // Título de los resultados

    // Imprimir los gráficos de cada candidato
    for (int i = 0; i < numCandidatos; ++i) {
        gotoxy(20, 9 + i); // Posición del nombre del candidato
        cout << setw(15) << left << candidatos[i].nombre << ": ";
        
        // Imprimir los votos utilizando caracteres '*'
        for (int j = 0; j < candidatos[i].votos; ++j) {
            cout << "*"; // Utilizar '*' para representar votos individuales
        }
        cout << endl;
    }

    // Mensaje de continuación
    gotoxy(20, 12 + numCandidatos); // Posición para el mensaje de continuar
    cout << "\nPresione cualquier tecla para continuar...";
    std::cin.get(); // Espera a que el usuario presione una tecla
}


// Función principal
int main() {
    menu();
    return 0;
}
