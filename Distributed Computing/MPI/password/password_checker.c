#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define MAX_PASS_LEN 100
#define CORRECT_PASSWORD "open123"
#define TAG_PASSWORD 1
#define TAG_RESPONSE 2

int main(int argc, char** argv) {
    int rank, size;
    char password[MAX_PASS_LEN];
    char response[50];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Total number of processes

    if (rank == 0) {
        // Master collects passwords for all workers
        for (int i = 1; i < size; i++) {
            printf("[Master] Enter password for process %d: \n", i);
            fgets(password, MAX_PASS_LEN, stdin);
            password[strcspn(password, "\n")] = 0;

            // Send the password to the worker
            MPI_Send(password, strlen(password) + 1, MPI_CHAR, i, TAG_PASSWORD, MPI_COMM_WORLD);
        }

        // Receive responses from all workers
        for (int i = 1; i < size; i++) {
            MPI_Recv(response, sizeof(response), MPI_CHAR, i, TAG_RESPONSE, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("[Master] Process %d says: %s\n", i, response);
        }

    } else {
        // Worker receives password from master
        MPI_Recv(password, MAX_PASS_LEN, MPI_CHAR, 0, TAG_PASSWORD, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if (strcmp(password, CORRECT_PASSWORD) == 0) {
            strcpy(response, "Password matched! Welcome.\n");
        } else {
            strcpy(response, "Incorrect password.\n");
        }

        // Send response back to master
        MPI_Send(response, strlen(response) + 1, MPI_CHAR, 0, TAG_RESPONSE, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

