#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
};

void srtf(struct Process *processes, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    printf("Gantt Chart:\n");

    printf("|");
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        int shortestIndex = -1;
        int shortestTime = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime < shortestTime && processes[i].remainingTime > 0) {
                shortestIndex = i;
                shortestTime = processes[i].remainingTime;
            }
        }

        if (shortestIndex == -1) {
            printf("      IDLE |");
            currentTime++;
        } else {
            printf(" P%d %2d-%2d |", processes[shortestIndex].processID, currentTime, currentTime + 1);
            processes[shortestIndex].remainingTime--;

            if (processes[shortestIndex].remainingTime == 0) {
                processes[shortestIndex].completionTime = currentTime + 1;
                completedProcesses++;
            }

            currentTime++;
        }
    }
    printf("\n");
    printf("\nProcess Table:\n");
    printf("| Process ID | Arrival Time | CPU Burst | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("|------------|--------------|-----------|------------------|------------------|--------------|\n");
    for (int i = 0; i < n; i++) {
        int turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        int waitingTime = turnaroundTime - processes[i].burstTime;
        printf("|     %2d     |      %2d      |     %2d    |        %2d        |        %2d        |      %2d      |\n",
               processes[i].processID, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].completionTime, turnaroundTime, waitingTime);
    }

    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        totalTurnaroundTime += processes[i].completionTime - processes[i].arrivalTime;
        totalWaitingTime += processes[i].completionTime - processes[i].arrivalTime - processes[i].burstTime;
    }
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;
    float avgWaitingTime = (float)totalWaitingTime / n;

    printf("\nAverage Turnaround Time: %.2f\n", avgTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
}

int main() {
    printf("+===============+\n");
    printf("  Shortest Remaining Time First\n");
    printf("+===============+\n\n");
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process *processes = (struct Process *)malloc(n * sizeof(struct Process));

    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        printf("\n");
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].completionTime = 0;
    }

    srtf(processes, n);

    free(processes);

    return 0;
}