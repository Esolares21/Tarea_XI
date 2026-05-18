# 🚀 Proyecto: Tablas Hash & Mapas de Datos (Tarea XI)

¡Hola! Bienvenido. Soy **Erix Alejandro Solares Flores** (Carné: **9941-20-23978**), estudiante de Ingeniería en Sistemas en la Universidad Mariano Gálvez (UMG). 

Este proyecto fue desarrollado para el curso de **Programación III** como parte del avance de nuestro proyecto final. El objetivo principal es procesar la carga masiva de datos académicos usando dispersión y resolución de colisiones en dos lenguajes distintos.

---

## 📂 Estructura del Repositorio

Cumpliendo con la guía de la tarea, el repositorio se organiza así:

```text
tarea-hash-csv/
├── cpp-hash/
│   ├── main.cpp            # Tabla Hash manual desde cero
│   └── estudiantes.csv     # Archivo de datos de los estudiantes
├── java-hashmap/
│   ├── Main.java           # Menú principal en Java
│   ├── Estudiante.java     # Clase de datos (POJO)
│   └── estudiantes.csv     # Mismo archivo de datos para Java
└── evidencias/
    └── evidencia.pdf       # Capturas de pantalla obligatorias
```
## 📊 Formato del CSV (estudiantes.csv)
Ambos programas leen un archivo separado por comas con la estructura:

student_id, full_name, career, semester_gua, skill_score

### 💻 1. Implementación en C++ (cpp-hash)
Aquí construimos una Tabla Hash completamente manual sin usar herramientas de la STL (como std::unordered_map o std::list).

Estructura: Arreglo fijo de punteros (SIZE = 15).

Colisiones: Resueltas mediante Separate Chaining (encadenamiento) con listas enlazadas dinámicas creadas a mano (Nodo*).

Operaciones: Inserción (valida duplicados), búsqueda, eliminación y cálculo del Factor de Carga.

## 📦 Para ejecutar en CLion: Abre la carpeta, coloca el archivo estudiantes.csv en la ruta de ejecución (cmake-build-debug o por CMakeLists) y dale al botón de Run.

### ☕ 2. Implementación en Java (java-hashmap)
En Java aprovechamos las herramientas nativas del lenguaje para ver el contraste de trabajar con un framework ya optimizado.

Estructura: Uso directo de la colección nativa HashMap<Integer, Estudiante>.

Abstracción: No manejamos punteros ni índices matemáticos a mano; Java gestiona el almacenamiento de forma interna y automática.

Operaciones: Lectura con BufferedReader y validación de claves únicas con .containsKey().

## 📦 Para ejecutar: Abre el proyecto en tu IDE preferido (IntelliJ, Eclipse, etc.) y ejecuta la clase Main.java.

### 🧠 Aprendizaje: Estructura Manual (C++) vs. Nativa (Java)
Punteros vs. Caja Negra: En C++ aprendí exactamente cómo se conectan los nodos en memoria y el peligro de romper un enlace (Segmentation Fault). En Java todo ocurre dentro de una "caja negra" segura donde solo llamamos a métodos como .put() o .get().

Control de Memoria: En C++ tuvimos que programar un destructor manual (delete) para limpiar la memoria. En Java, el Garbage Collector se encarga de todo de manera automática.

Eficiencia: Desarrollar en Java requirió menos código y fue mucho más rápido. Sin embargo, armar la estructura en C++ fue lo que realmente me ayudó a entender la matemática y la lógica algorítmica detrás de las tablas hash.
