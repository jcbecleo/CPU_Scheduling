#include <stdio.h>
#include <stdlib.h>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int priority;
    int priorityDupe;
    int turnaroundTime;
    int waitingTime;
    int completionTime;
    int queueLevel;
};

void calculateTimes(struct Process processes[], int numProcesses);

int main() {
    int numProcesses;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    struct Process processes[numProcesses];

    for (int i = 0; i < numProcesses; i++) {
        processes[i].processID = i + 1;

        printf("Enter the Arrival time for Process %d: ", i + 1);
        scanf("%d", &(processes[i].arrivalTime));

        printf("Enter the Burst time for Process %d: ", i + 1);
        scanf("%d", &(processes[i].burstTime));

        printf("Enter the Priority for Process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].priorityDupe = processes[i].priority;

        printf("Enter the Queue Level for Process %d (1 - Priority, 2 - Shortest Job First): ", i + 1);
        scanf("%d", &processes[i].queueLevel);
    }

    for (int i = 0; i < numProcesses - 1; i++) {
        for (int j = 0; j < numProcesses - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    calculateTimes(processes, numProcesses);

    printf("\n\nProcess ID  Arrival Time  Burst Time  Priority  Queue Level  Completion Time  Turnaround Time  Waiting Time  \n");
    for (int i = 0; i < numProcesses; i++) {
        printf("   P%d            %2d            %2d        %2d              %2d                %2d                %2d                %2d                \n",
               processes[i].processID, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].priority, processes[i].queueLevel, processes[i].completionTime,
               processes[i].turnaroundTime, processes[i].waitingTime);
    }

    printf("\nGantt Chart:\n");

    int chart[numProcesses * 2];
    int chartIndex = 0;

    for (int i = 0; i < numProcesses * 2; i++) {
        chart[i] = -1;
    }

    for (int i = 0; i < numProcesses; i++) {
        chart[chartIndex++] = processes[i].processID;
        chart[chartIndex++] = processes[i].completionTime;
    }

    for (int i = 0; i < numProcesses * 2; i += 2) {
        printf("|  P%d  ", chart[i]);
    }
    printf("|\n");

    printf("0      ");
    for (int i = 0; i < numProcesses * 2; i += 2) {
        printf("%d      ", chart[i + 1]);
    }
    printf("\n");

    return 0;
}

void calculateTimes(struct Process processes[], int numProcesses) {
    int currentTime = 0;

    for (int i = 0; i < numProcesses; i++) {
        if (processes[i].queueLevel == 1) {
            int highestPriorityIndex = i;

            for (int j = i + 1; j < numProcesses && processes[j].arrivalTime <= currentTime; j++) {
                if (processes[j].priority < processes[highestPriorityIndex].priority) {
                    highestPriorityIndex = j;
                }
            }

            struct Process temp = processes[i];
            processes[i] = processes[highestPriorityIndex];
            processes[highestPriorityIndex] = temp;

            processes[i].completionTime = currentTime + processes[i].burstTime;
            processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
            processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

            currentTime = processes[i].completionTime;
        } else if (processes[i].queueLevel == 2) {
            int shortestJobIndex = i;

            for (int j = i + 1; j < numProcesses && processes[j].arrivalTime <= currentTime; j++) {
                if (processes[j].burstTime < processes[shortestJobIndex].burstTime) {
                    shortestJobIndex = j;
                }
            }

            struct Process temp = processes[i];
            processes[i] = processes[shortestJobIndex];
            processes[shortestJobIndex] = temp;

            processes[i].completionTime = currentTime + processes[i].burstTime;
            processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
            processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

            currentTime = processes[i].completionTime;
        }
    }
}