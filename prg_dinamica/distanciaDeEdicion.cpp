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

/*
establecer estructura de la solucion optima
describir su valor
calcular valor
*/


string palabra,objetivo;
vector<vector<int>> tabla;
/*
void imprimirTabla() {
    for (const auto& fila : tabla) {
        for (int valor : fila) {
            if (valor == INT_MAX)  // Opcional: manejo especial para INT_MAX
                cout << "INF ";
            else
                cout << valor << " ";
        }
        cout << endl;
    }
}



int set(string& palabra, string& objetivo){
    ifstream data("dataset.txt");
    if (!data){
        cout<<"No se pudo abrir el archivo.\n";
        return 1;
    }
    cin.rdbuf(data.rdbuf());

    cin>>palabra;
    cin>>objetivo;
    data.close();
    return 0;
}


int distanciaEdicion(int i, int j){ // i para recorrer palabra y j para objetivo
    if (tabla[i][j] > -1)
        return tabla[i][j];
    // palabra vacia
    if (i<0){
        int ret = 0;
        int o=j;
        for (j;j>=0;--j){
            ret += costo_ins(objetivo[j]);
        }
        return ret;
    }
    else if(j<0){
        int ret=0;
        int o=i;
        for (i;i>=0;--i){
            ret+=costo_del(palabra[i]);
        }
        return ret;
    }
    else if(j<0 && i<0){
        return 0;
    }
    // caracter igual
    if (palabra[i] == objetivo[j]){
        return distanciaEdicion(i-1, j-1); // se le puede agregar el costo de intercambiar el mismo caracter
    }
    
    int eliminar = distanciaEdicion(i-1,j) + costo_del(palabra[i]);
    int insertar = distanciaEdicion(i, j-1) + costo_ins(objetivo[j]); 
    // si se quiere optimizar se puede asumir q la insercion es correcta, el primer
    // parametro seria la palabra como esta y el segundo la obj DESDE LA POS 1
    int sustituir = distanciaEdicion(i-1, j-1); 
    // con sustituir pasa lo mismo, solo que los 2 comenzaran desde pos 1
    int transponer = INT_MAX;
    if (i <palabra.size()-1 && j<objetivo.size()-1 && palabra[0] == objetivo[1] && palabra[1] == objetivo[0]){
        transponer = distanciaEdicion(i-2,j-2) + costo_trans(palabra[i],palabra[i-1]);
    }

    cout<<"eliminar: "<<eliminar<<"\n";
    cout<<"insertar "<<insertar<<"\n";
    cout<<"sustituir: "<<sustituir<<"\n";
    cout<<"transponer: "<<transponer<<"\n\n";
    tabla[i][j] = min(eliminar,min(insertar,min(sustituir,transponer)));
    cout<<"i: "<<i<<"   j: "<<j<<"\n\n";
    return tabla[i][j]; // + costo
}




void init(){
    tabla[0][0] = 0;
    for (int i=1;i<=palabra.size();i++)
        tabla[i][0] = costo_del(palabra[i-1]);
    
    for (int j=1;j<=objetivo.size();j++)
        tabla[0][j] = costo_ins(objetivo[j-1]);
}

int main(){
    if (set(palabra,objetivo)){
        return 1;
    }

    cout<<palabra<<"\n"<<objetivo<<"\n";
    tabla.resize(palabra.size()+1, vector<int>(objetivo.size()+1, -1));
    cout<<distanciaEdicion(palabra.size()-1,objetivo.size()-1)<<"\n";
    imprimirTabla();
    return 0;
}
*/

void imprimirTabla() {
    for (const auto& fila : tabla) {
        for (int valor : fila) {
            cout << valor << " ";
        }
        cout << endl;
    }
}

int set(string& palabra, string& objetivo){
    ifstream data("dataset.txt");
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
    } 
    else {

        int eliminar = distanciaLevenshtein(i - 1, j) + costo_del(palabra[i]);
        int insertar = distanciaLevenshtein(i, j - 1) + costo_ins(objetivo[j]); 
        int sustituir = distanciaLevenshtein( i - 1, j - 1) + costo_sub(palabra[i],objetivo[j]);
        int transponer = INT_MAX;  
        if (i > 1 && j > 1 && palabra[i] == objetivo[j - 1] && palabra[i - 1] == objetivo[j]) {
            transponer = distanciaLevenshtein(i - 2, j - 2) + costo_trans(palabra[i],palabra[i-1]);
        }

        tabla[i][j] = min({eliminar, insertar, sustituir, transponer});
    }

    return tabla[i][j];
}



int main() {
    if (set(palabra,objetivo)){
        return 1;
    }

    cout<<palabra<<"\n"<<objetivo<<"\n";
    
    // Inicializar la matriz de memoización con -1 (no calculado)
    int m = palabra.size();
    int n = objetivo.size();
    tabla = vector<vector<int>>(m, vector<int>(n, -1));
    tabla[0][0] = 0;
    // Calcular la distancia de Levenshtein empezando desde el final de ambas palabras
    int distancia = distanciaLevenshtein(m - 1, n - 1);
    cout << "La distancia de Levenshtein entre '" << palabra << "' y '" << objetivo << "' es: " << distancia << endl;
    imprimirTabla();
    return 0;
}