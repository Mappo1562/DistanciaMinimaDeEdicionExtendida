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




int distanciaEdicion(int i, int j) {
    if (i<0 && j<0)
        return 0;
    // palabra vacía
    if (i < 0) {
        /*
        int ret = 0;
        while (j >= 0) {
            ret += costo_ins(objetivo[j]);  // insertar caracteres restantes de objetivo
            j--;
        }
        return ret;
        */
        return costo_ins(objetivo[j]) + distanciaEdicion(i,j-1);
    }
    // objetivo vacío
    if (j < 0) {
        /*
        int ret = 0;
        while (i >= 0) {
            ret += costo_del(palabra[i]);  // eliminar caracteres restantes de palabra
            i--;
        }
        return ret;
        */
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


    cout<<palabra<<"\n"<<objetivo<<"\n";
    cout<<distanciaEdicion(palabra.size()-1,objetivo.size()-1)<<"\n";
    return 0;
}