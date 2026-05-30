#include <stdio.h>

// Function to print Gantt Chart
void ganttChart(int order[], int time[], int k)
{
    printf("\nGantt Chart:\n|");
    for(int i = 0; i < k; i++)
        printf(" P%d |", order[i]);

    printf("\n%d", time[0]);
    for(int i = 1; i <= k; i++)
        printf("   %d", time[i]);
    printf("\n");
}

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], pr[n];
    int ct[n], tat[n], wt[n], rt[n];
    int visited[n], pid[n];
    int order[n], timeLine[n + 1];

    int time = 0, completed = 0, k = 0;
    float avgTAT = 0, avgWT = 0, avgRT = 0;

    // Input
    for(int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        visited[i] = 0;

        printf("\nArrival Time for P%d: ", i + 1);
        scanf("%d", &at[i]);

        printf("Burst Time for P%d: ", i + 1);
        scanf("%d", &bt[i]);

        printf("Priority for P%d (Lower number = Higher priority): ", i + 1);
        scanf("%d", &pr[i]);
    }

    timeLine[0] = 0;

    while(completed < n)
    {
        int index = -1;
        int highestPriority = 9999;

        for(int i = 0; i < n; i++)
        {
            if(at[i] <= time && visited[i] == 0)
            {
                if(pr[i] < highestPriority)
                {
                    highestPriority = pr[i];
                    index = i;
                }
                else if(pr[i] == highestPriority)
                {
                    // FCFS among same priority
                    if(at[i] < at[index])
                    {
                        index = i;
                    }
                }
            }
        }

        if(index != -1)
        {
            order[k] = pid[index];

            rt[index] = time - at[index];

            time += bt[index];

            ct[index] = time;
            tat[index] = ct[index] - at[index];
            wt[index] = tat[index] - bt[index];

            timeLine[k + 1] = time;

            avgTAT += tat[index];
            avgWT += wt[index];
            avgRT += rt[index];

            visited[index] = 1;
            completed++;
            k++;
        }
        else
        {
            time++;   // CPU Idle
        }
    }

    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], pr[i],
               ct[i], tat[i], wt[i], rt[i]);
    }

    ganttChart(order, timeLine, k);

    printf("\nAverage Turnaround Time = %.2f", avgTAT / n);
    printf("\nAverage Waiting Time    = %.2f", avgWT / n);
    printf("\nAverage Response Time   = %.2f\n", avgRT / n);

    return 0;
}