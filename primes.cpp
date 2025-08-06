#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

// Declaraciones adelantadas
bool esPrimo(long long int numero);
void imprimirPrimosHasta(int limite);
void encontrarPrimoCercano(long long int numero);
void encontrarPrimosGemelosHasta(int limite);
void exportarPrimosComoEspiral(int limite, const string& archivo);
void generarScriptPython(const string& archivoPython, const string& archivoDatos);

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

// Exporta los primos como coordenadas polares (r = n, theta = n)
void exportarPrimosComoEspiral(int limite, const string& archivo) {
    ofstream salida(archivo);
    if (!salida.is_open()) {
        cout << "No se pudo abrir el archivo para escritura.\n";
        return;
    }

    for (int n = 2; n <= limite; ++n) {
        if (esPrimo(n)) {
            double r = n;
            double theta = n;
            salida << r << " " << theta << "\n";
        }
    }

    salida.close();
    cout << "Archivo '" << archivo << "' generado con coordenadas polares de primos.\n";
}

// Genera un script Python para graficar los puntos
void generarScriptPython(const string& archivoPython, const string& archivoDatos) {
    ofstream py(archivoPython);
    if (!py.is_open()) {
        cout << "No se pudo crear el archivo de Python.\n";
        return;
    }

    py << "import numpy as np\n";
    py << "import matplotlib.pyplot as plt\n\n";
    py << "r, theta = np.loadtxt('" << archivoDatos << "', unpack=True)\n";
    py << "x = r * np.cos(theta)\n";
    py << "y = r * np.sin(theta)\n\n";
    py << "plt.figure(figsize=(6,6))\n";
    py << "plt.scatter(x, y, s=1, c='blue')\n";
    py << "plt.axis('equal')\n";
    py << "plt.title('Espiral de primos')\n";
    py << "plt.show()\n";

    py.close();
    cout << "Script '" << archivoPython << "' generado exitosamente.\n";
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
            exportarPrimosComoEspiral(limite, "primos_polares.txt");
            generarScriptPython("graficar_primos.py", "primos_polares.txt");
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
