#include <iostream>

using namespace std;

constexpr int INF = 1000000000;

void initializeMatrix(int** &matrix, int vertices) {
    matrix = new int*[vertices];
    for (int i = 0; i < vertices; i++) {
        matrix[i] = new int[vertices];
        for (int j = 0; j < vertices; j++) {
            matrix[i][j] = 0;
        }
    }
}

void deleteMatrix(int** &matrix, int vertices) {
    for (int i = 0; i < vertices; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void addEdge(int** matrix, int vertices, int i, int j, int weight) {
    if (i >= 0 && i < vertices && j >= 0 && j < vertices) {
        matrix[i][j] = weight;
    }
}

void displayMatrix(int** matrix, int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void dijkstra(int** adjMatrix, int vertices, int startVertex) {
    int* distance = new int[vertices];
    bool* visited = new bool[vertices];

    for (int i = 0; i < vertices; ++i) {
        distance[i] = INF;
        visited[i] = false;
    }

    distance[startVertex] = 0;

    for (int count = 0; count < vertices - 1; ++count) {
        int u, minDistance = INF;
        for (int v = 0; v < vertices; ++v) {
            if (!visited[v] && distance[v] <= minDistance) {
                minDistance = distance[v];
                u = v;
            }
        }

        visited[u] = true;

        for (int v = 0; v < vertices; ++v) {
            if (!visited[v] && adjMatrix[u][v] && distance[u] != INF &&
                distance[u] + adjMatrix[u][v] < distance[v]) {
                distance[v] = distance[u] + adjMatrix[u][v];
            }
        }
    }

    cout << "Vertex\tDistance from Source\n";
    for (int i = 0; i < vertices; ++i) {
        cout << i << "\t" << distance[i] << endl;
    }

    delete[] distance;
    delete[] visited;
}

int main() {
    int vertices = 6 + 1;
    int** adjMatrix;

    initializeMatrix(adjMatrix, vertices);

    addEdge(adjMatrix, vertices, 1, 2, 2);
    addEdge(adjMatrix, vertices, 1, 3, 4);
    addEdge(adjMatrix, vertices, 2, 3, 1);
    addEdge(adjMatrix, vertices, 3, 5, 3);
    addEdge(adjMatrix, vertices, 4, 6, 1);
    addEdge(adjMatrix, vertices, 5, 4, 2);
    addEdge(adjMatrix, vertices, 5, 6, 5);

    cout << "Adjacency Matrix:" << endl;
    displayMatrix(adjMatrix, vertices);

    int startVertex = 1;
    cout << "Dijkstra's Algorithm:" << endl;
    dijkstra(adjMatrix, vertices, startVertex);

    deleteMatrix(adjMatrix, vertices);

    return 0;
}
