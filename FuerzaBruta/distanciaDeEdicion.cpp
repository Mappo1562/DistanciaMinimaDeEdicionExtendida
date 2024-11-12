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


int set(){
    ifstream data("dataset.txt");
    if (!data){
        cout<<"No se pudo abrir el archivo.\n";
        return 1;
    }
    data>>palabra;
    data>>objetivo;
    data.close();
    return 0;
}


int distanciaEdicion(unsigned int i,unsigned int j){ // i para recorrer palabra y j para objetivo
    // cout<<c++<<"\n";
    // palabra vacia
    if (i >= palabra.size()){
        int ret=0;
        while (j<objetivo.size()){ // esta malooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
            ret += costo_ins(objetivo[j]);  // costo_ins(c)
            j++;
        }
        return ret;
    }
    // objetivo vacio
    if (j >= objetivo.size()){
        int ret=0;
        while (i<palabra.size()){
            ret += costo_del(palabra[i]);  // costo_del(c)
            i++;
        }
        return ret;
    }
    // caracter igual
    if (palabra[i] == objetivo[j])
        return distanciaEdicion(i+1, j+1);
    
    int eliminar = distanciaEdicion(i+1,j) + costo_del(palabra[i]);
    int insertar = distanciaEdicion(i, j+1) + costo_ins(objetivo[j]); 
    // si se quiere optimizar se puede asumir q la insercion es correcta, el primer
    // parametro seria la palabra como esta y el segundo la obj DESDE LA POS 1
    int sustituir = distanciaEdicion(i+1, j+1) + costo_sub(palabra[i],objetivo[j]); 
    // con sustituir pasa lo mismo, solo que los 2 comenzaran desde pos 1
    int transponer = INT_MAX;
    if (i <palabra.size()-1 && j<objetivo.size()-1 && palabra[0] == objetivo[1] && palabra[1] == objetivo[0]){
        transponer = distanciaEdicion(i+2,j+2) + costo_trans(palabra[i],palabra[i+1]);
    }

    cout<<"eliminar: "<<eliminar<<"\n";
    cout<<"insertar "<<insertar<<"\n";
    cout<<"sustituir: "<<sustituir<<"\n";
    cout<<"transponer: "<<transponer<<"\n\n";
    return min({eliminar,insertar,sustituir,transponer});
}


int main(){
    if (set()){
        return 1;
    }


    cout<<palabra<<"\n"<<objetivo<<"\n";
    cout<<distanciaEdicion(0,0)<<"\n";
    return 0;
}