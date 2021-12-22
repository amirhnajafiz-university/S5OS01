#include <stdio.h>

// Struct of process 
struct process {
    int pid;
    int bt;
    int wt, tt;
};

int main() {
	// Number of processes 
    int n;
    scanf("%d", &n);
	
	// List of processes
    struct process processes[n];
	
	// Getting each process CPU burst time
    for(int i = 0; i < n; i++) {
		int temp;
        printf("%d >> ", i+1);
		
        scanf("%d", &temp);
		
		processes[i].pid = i;
		processes[i].bt = temp;
    }

	// Calculating the wait time and terminate time
    processes[0].wt = 0;
	processes[0].tt = processes[0].bt;
    for(int i = 1 ; i < n; i++) {
        processes[i].wt = processes[i-1].wt + processes[i-1].bt;
		processes[i].tt = processes[i].wt + processes[i].bt;
    }

	// Calculating the averages
    int wt_total, tt_total = 0;
    for(int i = 0; i < n; i++) {
        wt_total += processes[i].wt;
        tt_total += processes[i].tt;
    }
	
    float wt_avg = wt_total / n;
    float tt_avg = tt_total / n;


    printf("Waiting Time: %f\n", wt_avg);
    printf("Burst Time Average: %f\n", tt_avg);

    return 0;
}