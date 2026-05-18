#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Estudiante {
    int id;
    string nombre;
    string carrera;
    int semestre;
    float nota;
};

struct Nodo {
    Estudiante estudiante;
    Nodo* siguiente;
};

class HashTable {
private:
    static const int SIZE = 15;
    Nodo* tabla[SIZE];
    int totalElementos;
    int totalColisiones;

    int funcionHash(int id) const {
        return id % SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < SIZE; i++) {
            tabla[i] = nullptr;
        }
        totalElementos = 0;
        totalColisiones = 0;
    }

    bool insertar(int id, const string& nombre, const string& carrera, int semestre, float nota) {
        int indice = funcionHash(id);

        if (buscar(id) != nullptr) {
            return false;
        }

        Nodo* nuevo = new Nodo;
        nuevo->estudiante.id = id;
        nuevo->estudiante.nombre = nombre;
        nuevo->estudiante.carrera = carrera;
        nuevo->estudiante.semestre = semestre;
        nuevo->estudiante.nota = nota;

        nuevo->siguiente = nullptr;

        if (tabla[indice] != nullptr) {
            totalColisiones++;
        }

        nuevo->siguiente = tabla[indice];
        tabla[indice] = nuevo;

        totalElementos++;
        return true;
    }

    Estudiante* buscar(int id) const {
        int indice = funcionHash(id);
        Nodo* actual = tabla[indice];

        while (actual != nullptr) {
            if (actual->estudiante.id == id) {
                return const_cast<Estudiante*>(&actual->estudiante);
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    bool eliminar(int id) {
        int indice = funcionHash(id);
        Nodo* actual = tabla[indice];
        Nodo* anterior = nullptr;

        while (actual != nullptr) {
            if (actual->estudiante.id == id) {
                if (anterior == nullptr) {
                    tabla[indice] = actual->siguiente;
                } else {
                    anterior->siguiente = actual->siguiente;
                }

                delete actual;
                totalElementos--;
                return true;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        return false;
    }

    void cargarDesdeCSV(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
            cout << "Asegurese de colocarlo en el directorio de ejecucion correcto.\n";
            return;
        }

        string linea;
        getline(archivo, linea);

        int cargadosContador = 0;

        while (getline(archivo, linea)) {
            if (linea.empty()) continue;

            stringstream ss(linea);
            string s_id, nombre, carrera, s_semestre, s_nota;

            getline(ss, s_id, ',');
            getline(ss, nombre, ',');
            getline(ss, carrera, ',');
            getline(ss, s_semestre, ',');
            getline(ss, s_nota, ',');

            try {
                int id = stoi(s_id);
                int semestre = stoi(s_semestre);
                float nota = stof(s_nota);

                if (insertar(id, nombre, carrera, semestre, nota)) {
                    cargadosContador++;
                } else {
                    cout << "Estudiante con ID " << id << " omitido (Duplicado).\n";
                }
            } catch (...) {
                cout << "Error al procesar la linea: " << linea << " (Datos invalidos).\n";
            }
        }
        archivo.close();
        cout << "\n>>> Carga masiva finalizada. Estudiantes agregados: " << cargadosContador << " <<<\n";
    }

    void mostrarTabla() const {
        cout << "\n--- CONTENIDO DE LA HASH TABLE POR BUCKET ---\n";
        for (int i = 0; i < SIZE; i++) {
            cout << "Bucket [" << i << "]: ";
            Nodo* actual = tabla[i];

            if (actual == nullptr) {
                cout << "vacio\n";
                continue;
            }

            while (actual != nullptr) {
                cout << "[" << actual->estudiante.id << " | " << actual->estudiante.nombre << "] -> ";
                actual = actual->siguiente;
            }
            cout << "NULL\n";
        }
    }

    void mostrarEstadisticas() const {
        cout << "\n--- ESTADISTICAS DE LA TABLA HASH ---\n";
        cout << "Total de estudiantes cargados: " << totalElementos << endl;
        cout << "Total de buckets definidos: " << SIZE << endl;
        cout << "Total de colisiones generadas: " << totalColisiones << endl;
        cout << "Factor de carga (Load Factor): " << calcularFactorCarga() << endl;
    }

    float calcularFactorCarga() const {
        return static_cast<float>(totalElementos) / SIZE;
    }

    ~HashTable() {
        for (int i = 0; i < SIZE; i++) {
            Nodo* actual = tabla[i];
            while (actual != nullptr) {
                Nodo* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
        }
    }
};

int main() {
    cout << "====================================================\n";
    cout << "ESTUDIANTE: Erix Alejandro Solares Flores\n";
    cout << "CARNE: 9941-20-23978\n";
    cout << "====================================================\n";

    HashTable hash;
    int opcion;

    cout << "Cargando estudiantes desde 'estudiantes.csv'...\n";
    hash.cargarDesdeCSV("estudiantes.csv");

    do {
        cout << "\n========== MENU GENERAL (C++) ==========\n";
        cout << "1. Buscar estudiante por ID\n";
        cout << "2. Eliminar estudiante por ID\n";
        cout << "3. Mostrar tabla completa (por Buckets)\n";
        cout << "4. Mostrar Estadisticas y Factor de Carga\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            int id;
            cout << "Ingrese ID del estudiante a buscar: ";
            cin >> id;

            Estudiante* encontrado = hash.buscar(id);
            if (encontrado != nullptr) {
                cout << "\n--- ESTUDIANTE ENCONTRADO ---\n";
                cout << "ID: " << encontrado->id << "\nNombre: " << encontrado->nombre
                     << "\nCarrera: " << encontrado->carrera << "\nSemestre: " << encontrado->semestre
                     << "\nNota de Habilidad: " << encontrado->nota << endl;
            } else {
                cout << "Error: Estudiante no encontrado.\n";
            }
        }
        else if (opcion == 2) {
            int id;
            cout << "Ingrese ID del estudiante a eliminar: ";
            cin >> id;

            if (hash.eliminar(id)) {
                cout << "Estudiante con ID " << id << " eliminado correctamente.\n";
            } else {
                cout << "Error: No se encontro ningun estudiante con ese ID.\n";
            }
        }
        else if (opcion == 3) {
            hash.mostrarTabla();
        }
        else if (opcion == 4) {
            hash.mostrarEstadisticas();
        }
        else if (opcion == 5) {
            cout << "Saliendo del programa C++...\n";
        }
        else {
            cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 5);

    return 0;
}