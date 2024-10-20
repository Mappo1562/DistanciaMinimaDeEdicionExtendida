#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
using namespace std;

/*
para que funcione se necesita escribir la entrada
a utilizar en el archivo entrada.txt, que sigue el 
formato de 2 enteros, los cuales indican el largo
de la palabra 1 y el de la palabra 2 respectivamente
seguido de n caracteres que indiquen el alfabeto a
utilizar, por ejemplo:
10
5
a
b
c
d
e
f
g
h
i
*/

/*
para compílar hay que estar en la carpeta tarea 2-3
y escribir el siguiente comando
    g++ -o out dataset/datasetgenerator.cpp -Wall
y para correr
    ./out
*/

int main(){
    random_device generador;
    mt19937 gen(generador());

    ifstream alfabeto("dataset/entrada.txt");
    if (!alfabeto){
        cout<<"No se pudo abrir el archivo.\n";
        return 1;
    }

    vector<char> A;
    char c;
    cin.rdbuf(alfabeto.rdbuf());

    int Lp1,Lp2;
    cin>>Lp1;
    cin>>Lp2;

    while (cin>>c){
        A.push_back(c);
    }
    alfabeto.close();

    uniform_int_distribution<> distribucion(0,A.size()-1);

    ofstream salida("dataset.txt");
    if (!salida){
        cout<<"Error al crear/abrir el archivo\n";
        return 1;
    }

    for (int i=0;i<Lp1;i++){
        c=A[distribucion(gen)];
        salida<<c;
    }
    salida<<"\n";
    for (int i=0;i<Lp2;i++){
        c=A[distribucion(gen)];
        salida<<c;
    }
    salida<<"\n";

    salida.close();
    return 0;
}