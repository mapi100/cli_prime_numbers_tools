#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Funcion que determina si un numero es primo
bool esPrimo(long long int numero) {
    if (numero <= 1) return false;

    for (long long int divisor = 2; divisor <= sqrt(numero); ++divisor) {
        if (numero % divisor == 0) return false;
    }
    return true;
}

// Imprime todos los numeros primos hasta un limite dado usando la Criba de Eratostenes
void imprimirPrimosHasta(int limite) {
    vector<bool> esPrimo(limite + 1, true);

    esPrimo[0] = esPrimo[1] = false;

    for (int p = 2; p * p <= limite; ++p) {
        if (esPrimo[p]) {
            for (int i = p * p; i <= limite; i += p) {
                esPrimo[i] = false;
            }
        }
    }

    cout << "Numeros primos hasta " << limite << ":\n";
    for (int p = 2; p <= limite; ++p) {
        if (esPrimo[p]) cout << p << " ";
    }
    cout << "\n";
}

// Encuentra el numero primo mas cercano a un numero dado
void encontrarPrimoCercano(long long int numero) {
    if (esPrimo(numero)) {
        cout << "El numero " << numero << " ya es primo.\n";
        return;
    }

    long long int menor = numero - 1;
    long long int mayor = numero + 1;

    while (!esPrimo(menor)) --menor;
    while (!esPrimo(mayor)) ++mayor;

    cout << "El primo mas cercano a " << numero << " es: ";
    if (numero - menor <= mayor - numero)
        cout << menor;
    else
        cout << mayor;

    cout << "\n";
}

// Encuentra todos los primos gemelos hasta un cierto limite
void encontrarPrimosGemelosHasta(int limite) {
    cout << "Primos gemelos hasta " << limite << ":\n";
    for (int p = 2; p <= limite - 2; ++p) {
        if (esPrimo(p) && esPrimo(p + 2)) {
            cout << "(" << p << ", " << p + 2 << ") ";
        }
    }
    cout << "\n";
}

// Funcion principal con menu interactivo
int main() {
    int opcion;

    cout << "Elige una opcion:\n";
    cout << "1. Imprimir todos los primos hasta un limite.\n";
    cout << "2. Encontrar el primo mas cercano a un numero.\n";
    cout << "3. Encontrar todos los primos gemelos hasta un limite.\n";
    cout << "Opcion: ";
    cin >> opcion;

    switch (opcion) {
        case 1: {
            int limite;
            cout << "Ingresa el limite: ";
            cin >> limite;
            imprimirPrimosHasta(limite);
            break;
        }
        case 2: {
            long long int numero;
            cout << "Ingresa un numero: ";
            cin >> numero;
            encontrarPrimoCercano(numero);
            break;
        }
        case 3: {
            int limite;
            cout << "Ingresa el limite: ";
            cin >> limite;
            encontrarPrimosGemelosHasta(limite);
            break;
        }
        default:
            cout << "Opcion invalida!\n";
    }

    return 0;
}
