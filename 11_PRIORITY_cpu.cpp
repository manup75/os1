#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Struct to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
};

// Comparison function for the priority queue (Preemptive)
struct ComparePriority {
    bool operator()(const Process& a, const Process& b) {
        return a.priority > b.priority;
    }
};

// Function for Preemptive Priority Scheduling
void preemptivePriorityScheduling(vector<Process>& processes, int n) {
    // Manually sort processes based on arrival time (earlier arrival first)
    sort(processes.begin(), processes.end(), [](Process& a, Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    int currentTime = 0;
    priority_queue<Process, vector<Process>, ComparePriority> readyQueue;
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> finishTime(n, 0);
    int completed = 0;

    while (completed < n) {
        // Add processes that have arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= currentTime && processes[i].burst_time > 0) {
                readyQueue.push(processes[i]);
            }
        }

        // Process the one with the highest priority (preemptive)
        if (!readyQueue.empty()) {
            Process current = readyQueue.top();
            readyQueue.pop();

            int remainingTime = current.burst_time;
            if (remainingTime > 1) {
                current.burst_time = remainingTime - 1;
                readyQueue.push(current);
            }

            int processId = current.id - 1;
            if (finishTime[processId] == 0) {
                finishTime[processId] = currentTime + 1;
                waitingTime[processId] = finishTime[processId] - processes[processId].arrival_time - processes[processId].burst_time;
                turnaroundTime[processId] = finishTime[processId] - processes[processId].arrival_time;
                completed++;
            }
            currentTime++;
        } else {
            currentTime++;
        }
    }

    // Display results
    cout << "Gantt Chart:\n";
    for (const Process& process : processes) {
        cout << "| P" << process.id << " ";
    }
    cout << "|\n";
    cout << "0 ";
    for (int time : finishTime) {
        cout << " " << time << " ";
    }
    cout << endl;

    cout << "Process ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tFinish Time\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" 
             << processes[i].priority << "\t\t" << waitingTime[i] << "\t\t" << turnaroundTime[i] << "\t\t" << finishTime[i] << endl;
    }
}

// Function for Non-Preemptive Priority Scheduling
void nonPreemptivePriorityScheduling(vector<Process>& processes, int n) {
    // Manually sort processes based on priority (higher priority first)
    sort(processes.begin(), processes.end(), [](Process& a, Process& b) {
        return a.priority > b.priority;
    });

    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> finishTime(n, 0);
    finishTime[0] = processes[0].burst_time;
    turnaroundTime[0] = processes[0].burst_time - processes[0].arrival_time;
    waitingTime[0] = turnaroundTime[0] - processes[0].burst_time;

    for (int i = 1; i < n; i++) {
        finishTime[i] = finishTime[i - 1] + processes[i].burst_time;
        turnaroundTime[i] = finishTime[i] - processes[i].arrival_time;
        waitingTime[i] = turnaroundTime[i] - processes[i].burst_time;
    }

    // Display results
    cout << "Gantt Chart:\n";
    int totalTime = 0;
    for (const Process& process : processes) {
        cout << "| P" << process.id << " ";
        for (int i = 0; i < process.burst_time; i++) {
            cout << " ";
        }
        totalTime += process.burst_time;
    }
    cout << "|\n";
    cout << "0 ";
    for (int time : finishTime) {
        cout << " " << time << " ";
    }
    cout << endl;

    cout << "Process ID\tArrival Time\tBurst Time\tPriority\tTurnaround Time\tFinish Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" 
             << processes[i].priority << "\t\t" << turnaroundTime[i] << "\t\t" << finishTime[i] << "\t\t" << waitingTime[i] << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process information
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
        cout << "Enter priority for process " << i + 1 << ": ";
        cin >> processes[i].priority;
    }


 


        cout << "\nPreemptive Priority Scheduling\n";
        preemptivePriorityScheduling(processes, n);
   
        cout << "\nNon-Preemptive Priority Scheduling\n";
        nonPreemptivePriorityScheduling(processes, n);
  
        
  

    return 0;
}
