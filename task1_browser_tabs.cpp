// Lab 5 - Task 1: Browser Tab Manager
// Circular Doubly Linked List (CDLL)

#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Tab {
    int id;
    string title;
    string url;
    Tab* next;
    Tab* prev;

    
 Tab ( int id , string title, string url)
 {
    this->id = id;
    this->title = title;
    this->url = url;
    this->next = nullptr;
    this->prev = nullptr;
 }

};

//Tab Manager (CDLL) 
class TabManager {
private:
    Tab* current;   // active tab; nullptr means no tabs are open

    void printTab(Tab* t) const {
        cout << "  [ID: " << t->id << "] " << t->title << "  (" << t->url << ")\n";
    }

public:
    TabManager() : current(nullptr) {}

    // Free every node when the program ends
    ~TabManager() {
        while (current != nullptr) {
            closeCurrentTab(false);
        }
    }

    bool isEmpty() const { return current == nullptr; }

    // 1. Open New Tab - insert AFTER current; new tab becomes current
    void openNewTab(int id, const string& title, const string& url) {
        Tab* newTab = new Tab(id, title, url);

        if (isEmpty()) {
            // Single node points to itself in both directions
            newTab->next = newTab;
            newTab->prev = newTab;
        } else {
            Tab* after = current->next;   // node that will follow newTab

            newTab->prev = current;
            newTab->next = after;
            current->next = newTab;
            after->prev = newTab;
        }
        current = newTab;   // a newly opened tab becomes the active one
        cout << "Opened tab " << id << ".\n";
    }

    // 2. Close Current Tab 
    void closeCurrentTab(bool verbose = true) {
        if (isEmpty()) {
            if (verbose) cout << "No tabs open.\n";
            return;
        }

        Tab* toDelete = current;

        if (current->next == current) {
            // It was the only tab, so the list becomes empty
            current = nullptr;
        } else {
            // Unlink: connect prev and next directly to each other
            current->prev->next = current->next;
            current->next->prev = current->prev;
            current = current->next;
        }

        if (verbose) cout << "Closed tab " << toDelete->id << ".\n";
        delete toDelete;
    }

    // 3. Move Next
    void moveNext() {
        if (isEmpty()) { cout << "No tabs open.\n"; return; }
        current = current->next;
        cout << "Switched to:\n";
        printTab(current);
    }

    // 4. Move Previous
    void movePrevious() {
        if (isEmpty()) { cout << "No tabs open.\n"; return; }
        current = current->prev;
        cout << "Switched to:\n";
        printTab(current);
    }

    // 5. Display Current Tab
    void displayCurrent() const {
        if (isEmpty()) { cout << "No tabs open.\n"; return; }
        cout << "Current tab:\n";
        printTab(current);
    }

    // 6. Display All Tabs Forward
    void displayForward() const {
        if (isEmpty()) { cout << "No tabs open.\n"; return; }
        cout << "Tabs (forward):\n";
        Tab* temp = current;
        do {
            printTab(temp);
            temp = temp->next;
        } while (temp != current);
    }

    // 7. Display All Tabs Backward
    void displayBackward() const {
        if (isEmpty()) { cout << "No tabs open.\n"; return; }
        cout << "Tabs (backward):\n";
        Tab* temp = current;
        do {
            printTab(temp);
            temp = temp->prev;
        } while (temp != current);
    }

    // 8. Search Tab by ID
    void searchTab(int id) const {
        if (isEmpty()) { cout << "No tabs open.\n"; return; }
        Tab* temp = current;
        do {
            if (temp->id == id) {
                cout << "Tab found:\n";
                printTab(temp);
                return;
            }
            temp = temp->next;
        } while (temp != current);
        cout << "Tab with ID " << id << " not found.\n";
    }
};

//  Input helpers
int readInt(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number, try again: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

string readLine(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

//  Main menu 
int main() {
    TabManager browser;
    int choice;

    do {
        cout << "\n===== Browser Tab Manager =====\n"
             << "1. Open New Tab\n"
             << "2. Close Current Tab\n"
             << "3. Move Next\n"
             << "4. Move Previous\n"
             << "5. Display Current Tab\n"
             << "6. Display All Tabs Forward\n"
             << "7. Display All Tabs Backward\n"
             << "8. Search Tab\n"
             << "0. Exit\n";
        choice = readInt("Enter choice: ");

        switch (choice) {
            case 1: {
                int id = readInt("Tab ID: ");
                string title = readLine("Website Title: ");
                string url = readLine("URL: ");
                browser.openNewTab(id, title, url);
                break;
            }
            case 2: browser.closeCurrentTab(); break;
            case 3: browser.moveNext(); break;
            case 4: browser.movePrevious(); break;
            case 5: browser.displayCurrent(); break;
            case 6: browser.displayForward(); break;
            case 7: browser.displayBackward(); break;
            case 8: browser.searchTab(readInt("Enter Tab ID to search: ")); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;   // destructor frees all remaining tabs
}
