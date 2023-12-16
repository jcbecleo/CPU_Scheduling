#include <stdio.h>

int main() {
    // Input the number of processes
    printf("+===============+\n");
    printf("  Round Robin\n");
    printf("+===============+\n\n");
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int arrivalTime[n], burstTime[n], tempBurstTime[n];
    int remainingProcesses = n;

    // Input details of processes
    for (int i = 0; i < n; i++) {
        printf("\nArrival Time for Process %d: ", i + 1);
        scanf("%d", &arrivalTime[i]);
        printf("Burst Time for Process %d: ", i + 1);
        scanf("%d", &burstTime[i]);
        tempBurstTime[i] = burstTime[i];
    }

    // Input quantum time
    int quantumTime;
    printf("\nEnter Quantum Time: ");
    scanf("%d", &quantumTime);


    int turnaroundTime[n];
    int waitingTime[n];
    int endTime[n];

    int processIndex = 0;

    printf("\nGantt Chart:\n");
    printf("+-------------------------------------------------+\n");
    printf("|  Time  |  Process   | End Time  |\n");
    printf("+-------------------------------------------------+\n");

    int currentTime = 0;
    int tempCurrentTime = currentTime;


    while (remainingProcesses > 0) {
        if (tempBurstTime[processIndex] <= quantumTime && tempBurstTime[processIndex] > 0) {
            endTime[processIndex] = currentTime;
            currentTime = currentTime + tempBurstTime[processIndex];
            tempBurstTime[processIndex] = 0;
            printf("|  %-4d  |    P%-4d   |    %-6d |\n", tempCurrentTime, processIndex + 1, currentTime);
            tempCurrentTime = currentTime;
            
            
            turnaroundTime[processIndex] = endTime[processIndex] - arrivalTime[processIndex];
            waitingTime[processIndex] = turnaroundTime[processIndex] - burstTime[processIndex];
            
            remainingProcesses--;
        } else if (tempBurstTime[processIndex] > 0) {
            currentTime += quantumTime;
            tempBurstTime[processIndex] -= quantumTime;
            printf("|  %-4d  |    P%-4d   |    %-6d |\n", tempCurrentTime, processIndex + 1, currentTime);
            tempCurrentTime = currentTime;
        }

        processIndex = (processIndex + 1) % n;

        // Check for idle time between processes
        // if (remainingProcesses > 0 && currentTime < arrivalTime[processIndex]) {
        //     printf("|  %-4d  |   Idle    |    %-6d |\n", tempCurrentTime, arrivalTime[processIndex]);
        //     currentTime = arrivalTime[processIndex];
        //     tempCurrentTime = currentTime;
        // }
    }

    // Display the process table
    printf("\n+----------+------------+------------+----------+----------+------------+----------+\n");
    printf("| Process  |  Arrival   | Burst Time |   QT     | End Time | Turnaround | Waiting  |\n");
    printf("+----------+------------+------------+----------+----------+------------+----------+\n");
    int i;
    for (i = 0; i < n; i++) {
        printf("|  %-7d |     %-6d |     %-6d |     %-4d |     %-4d |     %-5d  |     %-4d |\n",
               i + 1, arrivalTime[i], burstTime[i],
               quantumTime, endTime[i],
               turnaroundTime[i],
               waitingTime[i]);
    }

    float averageWaitTime = 0;
    float averageTurnaroundTime = 0;

    for (i = 0; i < n; i++) {
        averageWaitTime += waitingTime[i];
        averageTurnaroundTime += turnaroundTime[i];
    }

    averageWaitTime /= n;
    averageTurnaroundTime /= n;

    printf("+----------------------------------------------------------------------------------+\n");
    printf("Average Waiting Time: %0.1f\n", averageWaitTime);
    printf("Average Turnaround Time: %0.1f\n", averageTurnaroundTime);

    return 0;

}