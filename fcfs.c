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
    scanf("%d", &n);
    
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
        
        int completion_time = current_time + p[i].burst;
        p[i].turnaround = completion_time - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        
        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
        current_time = completion_time;
    }
    
    printf("Waiting Time: ");
    for(int i = 0; i < n; i++) {
        printf("%s %d ", p[i].pid, p[i].waiting);
    }
    
    printf("Turnaround Time: ");
    for(int i = 0; i < n; i++) {
        printf("%s %d ", p[i].pid, p[i].turnaround);
    }
    
    printf("Average Waiting Time: %.2f Average Turnaround Time: %.2f\n", total_wt / n, total_tat / n);
    
    return 0;
}