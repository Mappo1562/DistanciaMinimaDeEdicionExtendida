#include "../costos.cpp"
using namespace std;

// cd /mnt/c/Users/admin/OneDrive/'archivos para estudiar'/2024-2/algoco/tarea2-3

/*
para compílar hay que estar en la carpeta tarea 2-3
y escribir el siguiente comando
    g++ -o out fuerzabruta/distanciadeedicion.cpp -Wall
y para correr
    ./out
*/

string palabra, objetivo;
int c=0;


long getMemoryUsage() {
    ifstream file("/proc/self/status");
    string line;
    while (getline(file, line)) {
        if (line.rfind("VmRSS:", 0) == 0) {
            istringstream iss(line);
            string label;
            long memory;
            iss >> label >> memory;
            return memory; 
        }
    }
    return 0;
}


int set(){
    ifstream data("entrada.txt");
    if (!data){
        cout<<"No se pudo abrir el archivo.\n";
        return 1;
    }
    data>>palabra;
    data>>objetivo;
    data.close();
    return 0;
}




int distanciaEdicion(int i, int j) {
    // condicion de termino
    if (i<0 && j<0)
        return 0;
    // palabra vacía
    if (i < 0) {
        return costo_ins(objetivo[j]) + distanciaEdicion(i,j-1);
    }
    // objetivo vacío
    if (j < 0) {
        return costo_del(palabra[i]) + distanciaEdicion(i-1,j);
    }
    // caracteres iguales
    if (palabra[i] == objetivo[j]) {
        return distanciaEdicion(i - 1, j - 1);
    }
    
    // operaciones de edición
    int eliminar = distanciaEdicion(i - 1, j) + costo_del(palabra[i]);
    int insertar = distanciaEdicion(i, j - 1) + costo_ins(objetivo[j]);
    int sustituir = distanciaEdicion(i - 1, j - 1) + costo_sub(palabra[i], objetivo[j]);
    
    int transponer = INT_MAX;
    if (i > 0 && j > 0 && palabra[i] == objetivo[j - 1] && palabra[i - 1] == objetivo[j]) {
        transponer = distanciaEdicion(i - 2, j - 2) + costo_trans(palabra[i], palabra[i - 1]);
    }


    return min({eliminar, insertar, sustituir, transponer});
}


int main(){
    if (set()){
        return 1;
    }
    if (GET_COSTOS()){
        return 1;
    }
    cout<<"#########################################################################\n";
    cout<<"\n    Distancia minima de edicion extendida con enfoque de fuerza bruta \n\n";
    cout<<" palabra: "<<palabra<<"\n objetivo: "<<objetivo<<"\n\n";

    // calculo distancia
    auto inicio = chrono::high_resolution_clock::now();
    int distancia = distanciaEdicion(palabra.size() - 1, objetivo.size() - 1);
    auto fin = chrono::high_resolution_clock::now();

    chrono::duration<double> duracion = fin - inicio;

    cout << " La distancia de edicion entre '" << palabra << "' y '" << objetivo << "' es: " << distancia << "\n";
    cout << " Tiempo de ejecución: " << duracion.count() << " segundos.\n";
    cout << " Uso de memoria: " << getMemoryUsage() << " KB.\n";
    cout<<"\n#########################################################################\n";
    return 0;
}