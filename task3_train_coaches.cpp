#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Coach {
    int number;
    string type;
    int capacity;
    int passengers;
    Coach* next;
    Coach* prev;

    Coach(int n, const string& t, int c, int p)
        : number(n), type(t), capacity(c), passengers(p), next(nullptr), prev(nullptr) {}
};

class Train {
private:
    Coach* head;
    Coach* current;

    void printCoach(Coach* c) const {
        cout << "  Coach " << c->number << " | Type: " << c->type
             << " | Capacity: " << c->capacity
             << " | Passengers: " << c->passengers
             << " | Empty seats: " << c->capacity - c->passengers << "\n";
    }

    Coach* findCoach(int number) const {
        if (!head) return nullptr;
        Coach* temp = head;
        do {
            if (temp->number == number) return temp;
            temp = temp->next;
        } while (temp != head);
        return nullptr;
    }

    void removeNode(Coach* target) {
        if (target->next == target) {
            head = current = nullptr;
        } else {
            target->prev->next = target->next;
            target->next->prev = target->prev;
            if (target == head) head = target->next;
            if (target == current) current = target->next;
        }
        delete target;
    }

public:
    Train() : head(nullptr), current(nullptr) {}

    ~Train() {
        while (head) removeNode(head);
    }

    bool isEmpty() const { return head == nullptr; }

    void addCoach(int number, const string& type, int cap, int pass) {
        Coach* c = new Coach(number, type, cap, pass);
        if (isEmpty()) {
            c->next = c->prev = c;
            head = current = c;
        } else {
            Coach* tail = head->prev;
            c->prev = tail;
            c->next = head;
            tail->next = c;
            head->prev = c;
        }
        cout << "Coach " << number << " added.\n";
    }

    void insertAfter(int afterNumber, int number, const string& type, int cap, int pass) {
        Coach* pos = findCoach(afterNumber);
        if (!pos) {
            cout << "Coach " << afterNumber << " not found.\n";
            return;
        }
        Coach* c = new Coach(number, type, cap, pass);
        Coach* after = pos->next;
        c->prev = pos;
        c->next = after;
        pos->next = c;
        after->prev = c;
        cout << "Coach " << number << " inserted after coach " << afterNumber << ".\n";
    }

    void removeCoach(int number) {
        Coach* target = findCoach(number);
        if (!target) {
            cout << "Coach " << number << " not found.\n";
            return;
        }
        removeNode(target);
        cout << "Coach " << number << " removed.\n";
    }

    void moveForward() {
        if (isEmpty()) { cout << "Train is empty.\n"; return; }
        current = current->next;
        printCoach(current);
    }

    void moveBackward() {
        if (isEmpty()) { cout << "Train is empty.\n"; return; }
        current = current->prev;
        printCoach(current);
    }

    void displayClockwise() const {
        if (isEmpty()) { cout << "Train is empty.\n"; return; }
        Coach* temp = head;
        do {
            printCoach(temp);
            temp = temp->next;
        } while (temp != head);
    }

    void displayAntiClockwise() const {
        if (isEmpty()) { cout << "Train is empty.\n"; return; }
        Coach* temp = head->prev;
        Coach* start = temp;
        do {
            printCoach(temp);
            temp = temp->prev;
        } while (temp != start);
    }

    void search(int number) const {
        Coach* c = findCoach(number);
        if (c) printCoach(c);
        else cout << "Coach " << number << " not found.\n";
    }

    void maxAvailable() const {
        if (isEmpty()) { cout << "Train is empty.\n"; return; }
        Coach* best = head;
        Coach* temp = head->next;
        while (temp != head) {
            if (temp->capacity - temp->passengers > best->capacity - best->passengers)
                best = temp;
            temp = temp->next;
        }
        cout << "Coach with most empty seats:\n";
        printCoach(best);
    }

    void displayCurrent() const {
        if (isEmpty()) { cout << "Train is empty.\n"; return; }
        printCoach(current);
    }

    // swap next/prev on every node, then the old tail becomes the head
    void reverse() {
        if (isEmpty()) { cout << "Train is empty.\n"; return; }
        Coach* temp = head;
        do {
            Coach* nxt = temp->next;
            temp->next = temp->prev;
            temp->prev = nxt;
            temp = nxt;
        } while (temp != head);
        head = head->next;
        cout << "Train direction reversed.\n";
    }
};

int readInt(const string& prompt) {
    int x;
    cout << prompt;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number, try again: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return x;
}

string readLine(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

void readCoach(int& num, string& type, int& cap, int& pass) {
    num = readInt("Coach Number: ");
    type = readLine("Coach Type: ");
    cap = readInt("Passenger Capacity: ");
    pass = readInt("Current Passengers: ");
    while (pass > cap || pass < 0) {
        cout << "Passengers must be between 0 and " << cap << ".\n";
        pass = readInt("Current Passengers: ");
    }
}

int main() {
    Train train;
    int num, cap, pass;
    string type;

    int n = readInt("Enter number of coaches: ");
    for (int i = 0; i < n; i++) {
        cout << "\nCoach " << i + 1 << ":\n";
        readCoach(num, type, cap, pass);
        train.addCoach(num, type, cap, pass);
    }

    int choice;
    do {
        cout << "\n===== Train Coach System =====\n"
             << "1. Add Coach\n"
             << "2. Insert Coach After\n"
             << "3. Remove Coach\n"
             << "4. Move Forward\n"
             << "5. Move Backward\n"
             << "6. Display Train Clockwise\n"
             << "7. Display Train Anti-clockwise\n"
             << "8. Search Coach\n"
             << "9. Find Maximum Available Capacity\n"
             << "10. Display Current Coach\n"
             << "11. Reverse Train Direction\n"
             << "0. Exit\n";
        choice = readInt("Enter choice: ");

        switch (choice) {
            case 1:
                readCoach(num, type, cap, pass);
                train.addCoach(num, type, cap, pass);
                break;
            case 2: {
                int after = readInt("Insert after coach number: ");
                readCoach(num, type, cap, pass);
                train.insertAfter(after, num, type, cap, pass);
                break;
            }
            case 3: train.removeCoach(readInt("Coach number to remove: ")); break;
            case 4: train.moveForward(); break;
            case 5: train.moveBackward(); break;
            case 6: train.displayClockwise(); break;
            case 7: train.displayAntiClockwise(); break;
            case 8: train.search(readInt("Coach number to search: ")); break;
            case 9: train.maxAvailable(); break;
            case 10: train.displayCurrent(); break;
            case 11: train.reverse(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
