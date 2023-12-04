#include <stdio.h>
#include <stdlib.h>

struct Process {
  int processID;
  int arrivalTime;
  int burstTime;
  int remainingTime;
  int priority;
  int completionTime;
  int turnaroundTime;
  int waitingTime;
};

void priorityScheduling(struct Process processes[], int n) {
  int currentTime = 0;
  int completed = 0;

  while (completed < n) {
    int highestPriority = -1;
    int selectedProcess = -1;

    for (int i = 0; i < n; i++) {
      if (processes[i].arrivalTime <= currentTime && processes[i].completionTime == 0) {
        if (highestPriority == -1 || processes[i].priority < highestPriority) {
          highestPriority = processes[i].priority;
          selectedProcess = i;
        }
      }
    }

    if (selectedProcess != -1) {
      
      if (processes[selectedProcess].completionTime == -1) {
        processes[selectedProcess].waitingTime = currentTime - processes[selectedProcess].arrivalTime;
    }

      int runTime = 1;
      if (processes[selectedProcess].remainingTime < 1) {
        runTime = processes[selectedProcess].remainingTime;
      }
      
      printf("| P%d %d-%d ", processes[selectedProcess].processID, currentTime, currentTime + runTime);
      
      processes[selectedProcess].remainingTime -= runTime;
      currentTime += runTime;

      if (processes[selectedProcess].remainingTime == 0) {
        processes[selectedProcess].completionTime = currentTime;
        processes[selectedProcess].turnaroundTime = processes[selectedProcess].completionTime - processes[selectedProcess].arrivalTime;
        completed++;
      }
    } else {
      printf("| Idle %d-%d ", currentTime, currentTime + 1);
      currentTime++;
    }
  }
}

void calculateAverages(struct Process processes[], int n, float *avgTurnaround, float *avgWaiting) {
  *avgTurnaround = 0;
  *avgWaiting = 0;

  for (int i = 0; i < n; i++) {
    *avgTurnaround += processes[i].turnaroundTime;
    *avgWaiting += processes[i].waitingTime;
  }

  *avgTurnaround = *avgTurnaround / n;
  *avgWaiting = *avgWaiting / n;
}


int main() {
    printf("+===============+\n");
    printf("  Priority Preemptive\n");
    printf("+===============+\n\n");
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
    processes[i].completionTime = -1;
    }

    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        printf("Enter priority for process P%d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].completionTime = 0;
        processes[i].turnaroundTime = 0;
        processes[i].waitingTime = 0;
    }

    printf("\nGantt Chart:\n");
    priorityScheduling(processes, n);

    float avgTurnaround, avgWaiting;
    calculateAverages(processes, n, &avgTurnaround, &avgWaiting);

    printf("\nProcess\t Arrival Time\t Burst Time\t Priority\t Completion Time\t Turnaround Time\t Waiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t %d\t\t %d\t\t %d\t\t %d\t\t\t %d\t\t\t %d\n", processes[i].processID, processes[i].arrivalTime, processes[i].burstTime, processes[i].priority, processes[i].completionTime, processes[i].turnaroundTime, processes[i].waitingTime);
    }

    printf("\nAverage Turnaround Time: %.2f\n", avgTurnaround);
    printf("Average Waiting Time: %.2f\n", avgWaiting);

    return 0;
}