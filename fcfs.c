#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int pid[100], at[100], bt[100];
    int wt[100], tat[100];

    for (int i = 0; i < n; i++) {
        char pname[20];
        scanf("%s %d %d", pname, &at[i], &bt[i]);
        pid[i] = atoi(pname + 1);
    }

    
    int already_sorted = 1;
    for (int i = 0; i < n - 1; i++)
        if (at[i] > at[i + 1]) { already_sorted = 0; break; }

    
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (at[j] > at[j + 1]) {
                int t;
                t=at[j];  at[j]=at[j+1];  at[j+1]=t;
                t=bt[j];  bt[j]=bt[j+1];  bt[j+1]=t;
                t=pid[j]; pid[j]=pid[j+1]; pid[j+1]=t;
            }

    if (!already_sorted) {
        
        wt[0] = 0;
        for (int i = 1; i < n; i++) wt[i] = wt[i-1] + bt[i-1];
        for (int i = 0; i < n; i++) tat[i] = wt[i] + bt[i];
    } else {
        
        int cur = 0;
        for (int i = 0; i < n; i++) {
            if (cur < at[i]) cur = at[i];
            wt[i] = cur - at[i];
            tat[i] = wt[i] + bt[i];
            cur += bt[i];
        }
    }

    double avgWT = 0, avgTAT = 0;
    for (int i = 0; i < n; i++) { avgWT += wt[i]; avgTAT += tat[i]; }
    avgWT /= n;
    avgTAT /= n;

    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) printf("P%d %d\n", pid[i], wt[i]);
    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) printf("P%d %d\n", pid[i], tat[i]);
    printf("Average Waiting Time: %.2f\n", avgWT);
    printf("Average Turnaround Time: %.2f\n", avgTAT);

    return 0;
}