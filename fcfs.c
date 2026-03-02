#include <stdio.h>
#include <string.h>

typedef struct {
    char pid[10];
    int arrival;
    int burst;
    int waiting;
    int turnaround;
} Process;

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    Process p[n];
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].arrival, &p[i].burst);
    }
    
    
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(p[j].arrival > p[j+1].arrival) {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    
    int current_time = 0;
    float total_wt = 0, total_tat = 0;
    
    for(int i = 0; i < n; i++) {
        if(current_time < p[i].arrival) {
            current_time = p[i].arrival;
        }
        p[i].waiting = current_time - p[i].arrival;
        p[i].turnaround = p[i].waiting + p[i].burst;
        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
        current_time += p[i].burst;
    }
    
   
    printf("Waiting Time: ");
    for(int i = 0; i < n; i++) {
        printf("%s %d%s", p[i].pid, p[i].waiting, (i == n - 1) ? "" : " ");
    }
    printf("\n");

    
    printf("Turnaround Time: ");
    for(int i = 0; i < n; i++) {
        printf("%s %d%s", p[i].pid, p[i].turnaround, (i == n - 1) ? "" : " ");
    }
    printf("\n");

   
    printf("Average Waiting Time: %.2f Average Turnaround Time: %.2f\n", total_wt / n, total_tat / n);
    
    return 0;
}