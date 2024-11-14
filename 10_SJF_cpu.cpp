#include <stdio.h>
#include <iostream>
using namespace std;

struct node {
    int fin_time, proc_num, burst_time, arrival_time, wait_time, ta_time;
} o[50];

void bubblesort(struct node t[], int nu) {
    struct node swap;
    int i, j;
    for (i = 0; i < nu - 1; i++) {
        for (j = 0; j < nu - 1; j++) {
            if (t[j].burst_time > t[j + 1].burst_time) {
                swap = t[j];
                t[j] = t[j + 1];
                t[j + 1] = swap;
            }
        }
    }
}

void bubblesort2(struct node t[], int nu) {
    struct node swap;
    int i, j;
    for (i = 0; i < nu - 1; i++) {
        for (j = 0; j < nu - 1; j++) {
            if (t[j].fin_time > t[j + 1].fin_time) {
                swap = t[j];
                t[j] = t[j + 1];
                t[j + 1] = swap;
            }
        }
    }
}

int get_smallest(int a[], int n, int bt[]) {
    int smallest = 9999, index;
    for (int i = 0; i < n; i++) {
        if (bt[a[i]] <= smallest) {
            index = a[i];
            smallest = bt[a[i]];
        }
    }
    return index;
}

void sjf_non_preemptive(int n) {
    int i, j, flag[10] = {0}, count = 0;
    int fin_tim = 0;
    cout << "\nSJF Non Preemptive:" << endl;
    cout << "\nYou have entered the following details:" << endl;
    cout << "\nP_ID\tAT\tBT" << endl;
    for (i = 0; i < n; i++) {
        cout << o[i].proc_num << "\t" << o[i].arrival_time << "\t" << o[i].burst_time << endl;
    }

    bubblesort(o, n); // Sorting by burst time

    while (count != n) {
        bool progress = false;
        for (i = 0; i < n; i++) {
            // Find the process that has arrived and not yet completed
            if (o[i].arrival_time <= fin_tim && flag[i] != 1) {
                flag[i] = 1;  // Mark process as completed
                fin_tim += o[i].burst_time; // Update the finish time
                o[i].fin_time = fin_tim;
                o[i].ta_time = o[i].fin_time - o[i].arrival_time;  // Turnaround time
                o[i].wait_time = o[i].ta_time - o[i].burst_time;  // Waiting time
                count++; // Increment completed processes
                progress = true;
                break;
            }
        }

        // If no progress was made in the loop, break to avoid infinite loop
        if (!progress) {
            break;
        }
    }

    // Sort by finish time for displaying the results
    bubblesort2(o, n);

    cout << "\nThe resultant process scheduling is as follows:\nP_ID\tAT\tBT\tFT\tTT\tWT\n";
    for (i = 0; i < n; i++) {
        cout << o[i].proc_num << "\t" << o[i].arrival_time << "\t" << o[i].burst_time << "\t"
             << o[i].fin_time << "\t" << o[i].ta_time << "\t" << o[i].wait_time << endl;
    }
}

void sjf_preemptive(int n) {
    int i, j, indexes[45], k = 0, flag[10] = {0}, count = 0, bt[50], gchart[200];
    cout << "\nSJF Preemptive:" << endl;
    cout << "\nYou have entered the following details:" << endl;
    cout << "\nP_ID\tAT\tBT" << endl;
    for (i = 0; i < n; i++) {
        cout << o[i].proc_num << "\t" << o[i].arrival_time << "\t" << o[i].burst_time << endl;
        bt[i] = o[i].burst_time;
    }

    bubblesort(o, n); // Sorting by burst time
    int fin_tim = 0;

    for (i = 0; i < n; i++) {
        if (o[i].arrival_time == 0) {
            gchart[k] = o[i].proc_num;
            k++;
            flag[i] = 1;
            fin_tim += 1;
            bt[i] = bt[i] - 1;
            if (bt[i] == 0) {
                count += 1;
                o[i].fin_time = fin_tim;
                o[i].ta_time = o[i].fin_time - o[i].arrival_time;
                o[i].wait_time = o[i].ta_time - o[i].burst_time;
            }
            break;
        }
    }

    int g, ind;
    while (count != n) {
        g = 0;
        for (i = 0; i < n; i++) {
            if ((o[i].arrival_time <= fin_tim) && (bt[i] != 0)) {
                indexes[g] = i;
                g++;
            }
        }

        ind = get_smallest(indexes, g, bt);
        gchart[k] = o[ind].proc_num;
        k++;
        flag[ind] = 1;
        fin_tim += 1;
        bt[ind] = bt[ind] - 1;
        if (bt[ind] == 0) {
            count += 1;
            o[ind].fin_time = fin_tim;
            o[ind].ta_time = o[ind].fin_time - o[ind].arrival_time;
            o[ind].wait_time = o[ind].ta_time - o[ind].burst_time;
        }
    }

    cout << "\nGantt Chart:\n ";
    for (i = 0; i < k; i++) {
        cout << gchart[i] << " ";
    }
    cout << endl;

    cout << "\nThe resultant process scheduling is as follows:\nP_ID\tAT\tBT\tFT\tTT\tWT\n";
    for (i = 0; i < n; i++) {
        cout << o[i].proc_num << "\t" << o[i].arrival_time << "\t" << o[i].burst_time << "\t"
             << o[i].fin_time << "\t" << o[i].ta_time << "\t" << o[i].wait_time << endl;
    }
}

int main() {
    int n, choice;
    cout << "Enter number of processes:\t";
    cin >> n;
    cout << "Enter the burst time and arrival time of respective processes:\n";
    for (int i = 0; i < n; i++) {
        o[i].proc_num = i;
        cout << "Enter arrival time for process " << i << " :\t";
        cin >> o[i].arrival_time;
        cout << "Enter burst time for process " << i << " :\t";
        cin >> o[i].burst_time;
    }

    // Non-Preemptive SJF
    sjf_non_preemptive(n);

    // Uncomment the following line if you want to run preemptive SJF as well
    sjf_preemptive(n);

    return 0;
}
