// KNAPSACK PROBLEM
// This program solves the 0/1 Knapsack problem using dynamic programming.
// It finds the maximum value that can be obtained with a given weight limit.
// The program uses a 2D array to store the maximum value for each weight limit
// and item combination.

// KNAPSACK PROBLEM
// Solves the 0/1 Knapsack problem using dynamic programming

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_ITEMS 5
#define MIN_CAPACITY 10
#define MAX_CAPACITY 13

// Function Prototypes
void generateRandomInput(const char *filename);
void readInput(const char *filename, int *W, int w[], int v[]);
int **knapsack(int w[], int v[], int n, int W);
void printDPTable(int **B, int n, int W, FILE *fp);
void selectedItemsSolution(int **B, int w[], int v[], int n, int W, FILE *fp);
void freeTable(int **B, int n);

void generateRandomInput(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("File open error");
        return;
    }

    srand(time(NULL));
    int W = rand() % (MAX_CAPACITY - MIN_CAPACITY + 1) + MIN_CAPACITY;
    fprintf(fp, "WEIGHT:%d\n", W);

    fprintf(fp, "weight:");
    for (int i = 0; i < MAX_ITEMS; i++) {
        int weight = rand() % 10 + 1;
        fprintf(fp, "%d ", weight);
    }
    fprintf(fp, "\nvalue:");
    for (int i = 0; i < MAX_ITEMS; i++) {
        int value = rand() % 7 + 4; // value between 4 and 10
        fprintf(fp, "%d ", value);
    }
    fprintf(fp, "\n");
    fclose(fp);
}

void readInput(const char *filename, int *W, int w[], int v[]) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("File open error");
        return;
    }

    fscanf(fp, "WEIGHT:%d\n", W);
    fscanf(fp, "weight:");
    for (int i = 0; i < MAX_ITEMS; i++) {
        fscanf(fp, "%d", &w[i]);
    }
    fscanf(fp, "\nvalue:");
    for (int i = 0; i < MAX_ITEMS; i++) {
        fscanf(fp, "%d", &v[i]);
    }
    fclose(fp);
}

int **knapsack(int w[], int v[], int n, int W) {
    int **B = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        B[i] = (int *)malloc((W + 1) * sizeof(int));
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            if (i == 0 || j == 0) {
                B[i][j] = 0;
            } else if (w[i - 1] <= j) {
                B[i][j] = fmax(B[i - 1][j], B[i - 1][j - w[i - 1]] + v[i - 1]);
            } else {
                B[i][j] = B[i - 1][j];
            }
        }
    }
    return B;
}

void printDPTable(int **B, int w[], int v[], int n, int W, FILE *fp) {
    fprintf(fp, "DP Table (B[i][w]):\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            fprintf(fp, "%2d ", B[i][j]);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "\nKnapsack capacity:%d\n", W);
    fprintf(fp, "All Items:\n");
    for (int i = 0; i < n; i++) {
        fprintf(fp, "Item %d (%d,%d)\n", i + 1, w[i], v[i]);
    }
}

void selectedItemsSolution(int **B, int w[], int v[], int n, int W, FILE *fp) {
    fprintf(fp, "\nOptimal value: %d\n", B[n][W]);
    fprintf(fp, "Optimal Solution:\nItem# (weight, value)\n");

    int i = n, k = W;
    while (i > 0 && k > 0) {
        if (B[i][k] != B[i - 1][k]) {
            fprintf(fp, "Item %d (%d,%d)\n", i, w[i - 1], v[i - 1]);
            k -= w[i - 1];
        }
        i--;
    }
}

void freeTable(int **B, int n) {
    for (int i = 0; i <= n; i++) {
        free(B[i]);
    }
    free(B);
}

int main(void) {
    int W, w[MAX_ITEMS], v[MAX_ITEMS];
    int n = MAX_ITEMS;
    FILE *out;

    generateRandomInput("items5.txt");
    readInput("items5.txt", &W, w, v);

    out = fopen("knapsackOut10.txt", "w");
    if (!out) {
        perror("Output file open error");
        return 1;
    }

    int **B = knapsack(w, v, n, W);
    printDPTable(B, w, v, n, W, out);
    selectedItemsSolution(B, w, v, n, W, out);

    printf("Output file name: knapsackOut10.txt\n");

    freeTable(B, n);
    fclose(out);

    return 0;
}
