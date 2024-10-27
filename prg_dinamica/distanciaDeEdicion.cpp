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

struct nodo{
    int value;
    int s;
    int i;
    int e;
    int t;
};

string sustitucion(string texto, char b){
    texto[0] = b;
    return texto;
}


string insercion(string texto, char a){
    return texto.insert(0,1,a);
}


string eliminacion(string texto){
    return texto.erase(0,1);
}


string transposicion(string texto, int i){
    if (i+1 >= texto.size())
        return "";
    char aux=texto[i];
    texto[i]=texto[i+1];
    texto[i+1]=aux;
    return texto;
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


int distanciaEdicion(string palabra, string obj){
    if (palabra.empty()){
        int ret=0;
        for (char c:obj){
            ret += 1;
        }
        return ret;
    }
    if (obj.empty()){
        int ret=0;
        for (char c:palabra){
            ret += 1;
        }
        return ret;
    }
}

void init(vector<vector<nodo>> cubo, string palabra, string obj){
    int aux;
    for(int i=0;i<palabra.size()){
        for (int j=0;j<obj.size();j++){
            aux = 0;
            if (palabra[i] == palabra[j])
                aux++;
            cubo[i][j].value = min(aux,i+1,j+1);
        }
    }
}

int main(){
    string palabra,objetivo;
    if (set(palabra,objetivo)){
        return 1;
    }


    vector<vector<nodo>> cubo;

    cout<<palabra<<"\n"<<objetivo<<"\n";
    init(cubo, palabra, obj);
    cout<<distanciaEdicion(palabra,objetivo)<<"\n";
    return 0;
}