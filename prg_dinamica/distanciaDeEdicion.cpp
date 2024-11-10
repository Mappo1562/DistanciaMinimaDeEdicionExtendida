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
    if (i >= palabra.size()){
        int ret=0;
        for (char c:objetivo){
            ret += 1;  // costo_ins(c)
        }
        return ret;
    }
    // objetivo vacio
    if (j >= objetivo.size()){
        int ret=0;
        for (char c:palabra){
            ret += 1;  // costo_del(c)
        }
        return ret;
    }
    // caracter igual
    if (palabra[i] == objetivo[j]){
        return distanciaEdicion(i++, j++); // se le puede agregar el costo de intercambiar el mismo caracter
    }
    
    int eliminar = distanciaEdicion(i+1,j) + costo_del(palabra[i]);
    int insertar = distanciaEdicion(i, j+1) + costo_ins(objetivo[j]); 
    // si se quiere optimizar se puede asumir q la insercion es correcta, el primer
    // parametro seria la palabra como esta y el segundo la obj DESDE LA POS 1
    int sustituir = distanciaEdicion(i+1, j+1); 
    // con sustituir pasa lo mismo, solo que los 2 comenzaran desde pos 1
    int transponer = INT_MAX;
    if (i <palabra.size()-1 && j<objetivo.size()-1 && palabra[0] == objetivo[1] && palabra[1] == objetivo[0]){
        transponer = distanciaEdicion(i+2,j+2) + costo_trans(palabra[i],palabra[i+1]);
    }

    cout<<"eliminar: "<<eliminar<<"\n";
    cout<<"insertar "<<insertar<<"\n";
    cout<<"sustituir: "<<sustituir<<"\n";
    cout<<"transponer: "<<transponer<<"\n\n";
    return min(eliminar,min(insertar,min(sustituir,transponer))); // + costo
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
    // init(cubo, palabra, obj);
    tabla.reserve(palabra.size());
    for (auto X:tabla){
        X.reserve(objetivo.size());
    }
    fill(&tabla[0][0], &tabla[0][0] + palabra.size() * objetivo.size(), -1);
    init();
    cout<<distanciaEdicion(palabra.size(),objetivo.size())<<"\n";
    return 0;
}