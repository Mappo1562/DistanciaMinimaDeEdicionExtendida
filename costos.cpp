#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <algorithm>
#include <climits>
#include <chrono>
#include <sstream>
using namespace std;

int N=26;
vector<int> insertar(N,0), eliminar(N,0);
vector<vector<int>> sustituir(N, vector<int>(N, 0)), transposicion(N, vector<int>(N, 0));


int GET_COSTOS(){
    int n;
    ifstream datai("costos/cost_insert.txt");
    if (!datai){
        cout<<"No se pudo abrir el archivo cost_insert.txt\n";
        return 1;
    }
    for (int i=0;i<N;++i){
        datai>>n;
        insertar[i] = n;
    }
    datai.close();


    ifstream datae("costos/cost_delete.txt");
    if (!datae){
        cout<<"No se pudo abrir el archivo cost_delete.txt\n";
        return 1;
    }
    for (int i=0;i<N;++i){
        datae>>n;
        eliminar[i] = n;
    }
    datae.close();


    ifstream datar("costos/cost_replace.txt");
    if (!datar){
        cout<<"No se pudo abrir el archivo cost_replace.txt\n";
        return 1;
    }
    for (int i=0;i<N;++i){
        for (int j=0;j<N;++j){
            datar>>n;
            sustituir[i][j] = n;
        }
    }
    datar.close();


    ifstream datat("costos/cost_transpose.txt");
    if (!datat){
        cout<<"No se pudo abrir el archivo cost_transpose.txt\n";
        return 1;
    }
    for (int i=0;i<N;++i){
        for (int j=0;j<N;++j){
            datat>>n;
            transposicion[i][j] = n;
        }
    }
    datat.close();
    return 0;
}



int costo_sub(char a, char b){
    return sustituir[a - 'a'][b - 'a'];
}



int costo_ins(char a){
    return insertar[a - 'a'];
}



int costo_del(char a){
    return eliminar[a - 'a'];
}



int costo_trans(char a, char b){
    return transposicion[a - 'a'][b - 'a'];
}