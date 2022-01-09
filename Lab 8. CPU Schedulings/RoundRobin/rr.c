#include <stdio.h>

int main()
{
    int i, NOP, sum = 0, count = 0, y, quant, wt = 0, tat = 0;
    float avg_wt, avg_tat;

    printf("Total process \t>> ");
    scanf("%d", &NOP);

    int at[NOP], bt[NOP], temp[NOP];
    y = NOP; 

    for (i = 0; i < NOP; i++)
    {
        printf("Arrival Time %d \t>> ", i + 1); 
        scanf("%d", &at[i]);
        printf("Burst Time %d \t>> ", i + 1); 
        scanf("%d", &bt[i]);
        temp[i] = bt[i]; 
    }

    printf("Time Quantom \t>> ");
    scanf("%d", &quant);

    for (sum = 0, i = 0; y != 0;)
    {
        if (temp[i] <= quant && temp[i] > 0) 
        {
            sum = sum + temp[i];
            temp[i] = 0;
            count = 1;
        }
        else if (temp[i] > 0)
        {
            temp[i] = temp[i] - quant;
            sum = sum + quant;
        }
        if (temp[i] == 0 && count == 1)
        {
            y--; 
            printf("Process [%d]:\t\t\t Burst time:%d\t\t\t Turn around time:%d\t\t\t Waiting time:%d\n", i + 1, bt[i], sum - at[i], sum - at[i] - bt[i]);
            wt = wt + sum - at[i] - bt[i];
            tat = tat + sum - at[i];
            count = 0;
        }
        if (i == NOP - 1)
        {
            i = 0;
        }
        else if (at[i + 1] <= sum)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }

    avg_wt = wt * 1.0 / NOP;
    avg_tat = tat * 1.0 / NOP;
    printf("Average Turn Around Time: \t%f\n", avg_wt);
    printf("Average Waiting Time: \t\t%f\n", avg_tat);
    
    return 0;
}