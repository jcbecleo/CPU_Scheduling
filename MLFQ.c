#include <stdio.h>

struct process
{
    char name;
    int AT, BT, WT, TAT, RT, CT;
} Q1[10], Q2[10], Q3[10]; /*Three queues*/

int n;

void sortByArrival()
{
    struct process temp;
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (Q1[i].AT > Q1[j].AT)
            {
                temp = Q1[i];
                Q1[i] = Q1[j];
                Q1[j] = temp;
            }
        }
    }
}

void displayTable(struct process queue[], int size)
{
    printf("\nProcess\tArrival Time\tBurst Time\tEnd Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < size; i++)
    {
        printf("%c\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", queue[i].name, queue[i].AT, queue[i].BT, queue[i].CT,
               queue[i].TAT, queue[i].WT);
    }
}

int main()
{
    int i, j, k = 0, r = 0, time = 0, tq1, tq2, flag = 0;
    char c;
    printf("Enter the number of processes:");
    scanf("%d", &n);

    for (i = 0, c = 'A'; i < n; i++, c++)
    {
        Q1[i].name = c;
        printf("\nEnter the arrival time of process %c: ", Q1[i].name);
        scanf("%d", &Q1[i].AT);
        printf("Enter the burst time of process %c: ", Q1[i].name);
        scanf("%d", &Q1[i].BT);
        Q1[i].RT = Q1[i].BT; /*save burst time in remaining time for each process*/
    }

    sortByArrival();

    printf("Enter the time quantum for Queue 1 (Round Robin): ");
    scanf("%d", &tq1);

    printf("Enter the time quantum for Queue 2 (Round Robin): ");
    scanf("%d", &tq2);

    time = Q1[0].AT;
    printf("\nProcess in the first queue following RR with quantum time %d", tq1);
    printf("\nProcess\t\tRT\t\tWT\t\tTAT\t\t");
    for (i = 0; i < n; i++)
    {
        if (Q1[i].RT <= tq1)
        {
            time += Q1[i].RT; /*from arrival time of the first process to completion of this process*/
            Q1[i].RT = 0;
            Q1[i].WT = time - Q1[i].AT - Q1[i].BT; /*amount of time the process has been waiting in the first queue*/
            Q1[i].TAT = time - Q1[i].AT;             /*amount of time to execute the process*/
            Q1[i].CT = time;
            printf("\n%c\t\t%d\t\t%d\t\t%d", Q1[i].name, Q1[i].BT, Q1[i].WT, Q1[i].TAT);
        }
        else /*process moves to queue 2 with qt=8*/
        {
            Q2[k].WT = time;
            time += tq1;
            Q1[i].RT -= tq1;
            Q2[k].BT = Q1[i].RT;
            Q2[k].RT = Q2[k].BT;
            Q2[k].name = Q1[i].name;
            k = k + 1;
            flag = 1;
        }
    }

    if (flag == 1)
    {
        printf("\nProcess in the second queue following RR with quantum time %d", tq2);
        printf("\nProcess\t\tRT\t\tWT\t\tTAT\t\t");
    }
    for (i = 0; i < k; i++)
    {
        if (Q2[i].RT <= tq2)
        {
            time += Q2[i].RT; /*from arrival time of the first process +BT of this process*/
            Q2[i].RT = 0;
            Q2[i].WT = time - tq1 - Q2[i].BT; /*amount of time the process has been waiting in the ready queue*/
            Q2[i].TAT = time - Q2[i].AT;       /*amount of time to execute the process*/
            Q2[i].CT = time;
            printf("\n%c\t\t%d\t\t%d\t\t%d", Q2[i].name, Q2[i].BT, Q2[i].WT, Q2[i].TAT);
        }
        else /*process moves to queue 3 with FCFS*/
        {
            Q3[r].AT = time;
            time += tq2;
            Q2[i].RT -= tq2;
            Q3[r].BT = Q2[i].RT;
            Q3[r].RT = Q3[r].BT;
            Q3[r].name = Q2[i].name;
            r = r + 1;
            flag = 2;
        }
    }

    if (flag == 2)
    {
        printf("\nProcess in the third queue following FCFS ");
    }
    for (i = 0; i < r; i++)
    {
        if (i == 0)
            Q3[i].CT = Q3[i].BT + time - tq1 - tq2;
        else
            Q3[i].CT = Q3[i - 1].CT + Q3[i].BT;
    }

    for (i = 0; i < r; i++)
    {
        Q3[i].TAT = Q3[i].CT;
        Q3[i].WT = Q3[i].TAT - Q3[i].BT;
    }

    printf("\n\nGantt Chart:\n");
    printf(" ");
    for (i = 0; i < n; i++)
    {
        printf("--------");
    }
    printf("\n|");
    for (i = 0; i < n; i++)
    {
        printf("   %c   |", Q1[i].name);
    }
    printf("\n ");
    for (i = 0; i < n; i++)
    {
        printf("--------");
    }
    printf("\n0");
    for (i = 0; i < n; i++)
    {
        printf("       %d", Q1[i].CT);
    }

    displayTable(Q1, n);
    displayTable(Q2, k);
    displayTable(Q3, r);

    return 0;
}