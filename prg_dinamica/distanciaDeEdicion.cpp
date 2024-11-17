#include "../costos.cpp"
using namespace std;


//  cd /mnt/c/Users/admin/OneDrive/'archivos para estudiar'/2024-2/algoco/tarea2-3

/*
para compílar hay que estar en la carpeta tarea 2-3
y escribir el siguiente comando
    g++ -o out prg_dinamica/distanciadeedicion.cpp -Wall
y para correr
    ./out
*/

string palabra,objetivo;
vector<vector<int>> tabla;



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

    if (tabla[i][j] != -1) 
        return tabla[i][j];
    
    if(i==0){
        tabla[i][j] = distanciaEdicion(0,j-1) + costo_ins(objetivo[j]);
        return tabla[i][j];
    }
    if(j==0){
        tabla[i][j] = distanciaEdicion(i-1,j) + costo_del(palabra[i]);
        return tabla[i][j];
    }

    if (palabra[i] == objetivo[j]) {
        tabla[i][j] = distanciaEdicion(i - 1, j - 1);
        return tabla[i][j];
    } 


    int eliminar = distanciaEdicion(i - 1, j) + costo_del(palabra[i]);
    int insertar = distanciaEdicion(i, j - 1) + costo_ins(objetivo[j]); 
    int sustituir = distanciaEdicion( i - 1, j - 1) + costo_sub(palabra[i],objetivo[j]);
    int transponer = INT_MAX;  
    if (i > 1 && j > 1 && palabra[i] == objetivo[j - 1] && palabra[i - 1] == objetivo[j]) {
        transponer = distanciaEdicion(i - 2, j - 2) + costo_trans(palabra[i],palabra[i-1]);
    }

    tabla[i][j] = min({eliminar, insertar, sustituir, transponer});
    
    return tabla[i][j];
}


void helpDistanciaEdicion(){
    palabra="-"+palabra;
    objetivo="-"+objetivo;
    
    // Inicializar la matriz de memoización con -1 (no calculado)
    tabla = vector<vector<int>>(palabra.size(), vector<int>(objetivo.size(), -1));
    tabla[0][0] = 0;
}


int main() {
    if (set()){
        return 1;
    }
    if (GET_COSTOS()){
        return 1;
    }
    cout<<"##################################################################################\n";
    cout<<"\n    Distancia minima de edicion extendida con enfoque de programacion dinamica \n\n";
    cout<<" palabra: "<<palabra<<"\n objetivo: "<<objetivo<<"\n\n";
    string p=palabra;
    string o=objetivo;
    helpDistanciaEdicion();

    // Calcular la distancia de edicion
    auto inicio = chrono::high_resolution_clock::now();
    int distancia = distanciaEdicion(palabra.size() - 1, objetivo.size() - 1);
    auto fin = chrono::high_resolution_clock::now();

    chrono::duration<double> duracion = fin - inicio;

    cout << " La distancia de edicion entre '" << p << "' y '" << o << "' es: " << distancia << "\n";
    cout << " Tiempo de ejecución: " << duracion.count() << " segundos.\n";
    cout << " Uso de memoria: " << getMemoryUsage() << " KB.\n";
    cout<<"\n##################################################################################\n";
    return 0;
}