#include "../costos.cpp"
using namespace std;


/*
para compílar hay que estar en la carpeta tarea 2-3
y escribir el siguiente comando
    g++ -o out fuerzabruta/distanciadeedicion.cpp -Wall
y para correr
    ./out
*/

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


int distanciaEdicion(string palabra, string obj, int flag = 1){
    // palabra vacia
    if (palabra.empty()){
        int ret=0;
        for (char c:obj){
            ret += 1;
        }
        return ret;
    }
    // objetivo vacio
    if (obj.empty()){
        int ret=0;
        for (char c:palabra){
            ret += 1;
        }
        return ret;
    }
    // primer caracter igual
    if (palabra[0] == obj[0])
        return distanciaEdicion(palabra.substr(1), obj.substr(1));
    
    int eliminar = distanciaEdicion(eliminacion(palabra),obj);
    int insertar = distanciaEdicion(insercion(palabra,obj[0]).substr(1), obj.substr(1)); 
    // si se quiere optimizar se puede asumir q la insercion es correcta, el primer
    // parametro seria la palabra como esta y el segundo la obj DESDE LA POS 1
    int sustituir = distanciaEdicion(sustitucion(palabra,obj[0]).substr(1), obj.substr(1));
    // con sustituir pasa lo mismo, solo que los 2 comenzaran desde pos 1
    int transponer = 999999999;
    if (flag){
        flag=0;
        transponer = distanciaEdicion(transposicion(palabra,0),obj,0);
    }

    cout<<"eliminar: "<<eliminar<<"\n";
    cout<<"insertar "<<insertar<<"\n";
    cout<<"sustituir: "<<sustituir<<"\n";
    cout<<"transponer: "<<transponer<<"\n\n";
    return 1 + min(eliminar,min(insertar,min(sustituir,transponer)));
}

int main(){
    string palabra,objetivo;
    if (set(palabra,objetivo)){
        return 1;
    }


    cout<<palabra<<"\n"<<objetivo<<"\n";
    cout<<distanciaEdicion(palabra,objetivo)<<"\n";
    return 0;
}