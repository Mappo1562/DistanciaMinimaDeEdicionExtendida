#include "../costos.cpp"
using namespace std;


/*
para compílar hay que estar en la carpeta tarea 2-3
y escribir el siguiente comando
    g++ -o out fuerzabruta/distanciadeedicion.cpp -Wall
y para correr
    ./out
*/

string palabra, objetivo;



int set(){
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
    if (palabra[i] == objetivo[j])
        return distanciaEdicion(i++, j++);
    
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
    return min(eliminar,min(insertar,min(sustituir,transponer)));
}

int main(){
    string palabra,objetivo;
    if (set()){
        return 1;
    }


    cout<<palabra<<"\n"<<objetivo<<"\n";
    cout<<distanciaEdicion(0,0)<<"\n";
    return 0;
}