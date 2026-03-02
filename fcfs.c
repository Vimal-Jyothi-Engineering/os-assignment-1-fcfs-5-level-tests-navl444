#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char pid[10];
    int arrival;
    int burst;
    int waiting;
    int turnaround;
    int original_index;
} Process;

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    Process p[100];
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].arrival, &p[i].burst);
        p[i].original_index = i;
    }

    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            // Extract numbers: "P1" becomes 1, "P10" becomes 10
            int id1 = atoi(&p[j].pid[1]);
            int id2 = atoi(&p[j+1].pid[1]);

            if(p[j].arrival > p[j+1].arrival || (p[j].arrival == p[j+1].arrival && id1 > id2)) {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int cur = 0;
    float tw = 0, tt = 0;
    for(int i = 0; i < n; i++) {
        if(cur < p[i].arrival) cur = p[i].arrival;
        p[i].waiting = cur - p[i].arrival;
        p[i].turnaround = p[i].waiting + p[i].burst;
        tw += p[i].waiting;
        tt += p[i].turnaround;
        cur += p[i].burst;
    }

    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(p[j].original_index > p[j+1].original_index) {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    printf("Waiting Time:\n");
    for(int i = 0; i < n; i++) printf("%s %d\n", p[i].pid, p[i].waiting);
    printf("Turnaround Time:\n");
    for(int i = 0; i < n; i++) printf("%s %d\n", p[i].pid, p[i].turnaround);
    printf("Average Waiting Time: %.2f\n", tw / (float)n);
    printf("Average Turnaround Time: %.2f\n", tt / (float)n);
    return 0;
}