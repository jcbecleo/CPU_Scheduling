#include <stdio.h>
#include <stdlib.h>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
};

void sjf(struct Process *processes, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int completionTimes[n];
    int turnaroundTimes[n];

    printf("Gantt Chart:\n");

    printf("|");
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        int shortestIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (processes[j].arrivalTime <= currentTime && processes[j].burstTime < processes[shortestIndex].burstTime) {
                shortestIndex = j;
            }
        }

        printf(" P%d %2d-%2d |", processes[shortestIndex].processID, currentTime, currentTime + processes[shortestIndex].burstTime - 1);

        processes[shortestIndex].completionTime = currentTime + processes[shortestIndex].burstTime;
        completionTimes[i] = processes[shortestIndex].completionTime;
        turnaroundTimes[i] = processes[shortestIndex].completionTime - processes[shortestIndex].arrivalTime;

        currentTime = processes[shortestIndex].completionTime;
        struct Process temp = processes[i];
        processes[i] = processes[shortestIndex];
        processes[shortestIndex] = temp;
    }
    printf("\n");

    printf("\nProcess Table:\n");
    printf("| Process ID | Arrival Time | CPU Burst | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("|------------|--------------|-----------|------------------|------------------|--------------|\n");
    for (int i = 0; i < n; i++) {
        printf("|     %2d     |      %2d      |     %2d    |       %2d-%2d     |        %2d        |      %2d      |\n",
               processes[i].processID, processes[i].arrivalTime, processes[i].burstTime,
               completionTimes[i] - processes[i].burstTime, completionTimes[i],
               turnaroundTimes[i], turnaroundTimes[i] - processes[i].burstTime);
    }

    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        totalTurnaroundTime += turnaroundTimes[i];
        totalWaitingTime += turnaroundTimes[i] - processes[i].burstTime;
    }
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;
    float avgWaitingTime = (float)totalWaitingTime / n;

    printf("\nAverage Turnaround Time: %.2f\n", avgTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
}

int main() {
    printf("+===============+\n");
    printf("  Shortest Job First\n");
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
    }

    sjf(processes, n);

    free(processes);

    return 0;
}