#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Struct to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
};

// Function to calculate waiting time, turnaround time, and finish time for each process
void calculateWaitingTurnaroundFinishTime(vector<Process> &processes, int timeQuantum, vector<int> &waitingTime, vector<int> &turnaroundTime, vector<int> &finishTime) {
    int n = processes.size();
    queue<Process> readyQueue;
    int currentTime = 0;
    int remainingTime[n];

    fill(remainingTime, remainingTime + n, 0);

    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burst_time;
    }

    int completed = 0;
    int i = 0;
    
    while (completed < n) {
        Process current = processes[i];
        if (remainingTime[i] > 0) {
            int executeTime = min(timeQuantum, remainingTime[i]);
            currentTime += executeTime;
            remainingTime[i] -= executeTime;

            if (remainingTime[i] == 0) {
                completed++;
                finishTime[i] = currentTime;
                turnaroundTime[i] = finishTime[i] - current.arrival_time;
                waitingTime[i] = turnaroundTime[i] - current.burst_time;
            }

            for (int j = 0; j < n; j++) {
                if (j != i && processes[j].arrival_time <= currentTime && remainingTime[j] > 0) {
                    readyQueue.push(processes[j]);
                }
            }

            if (!readyQueue.empty()) {
                readyQueue.push(current);
                current = readyQueue.front();
                readyQueue.pop();
                i = current.id - 1;
            }
        }
        i = (i + 1) % n;
    }
}

// Function to display Gantt chart
void displayGanttChart(vector<Process> &processes, vector<int> &finishTime) {
    cout << "Gantt Chart:\n";
    int totalTime = 0;

    for (const Process &process : processes) {
        cout << "| P" << process.id << " ";
        for (int i = 0; i < process.burst_time; i++) {
            cout << " ";
        }
        totalTime += process.burst_time;
    }
    cout << "|\n";

    // Display timeline
    cout << "0 ";
    for (int time : finishTime) {
        cout << " " << time << " ";
    }
    cout << endl;
}

int main() {
    int n, timeQuantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the time quantum: ";
    cin >> timeQuantum;

    vector<Process> processes(n);
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> finishTime(n, 0);

    // Input process information
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
    }

    calculateWaitingTurnaroundFinishTime(processes, timeQuantum, waitingTime, turnaroundTime, finishTime);
    displayGanttChart(processes, finishTime);

    cout << "Process ID\tArrival Time\tBurst Time\tTurnaround Time\tFinish Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time
             << "\t\t" << processes[i].burst_time << "\t\t" << turnaroundTime[i]
             << "\t\t" << finishTime[i] << "\t\t" << waitingTime[i] << endl;
    }

    return 0;
}
