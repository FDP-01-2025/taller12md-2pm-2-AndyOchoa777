#include <iostream>
#include <fstream>
using namespace std;

struct Estudiante {
    string nombre;
    string carnet;
    int edad;
};

// Función para agregar estudiante (CREATE)
void agregarEstudiante() {
    Estudiante e;
    cout << "Nombre (sin espacios): ";
    cin >> e.nombre;
    cout << "Carnet: ";
    cin >> e.carnet;
    cout << "Edad: ";
    cin >> e.edad;

    ofstream archivo("estudiantes.txt", ios::app);
    if (archivo.is_open()) {
        archivo << e.nombre << " " << e.carnet << " " << e.edad << endl;
        archivo.close();
        cout << "Estudiante agregado correctamente.\n";
    } else {
        cout << "Error al abrir el archivo.\n";
    }
}

// Función para mostrar estudiantes (READ)
void mostrarEstudiantes() {
    ifstream archivo("estudiantes.txt");
    Estudiante e;

    if (archivo.is_open()) {
        cout << "\n--- Lista de Estudiantes ---\n";
        while (archivo >> e.nombre >> e.carnet >> e.edad) {
            cout << "Nombre: " << e.nombre 
                 << ", Carnet: " << e.carnet
                 << ", Edad: " << e.edad << endl;
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo.\n";
    }
}

// -----------------------------
// 👇 TU TAREA: Completa esta función (UPDATE)
void modificarEstudiante() {
    // Debes permitir actualizar nombre, carnet y/o edad
    // de un estudiante identificado por su carnet.
    // Puedes usar o no manejo de archivos.
    // Si lo implementas con archivos correctamente, obtendrás **2 puntos extra**.

    //Se declara las variables y parametros que ocuparmeos en la funcion.
    ifstream archivo("estudiantes.txt");
    ofstream temp("temp.txt");
    Estudiante e;
    string buscado;
    bool reemplazo = false;

    //Solicitamos el carnet del estudiante al cual queremos actualizar la informacion.
    cout << "Ingrese carnet del estudiante a reemplazar: ";
    cin >> buscado;

    //comprobamos que se abra un archivo estudiantes y uno temp
    if (archivo.is_open() && temp.is_open()) {
        //Creamos un bucle que se ira repitiendo mientras existan datos en el archivo.
        //A su vez en cada ciclo se ira guardando informacion del archivo estudiantes.txt
        //en la variable struct e.
        while (archivo >> e.nombre >> e.carnet >> e.edad) {
            //Buscamos si hay algun carnet que coincida con el que ingreso el usuario
            if (e.carnet == buscado) {

                //Si encuentra uno haremos true la variable reemplazo.
                //Tambien solicitaremos al usuario los datos nuevos que ingresara del estudiante.
                //Por ultimo subimos la nueva informacion al archivo temp.
                reemplazo = true;
                cout<<"Ingresa el carnet del estudiante que quieres actualizar: ";
                cin>>e.carnet;
                cout<<endl;
                cout<<"Ingresa el nombre del estudiante actualizado: ";
                cin>>e.nombre;
                cout<<endl;
                cout<<"Ingresa la edad del estudiante actualizado: ";
                cin>>e.edad;
                cout<<endl;
                 temp << e.nombre << " " << e.carnet << " " << e.edad << endl;
            } else {
                //Si no coincide el carnet con el carnet ingresado por el usuario simplemente se volvera a subir
                temp << e.nombre << " " << e.carnet << " " << e.edad << endl;
            }
        }

        //Una vez termina el ciclo while cerramos ambos archivos.
        archivo.close();
        temp.close();

        //Despues borramos el anterior archivo estudiantes.txt
        //El cual contiene la lista de estudiantes sin actualizar
        remove("estudiantes.txt");

        //Renombramos el archivo temp.txt que es donde guardamos la lista de estudiantes
        //con la informacion del estudiante actualizada a estudiantes.txt
        rename("temp.txt", "estudiantes.txt");

        //Despues con la variable de reemplazo verificamos si se logro
        //Hacer algun cambio en la lista de estudiantes.
        if (reemplazo)
            cout << "Se actualizo la informacion del estudiante correctamente.\n";
        else
        //Caso que no se haya encontrado el carnet se le informa al usuario de esto.
            cout << "Carnet no encontrado.\n";
    } else {
        //Si no se abren ambos archivos que se encuentran en el if
        //se le informara al usario que hubo un error.
        cout << "Error abriendo los archivos.\n";
    }
}
// -----------------------------

// Función para eliminar estudiante (DELETE)
void eliminarEstudiante() {
    ifstream archivo("estudiantes.txt");
    ofstream temp("temp.txt");
    Estudiante e;
    string buscado;
    bool eliminado = false;

    cout << "Ingrese carnet a eliminar: ";
    cin >> buscado;

    if (archivo.is_open() && temp.is_open()) {
        while (archivo >> e.nombre >> e.carnet >> e.edad) {
            if (e.carnet == buscado) {
                eliminado = true;               // No se copia: se “borra”
            } else {
                temp << e.nombre << " " << e.carnet << " " << e.edad << endl;
            }
        }
        archivo.close();
        temp.close();
        remove("estudiantes.txt");
        rename("temp.txt", "estudiantes.txt");

        if (eliminado)
            cout << "Estudiante eliminado correctamente.\n";
        else
            cout << "Carnet no encontrado.\n";
    } else {
        cout << "Error abriendo los archivos.\n";
    }
}

// Menú principal
int main() {
    int opcion;
    do {
        cout << "\n=== CRUD de Estudiantes ===\n";
        cout << "1. Agregar estudiante\n";
        cout << "2. Mostrar todos\n";
        cout << "3. Modificar estudiante\n";
        cout << "4. Eliminar estudiante\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agregarEstudiante(); break;
            case 2: mostrarEstudiantes(); break;
            case 3: modificarEstudiante(); break;  // 👉 Completa aquí
            case 4: eliminarEstudiante(); break;
            case 5: cout << "Saliendo...\n"; break;
            default: cout << "Opción inválida.\n";
        }

    } while (opcion != 5);

    return 0;
}