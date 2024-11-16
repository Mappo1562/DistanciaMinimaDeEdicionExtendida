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



void imprimirTabla() {
    for (const auto& fila : tabla) {
        for (int valor : fila) {
            cout << valor << " ";
        }
        cout << endl;
    }
}

int set(){
    ifstream data("entrada.txt");
    if (!data){
        cout<<"No se pudo abrir el archivo.\n";
        return 1;
    }
    cin.rdbuf(data.rdbuf());

    cin>>palabra;
    palabra = "-"+palabra;
    cin>>objetivo;
    objetivo = "-"+objetivo;
    data.close();
    return 0;
}

int distanciaLevenshtein(int i, int j) {

    if (tabla[i][j] != -1) 
        return tabla[i][j];
    
    if(i==0){
        tabla[i][j] = distanciaLevenshtein(0,j-1) + costo_ins(objetivo[j]);
        return tabla[i][j];
    }
    if(j==0){
        tabla[i][j] = distanciaLevenshtein(i-1,j) + costo_del(palabra[i]);
        return tabla[i][j];
    }

    if (palabra[i] == objetivo[j]) {
        tabla[i][j] = distanciaLevenshtein(i - 1, j - 1);
        return tabla[i][j];
    } 


    int eliminar = distanciaLevenshtein(i - 1, j) + costo_del(palabra[i]);
    int insertar = distanciaLevenshtein(i, j - 1) + costo_ins(objetivo[j]); 
    int sustituir = distanciaLevenshtein( i - 1, j - 1) + costo_sub(palabra[i],objetivo[j]);
    int transponer = INT_MAX;  
    if (i > 1 && j > 1 && palabra[i] == objetivo[j - 1] && palabra[i - 1] == objetivo[j]) {
        transponer = distanciaLevenshtein(i - 2, j - 2) + costo_trans(palabra[i],palabra[i-1]);
    }

    tabla[i][j] = min({eliminar, insertar, sustituir, transponer});
    
    return tabla[i][j];
}



int main() {
    if (set()){
        return 1;
    }
    if (GET_COSTOS()){
        return 1;
    }
    cout<<palabra<<"\n"<<objetivo<<"\n";
    
    // Inicializar la matriz de memoización con -1 (no calculado)
    int n = palabra.size();
    int m = objetivo.size();
    tabla = vector<vector<int>>(n, vector<int>(m, -1));
    tabla[0][0] = 0;
    // Calcular la distancia de Levenshtein empezando desde el final de ambas palabras
    int distancia = distanciaLevenshtein(n - 1, m - 1);
    cout << "La distancia de Levenshtein entre '" << palabra << "' y '" << objetivo << "' es: " << distancia << endl;
    imprimirTabla();
    return 0;
}