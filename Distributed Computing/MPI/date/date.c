#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BUFFER_SIZE 10000
#define TAG_REQUEST 1
#define TAG_RESPONSE 2

void get_system_info(char* response) {
    time_t t;
    time(&t);
    char* current_time = ctime(&t);  // Current time as a string

    // Open a process to execute "uname -a" and capture system info
    FILE *fp = popen("uname -a", "r");
    if (fp == NULL) {
        perror("Failed to run command");
        strcpy(response, "Failed to get system info.");
        return;
    }

    char sys_info[MAX_BUFFER_SIZE];
    fgets(sys_info, sizeof(sys_info), fp);
    fclose(fp);

    // Remove trailing newline if exists in sys_info
    sys_info[strcspn(sys_info, "\r\n")] = 0;

    // Calculate available space in response for sys_info
    size_t available_space = MAX_BUFFER_SIZE - strlen(current_time) - 20;  // 20 for "Time: " and "System Info: "
    
    // Ensure that sys_info does not exceed available space
    if (strlen(sys_info) > available_space) {
        sys_info[available_space] = '\0';  // Truncate sys_info if necessary
    }

    // Safely format the string with the available space for sys_info
    snprintf(response, MAX_BUFFER_SIZE, "Time: %sSystem Info: %s", current_time, sys_info);

    // Ensure that snprintf won't overflow by limiting the output
    response[MAX_BUFFER_SIZE - 1] = '\0';  // Always null-terminate to prevent overflow
}

int main(int argc, char** argv) {
    int rank, size;
    char response[MAX_BUFFER_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get total number of processes

    if (rank == 0) {
        // Master Process: Send a request to all worker processes
        printf("[Master] Requesting system information from all worker processes...\n");

        for (int i = 1; i < size; i++) {
            // Send request to worker
            MPI_Send(NULL, 0, MPI_CHAR, i, TAG_REQUEST, MPI_COMM_WORLD);
        }

        // Receive responses from workers
        for (int i = 1; i < size; i++) {
            MPI_Recv(response, MAX_BUFFER_SIZE, MPI_CHAR, i, TAG_RESPONSE, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("[Master] Received from Process %d:\n%s\n", i, response);
        }
    } else {
        // Worker Process: Get system info and send it back to master
        MPI_Recv(NULL, 0, MPI_CHAR, 0, TAG_REQUEST, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        // Get system information and current time
        get_system_info(response);

        // Send response back to master
        MPI_Send(response, strlen(response) + 1, MPI_CHAR, 0, TAG_RESPONSE, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

