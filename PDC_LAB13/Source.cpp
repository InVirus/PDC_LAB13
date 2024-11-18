#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;

void loadGraph(const string& filename, int& n, int& m, int**& edges) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    inputFile >> n >> m;

    if (n <= 0 || m <= 0) {
        cout << "Invalid number of vertices or edges." << endl;
        n = 0;
        m = 0;
        return;
    }

    edges = new int* [m];
    for (int i = 0; i < m; ++i) {
        edges[i] = new int[2];
        inputFile >> edges[i][0] >> edges[i][1];

        if (edges[i][0] <= 0 || edges[i][1] <= 0) {
            cout << "Invalid edge data: " << edges[i][0] << " " << edges[i][1] << endl;
            for (int j = 0; j < i; ++j) {
                delete[] edges[j];
            }
            delete[] edges;
            edges = nullptr;
            return;
        }
    }

    inputFile.close();
}

int** buildAdjacencyMatrix(int n, int m, int** edges) {
    int** adjacencyMatrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        adjacencyMatrix[i] = new int[n]();
    }
    for (int i = 0; i < m; ++i) {
        int v = edges[i][0] - 1;
        int u = edges[i][1] - 1;
        adjacencyMatrix[v][u] = 1;
        adjacencyMatrix[u][v] = 1;
    }

    return adjacencyMatrix;
}

void graphColoring(int** adjacencyMatrix, int n) {
    vector<int> result(n, -1); 
    vector<bool> available(n, true); 

    result[0] = 0;

    for (int u = 1; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (adjacencyMatrix[u][v] == 1 && result[v] != -1) {
                available[result[v]] = false;
            }
        }

        int cr;
        for (cr = 0; cr < n; cr++) {
            if (available[cr]) {
                break;
            }
        }

        result[u] = cr;

        fill(available.begin(), available.end(), true);
    }

    cout << "Розфарбування графа:\n";
    for (int u = 0; u < n; u++) {
        cout << "Вершина " << u + 1 << " -> Колір " << result[u] + 1 << "\n";
    }

    int minColors = *max_element(result.begin(), result.end()) + 1;
    cout << "Мінімальна кількість кольорів: " << minColors << endl;
}

void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n, m;
    int** edges = nullptr;
    string inputFile, outputFile;

    cout << "Enter input file: ";
    cin >> inputFile;

    loadGraph(inputFile, n, m, edges);
    if (n <= 0 || m <= 0 || edges == nullptr) {
        cout << "Invalid graph data" << endl;
        return 1;
    }

    int** adjacencyMatrix = buildAdjacencyMatrix(n, m, edges);

    graphColoring(adjacencyMatrix, n);

    freeMatrix(adjacencyMatrix, n);

    for (int i = 0; i < m; ++i) {
        delete[] edges[i];
    }
    delete[] edges;

    return 0;
}
