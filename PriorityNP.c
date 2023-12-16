#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int priority;
};

void displayTable(struct Process processes[], int n, int ganttChart[]) {
    printf("--------------------------------------------------------------------------------------------\n");
    printf("| ProcessID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("--------------------------------------------------------------------------------------------\n");

    float totalTurnaroundTime = 0;
    float totalWaitingTime = 0;

    for (int i = 0; i < n; i++) {
        printf("| %9d | %12d | %10d | %15d | %15d | %12d |\n",
               processes[i].processID, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].completionTime, processes[i].turnaroundTime, processes[i].waitingTime);

        totalTurnaroundTime += processes[i].turnaroundTime;
        totalWaitingTime += processes[i].waitingTime;
    }

    printf("--------------------------------------------------------------------------------------------\n");

    printf("Total Turnaround Time: %.1f\n", totalTurnaroundTime / n);
    printf("Total Waiting Time: %.1f\n", totalWaitingTime / n);

    int startTime = 0;

    printf("\nGantt Chart:\n");
    printf("--------------------------------------------------------------------------------------------\n");

    if (processes[0].arrivalTime > 0) {
        printf("| Idle %d-%d ", startTime, processes[0].arrivalTime);
        startTime = processes[0].arrivalTime;
    }

    for (int i = 0; i < n; i++) {
        printf("| P%d ", ganttChart[i]);
        int endTime = startTime + processes[i].burstTime;
        printf("%d-%d", startTime, endTime);

        while (startTime < endTime) {
            startTime++;
        }

        if (i < n - 1 && processes[i + 1].arrivalTime > endTime) {
            printf("| Idle %d-%d ", endTime, processes[i + 1].arrivalTime);
            startTime = processes[i + 1].arrivalTime;
        }
    }
    printf("\n--------------------------------------------------------------------------------------------");
}

void priorityScheduling(struct Process processes[], int n, int ganttChart[]) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        int highestPriorityIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (processes[j].arrivalTime <= currentTime && processes[j].priority < processes[highestPriorityIndex].priority) {
                highestPriorityIndex = j;
            }
        }

        if (currentTime < processes[highestPriorityIndex].arrivalTime) {
            ganttChart[i] = 0;
            currentTime = processes[highestPriorityIndex].arrivalTime;
        }

        struct Process temp = processes[i];
        processes[i] = processes[highestPriorityIndex];
        processes[highestPriorityIndex] = temp;

        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        ganttChart[i] = processes[i].processID;
        currentTime = processes[i].completionTime;
    }
}

int main() {
    printf("+===========================+\n");
    printf("|  Priority Non-Preemptive  |\n");
    printf("+===========================+\n\n");

    int n = 5;

    struct Process processes[MAX_PROCESSES];
    int ganttChart[MAX_PROCESSES];
    
    for(int i = 0; i < n; i++){
        
        printf("Enter the Process ID: ");
        scanf("%d", &processes[i].processID);
        printf("Enter the Arrival Time of P%d: ", processes[i].processID);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter the Burst Time of P%d: ", processes[i].processID);
        scanf("%d", &processes[i].burstTime);
        printf("Enter the Priority of P%d: ", processes[i].processID);
        scanf("%d", &processes[i].priority);
        printf("\n");
    }
    // processes[0].processID = 1;
    // processes[0].arrivalTime = 4;
    // processes[0].burstTime = 4;
    // processes[0].priority = 3;

    // processes[1].processID = 2;
    // processes[1].arrivalTime = 8;
    // processes[1].burstTime = 9;
    // processes[1].priority = 1;

    // processes[2].processID = 3;
    // processes[2].arrivalTime = 3;
    // processes[2].burstTime = 4;
    // processes[2].priority = 2;

    // processes[3].processID = 4;
    // processes[3].arrivalTime = 6;
    // processes[3].burstTime = 7;
    // processes[3].priority = 4;

    // processes[4].processID = 5;
    // processes[4].arrivalTime = 0;
    // processes[4].burstTime = 6;
    // processes[4].priority = 1;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime ||
                (processes[j].arrivalTime == processes[j + 1].arrivalTime && processes[j].priority > processes[j + 1].priority)) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    priorityScheduling(processes, n, ganttChart);

    displayTable(processes, n, ganttChart);

    return 0;
}