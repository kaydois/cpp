#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace std;

class Task {
public:
    string name;
    string description;
    int priority;
    bool completed;

    Task(string name, string description, int priority, bool completed)
        : name(name), description(description), priority(priority), completed(completed) {}
};

class TodoManager {
public:
    vector<Task> tasks;

    void RetrieveTasks() {
        if(!this->tasks.size()) cout << "No tasks found, type \"add\" to get started" << endl;
        for (int i = 0; i < tasks.size(); i++) {
            if (!tasks[i].completed) {
                cout << (i + 1) << ". " << tasks[i].name << " (" << tasks[i].description << ") [Priority: " << tasks[i].priority << "]" << endl;
            }
        }
    }

    void AddTask() {
        string name;
        string description;
        string priorityLevel;
        int priority;

        cout << "Enter task name: ";

        while (true) {
            getline(cin, name);
            if (name.empty()) {
                cout << "Please enter a name for the task" << endl;
                cout << "Enter task name: ";
            } else {
                break;
            }
        }

        cout << "Enter task description: ";
        while (true) {
            getline(cin, description);
            if (!description.empty()) {
                break;
            } else {
                cout << "For now, descriptions are required" << endl;
                cout << "Enter task description: ";
            }
        }

        cout << "Enter task priority level: ";
        while (true) {
            getline(cin, priorityLevel);
            try {
                priority = stoi(priorityLevel);
                if (priority >= 0) {
                    tasks.push_back(Task(name, description, priority, false));
                    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                        return a.priority < b.priority;
                    });
                    cout << "Successfully added the task" << endl;
                    cout << "Type \"list\" to see all tasks" << endl;
                    break;
                } else {
                    cout << "Invalid priority level. Priority level must be 0 or above" << endl;
                    cout << "Enter task priority level: ";
                }
            } catch (const invalid_argument& arg) {
                cout << "TypeError! " << arg.what() << endl;
                cout << "Please enter a positive number for the priority level: ";
            }
        }
    }

    void MarkTaskAsCompleted() {
        if (tasks.empty()) {
            cout << "No tasks added, type \"add\" to get started" << endl;
            return;
        }

        vector<Task*> tasksNotCompleted;
        for (auto& task : tasks) {
            if (!task.completed) {
                tasksNotCompleted.push_back(&task);
            }
        }

        cout << "Enter the corresponding number to the task you want to mark as completed" << endl;
        for (int i = 0; i < tasksNotCompleted.size(); i++) {
            cout << (i + 1) << ". " << tasksNotCompleted[i]->name << " (" << tasksNotCompleted[i]->description << ")" << endl;
        }

        while (true) {
            string response;
            getline(cin, response);
            try {
                int resp = stoi(response);
                if (resp > tasksNotCompleted.size() || resp < 1) {
                    cout << "Inputted number not in range" << endl;
                } else {
                    tasksNotCompleted[resp - 1]->completed = true;
                    cout << "Successfully marked the task as completed" << endl;
                    break;
                }
            } catch (const invalid_argument& invalidArg) {
                cout << "FatalError! " << invalidArg.what() << endl;
                cout << "Invalid number received" << endl;
                cout << "Enter the corresponding number to the task you want to mark as completed: ";
            }
        }
    }

    void RetrieveCompletedTasks() {
        bool hasCompletedTasks = false;
        for (const auto& task : tasks) {
            if (task.completed) {
                cout << task.name << " (" << task.description << ") [Priority: " << task.priority << "]" << endl;
                hasCompletedTasks = true;
            }
        }
        if (!hasCompletedTasks) {
            cout << "No completed tasks found." << endl;
        }
    }
};

int main() {
    TodoManager manager;

    while (true) {
        string input;
        getline(cin, input);

        if (input == "exit") {
            break;
        } else if (input == "help") {
            cout << "Available commands:" << endl;
            cout << "exit" << endl;
            cout << "list" << endl;
            cout << "mark" << endl;
            cout << "add" << endl;
            cout << "clear" << endl;
            cout << "cpts" << endl;
        } else if (input == "list") {
            manager.RetrieveTasks();
        } else if (input == "mark") {
            manager.MarkTaskAsCompleted();
        } else if (input == "add") {
            manager.AddTask();
        } else if (input == "clear") {
            system("cls");
        } else if (input == "cpts") {
            manager.RetrieveCompletedTasks();
        }
    }

    return 0;
}