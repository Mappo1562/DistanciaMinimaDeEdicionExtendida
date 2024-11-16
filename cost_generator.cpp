#include <iostream>
#include <fstream>
#include <random>

int N=26;

void GENERATE_COST_FILES() {
    // Configurar el generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    int min, max;

//###################################################################################################//
    // Crear archivo para los costos de inserción
    min = 1;
    max = 3;

    std::uniform_int_distribution<> dis(min, max);
    std::ofstream costInsert("costos/cost_insert.txt");
    if (!costInsert) {
        std::cerr << "No se pudo crear el archivo cost_insert.txt\n";
        return;
    }
    for (int i = 0; i < N; ++i) {
        costInsert << dis(gen) << " ";
    }
    costInsert.close();

//###################################################################################################//
    // Crear archivo para los costos de eliminación
    min = 1;
    max = 3;

    std::uniform_int_distribution<> dis2(min, max);
    std::ofstream costDelete("costos/cost_delete.txt");
    if (!costDelete) {
        std::cerr << "No se pudo crear el archivo cost_delete.txt\n";
        return;
    }
    for (int i = 0; i < N; ++i) {
        costDelete << dis2(gen) << " ";
    }
    costDelete.close();

//###################################################################################################//
    // Crear archivo para los costos de sustitución
    min=2;
    max=5;
    std::uniform_int_distribution<> dis3(min, max);
    std::ofstream costReplace("costos/cost_replace.txt");
    if (!costReplace) {
        std::cerr << "No se pudo crear el archivo cost_replace.txt\n";
        return;
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            costReplace << dis3(gen) << " ";
        }
        costReplace << "\n"; // Separar filas
    }
    costReplace.close();

//###################################################################################################//
    // Crear archivo para los costos de transposición
    min=1;
    max=2;
    std::uniform_int_distribution<> dis4(min, max);
    std::ofstream costTranspose("costos/cost_transpose.txt");
    if (!costTranspose) {
        std::cerr << "No se pudo crear el archivo cost_transpose.txt\n";
        return;
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            costTranspose << dis4(gen) << " ";
        }
        costTranspose << "\n"; 
    }
    costTranspose.close();

    std::cout << "Archivos generados correctamente.\n";
}

int main() {

    // Crear los archivos de costos
    GENERATE_COST_FILES();

    return 0;
}