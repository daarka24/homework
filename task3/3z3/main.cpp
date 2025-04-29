#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


struct Task {
    string description;
    int priority;
};


vector<Task> tasks;


void addTask() {
    Task newTask;
    cout << "Enter task name: ";
    cin.ignore();
    getline(cin, newTask.description);

    cout << "Enter priority (1 - low, 10 - high): ";
    cin >> newTask.priority;

    tasks.push_back(newTask);
    cout << "Task added!\n";
}


void showTasks() {
    if (tasks.empty()) {
        cout << "No tasks yet.\n";
        return;
    }

    cout << "\nYour tasks:\n";
    for (size_t i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ") " << tasks[i].description << " (priority " << tasks[i].priority << ")\n";
    }
}


void completeTask() {
    if (tasks.empty()) {
        cout << "No tasks to complete.\n";
        return;
    }

    int num;
    cout << "Enter task number to complete (1 to " << tasks.size() << "): ";
    cin >> num;

    if (num < 1 || num >(int)tasks.size()) {
        cout << "Invalid task number!\n";
        return;
    }

    cout << "Task completed: " << tasks[num - 1].description << "\n";

    tasks.erase(tasks.begin() + (num - 1));
}


void readTasksFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "No existing task file found. Starting fresh.\n";
        return;
    }

    Task task;
    while (getline(inFile, task.description)) {
        inFile >> task.priority;
        inFile.ignore(); 
        tasks.push_back(task);
    }

    inFile.close();
    cout << "Tasks loaded from file.\n";
}


void saveTasksToFile(const string& filename) {
    ofstream outFile(filename);
    for (const auto& task : tasks) {
        outFile << task.description << endl << task.priority << endl;
    }
    outFile.close();
    cout << "Tasks saved to file.\n";
}

int main() {
    string filename = "tasks.txt"; 

    
    char loadFromFile;
    cout << "Do you want to load tasks from file? (y/n): ";
    cin >> loadFromFile;

    if (loadFromFile == 'y' || loadFromFile == 'Y') {
        
        readTasksFromFile(filename);
    }
    else {
        cout << "Starting with an empty task list.\n";
    }

    int choice;

    do {
        cout << "\n===== TASK MANAGER =====\n";
        cout << "1. Add task\n";
        cout << "2. Show tasks\n";
        cout << "3. Complete task\n";
        cout << "4. Save tasks\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
        case 1: addTask(); break;
        case 2: showTasks(); break;
        case 3: completeTask(); break;
        case 4: saveTasksToFile(filename); break;
        case 0: cout << "Goodbye!\n"; break;
        default: cout << "Wrong choice!\n";
        }
    } while (choice != 0);

    
    saveTasksToFile(filename);

    return 0;
}
