import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        System.out.println("====================================================");
        System.out.println("ESTUDIANTE: Erix Alejandro Solares Flores");
        System.out.println("CARNÉ: 9941-20-23978");
        System.out.println("====================================================\n");

        HashMap<Integer, Estudiante> mapaEstudiantes = new HashMap<>();
        Scanner scanner = new Scanner(System.in);

        String archivoCSV = "estudiantes.csv";
        System.out.println("Cargando estudiantes desde '" + archivoCSV + "'...");

        try (BufferedReader br = new BufferedReader(new FileReader(archivoCSV))) {
            String linea;
            br.readLine();

            int cargadosExitosamente = 0;

            while ((linea = br.readLine()) != null) {
                if (linea.trim().isEmpty()) continue;

                String[] datos = linea.split(",");

                if (datos.length >= 5) {
                    try {
                        int id = Integer.parseInt(datos[0].trim());
                        String nombre = datos[1].trim();
                        String carrera = datos[2].trim();
                        int semestre = Integer.parseInt(datos[3].trim());
                        double nota = Double.parseDouble(datos[4].trim());

                        if (!mapaEstudiantes.containsKey(id)) {
                            Estudiante est = new Estudiante(id, nombre, carrera, semestre, nota);
                            mapaEstudiantes.put(id, est);
                            cargadosExitosamente++;
                        } else {
                            System.out.println("Estudiante con ID " + id + " omitido (Ya existe en HashMap).");
                        }
                    } catch (NumberFormatException e) {
                        System.out.println("Error de formato en linea: " + linea);
                    }
                }
            }
            System.out.println(">>> Carga masiva en Java finalizada. Registros cargados: " + cargadosExitosamente + " <<<\n");

        } catch (IOException e) {
            System.out.println("Error al leer el archivo CSV: " + e.getMessage());
            System.out.println("Asegurese de colocar 'estudiantes.csv' en la raiz asignada de ejecucion.");
        }

        int opcion;
        do {
            System.out.println("\n========== MENU GENERAL (JAVA HASHMAP) ==========");
            System.out.println("1. Buscar estudiante por ID");
            System.out.println("2. Eliminar estudiante por ID");
            System.out.println("3. Mostrar todos los estudiantes en el HashMap");
            System.out.println("4. Mostrar total de estudiantes cargados");
            System.out.println("5. Salir");
            System.out.print("Seleccione una opcion: ");
            opcion = scanner.nextInt();

            switch (opcion) {
                case 1:
                    System.out.print("Ingrese ID a buscar: ");
                    int idBuscar = scanner.nextInt();
                    if (mapaEstudiantes.containsKey(idBuscar)) {
                        System.out.println("\n=== ESTUDIANTE ENCONTRADO ===");
                        System.out.println(mapaEstudiantes.get(idBuscar));
                    } else {
                        System.out.println("Error: Estudiante no registrado.");
                    }
                    break;

                case 2:
                    System.out.print("Ingrese ID a eliminar: ");
                    int idEliminar = scanner.nextInt();
                    if (mapaEstudiantes.containsKey(idEliminar)) {
                        mapaEstudiantes.remove(idEliminar);
                        System.out.println("Estudiante con ID " + idEliminar + " eliminado correctamente del HashMap.");
                    } else {
                        System.out.println("Error: No existe estudiante con ese ID.");
                    }
                    break;

                case 3:
                    System.out.println("\n=== CONTENIDO ACTUAL DEL HASHMAP ===");
                    if (mapaEstudiantes.isEmpty()) {
                        System.out.println("El mapa esta vacio.");
                    } else {
                        for (Integer key : mapaEstudiantes.keySet()) {
                            System.out.println("--------------------------------");
                            System.out.println("Clave (Key): " + key);
                            System.out.println(mapaEstudiantes.get(key));
                        }
                    }
                    break;

                case 4:
                    System.out.println("\n=== ESTADISTICAS HASHMAP ===");
                    System.out.println("Total de estudiantes almacenados: " + mapaEstudiantes.size());
                    break;

                case 5:
                    System.out.println("Saliendo del programa Java...");
                    break;

                default:
                    System.out.println("Opcion no valida.");
            }
        } while (opcion != 5);

        scanner.close();
    }
}
