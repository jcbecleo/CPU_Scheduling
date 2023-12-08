#include<stdio.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};
void fcfs_scheduling(struct Process processes[], int n) {
    int i,j;
    for (i = 0; i < n - 1; i++) {`
        for (j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int completion_time = 0;

    for (i = 0; i < n; i++) {
        if (processes[i].arrival_time > completion_time) {
            completion_time = processes[i].arrival_time;
        }
        processes[i].completion_time = completion_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        completion_time = processes[i].completion_time;
    }
}

void display_gantt_chart(struct Process processes[], int n) {
    printf("\nGantt Chart:\n");
    printf("-----------\n");

    int i,j;
    for (i = 0; i < n; i++) {
        printf("|  P%d  ", processes[i].process_id);
    }
    printf("|\n");

    printf("0");
    for (i = 0; i < n; i++) {
        for (j = 0; j < processes[i].completion_time - 1; j++) {
            printf(" ");
        }
        printf("%d", processes[i].completion_time);

        int k;
        if (i < n - 1) {
            for (k = 0; k < processes[i + 1].completion_time - processes[i].completion_time - 1; k++) {
                printf(" ");
            }
        }
    }
    printf("\n\n");
}

int main() {
    int n;
    printf("+===============+\n");
    printf("  First Come First Serve\n");
    printf("+===============+\n\n");

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    int i;
    for (i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter arrival time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("\n");
    }
    fcfs_scheduling(processes, n);

    float avg_turnaround_time = 0, avg_waiting_time = 0;
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time,
               processes[i].waiting_time);

        avg_turnaround_time += processes[i].turnaround_time;
        avg_waiting_time += processes[i].waiting_time;
    }

    avg_turnaround_time /= n;
    avg_waiting_time /= n;

    printf("\nAverage Turnaround Time: %.2f", avg_turnaround_time);
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);

    display_gantt_chart(processes, n);

    return 0;
}