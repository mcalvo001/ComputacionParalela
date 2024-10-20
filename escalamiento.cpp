#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <omp.h>

// Función para generar un arreglo de números aleatorios
std::vector<int> generarArregloAleatorio(size_t N) {
    std::vector<int> arr(N);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);

    for (size_t i = 0; i < N; ++i) {
        arr[i] = dis(gen);
    }
    return arr;
}

// Función para calcular el promedio en paralelo
double calcularPromedioParalelo(const std::vector<int>& arr, int numThreads) {
    double suma = 0.0;
    #pragma omp parallel num_threads(numThreads) reduction(+:suma)
    {
        #pragma omp for
        for (size_t i = 0; i < arr.size(); ++i) {
            suma += arr[i];
        }
    }
    return suma / arr.size();
}

// Función para medir el tiempo de ejecución
double medirTiempo(const std::vector<int>& arr, int numThreads) {
    auto inicio = std::chrono::high_resolution_clock::now();
    calcularPromedioParalelo(arr, numThreads);
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = fin - inicio;
    return duracion.count();
}

int main() {
    const size_t N_BASE = 100000000; // 100 millones de elementos
    const std::vector<int> numThreads = {1, 2, 4, 8, 16};

    std::cout << "Escalamiento Fuerte:" << std::endl;
    std::cout << "Threads,Tiempo" << std::endl;
    auto arrFuerte = generarArregloAleatorio(N_BASE);
    for (int t : numThreads) {
        double tiempo = medirTiempo(arrFuerte, t);
        std::cout << t << "," << tiempo << std::endl;
    }

    std::cout << "\nEscalamiento Débil:" << std::endl;
    std::cout << "Threads,N,Tiempo" << std::endl;
    for (int t : numThreads) {
        size_t N = N_BASE * t;
        auto arrDebil = generarArregloAleatorio(N);
        double tiempo = medirTiempo(arrDebil, t);
        std::cout << t << "," << N << "," << tiempo << std::endl;
    }

    return 0;
}