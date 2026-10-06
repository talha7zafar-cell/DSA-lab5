#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Photo {
    int id;
    string name;
    string date;
    string location;
    Photo* next;
    Photo* prev;

    Photo(int i, const string& n, const string& d, const string& l)
        : id(i), name(n), date(d), location(l), next(nullptr), prev(nullptr) {}
};

class Album {
private:
    Photo* head;
    Photo* current;

    void printPhoto(Photo* p) const {
        cout << "  [ID: " << p->id << "] " << p->name
             << " | Date: " << p->date << " | Location: " << p->location << "\n";
    }

    Photo* findById(int id) const {
        if (!head) return nullptr;
        Photo* temp = head;
        do {
            if (temp->id == id) return temp;
            temp = temp->next;
        } while (temp != head);
        return nullptr;
    }

    void removeNode(Photo* target) {
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
    Album() : head(nullptr), current(nullptr) {}

    ~Album() {
        while (head) removeNode(head);
    }

    bool isEmpty() const { return head == nullptr; }

    void addPhoto(int id, const string& name, const string& date, const string& loc) {
        Photo* p = new Photo(id, name, date, loc);
        if (isEmpty()) {
            p->next = p->prev = p;
            head = current = p;
        } else {
            Photo* tail = head->prev;
            p->prev = tail;
            p->next = head;
            tail->next = p;
            head->prev = p;
        }
        cout << "Photo " << id << " added.\n";
    }

    void insertAfterCurrent(int id, const string& name, const string& date, const string& loc) {
        if (isEmpty()) {
            addPhoto(id, name, date, loc);
            return;
        }
        Photo* p = new Photo(id, name, date, loc);
        Photo* after = current->next;
        p->prev = current;
        p->next = after;
        current->next = p;
        after->prev = p;
        cout << "Photo " << id << " inserted after current.\n";
    }

    void removeById(int id) {
        Photo* target = findById(id);
        if (!target) {
            cout << "Photo " << id << " not found.\n";
            return;
        }
        removeNode(target);
        cout << "Photo " << id << " removed.\n";
    }

    void removeCurrent() {
        if (isEmpty()) { cout << "Album is empty.\n"; return; }
        int id = current->id;
        removeNode(current);
        cout << "Photo " << id << " removed.\n";
    }

    void moveNext() {
        if (isEmpty()) { cout << "Album is empty.\n"; return; }
        current = current->next;
        printPhoto(current);
    }

    void movePrevious() {
        if (isEmpty()) { cout << "Album is empty.\n"; return; }
        current = current->prev;
        printPhoto(current);
    }

    void displayForward() const {
        if (isEmpty()) { cout << "Album is empty.\n"; return; }
        Photo* temp = current;
        do {
            printPhoto(temp);
            temp = temp->next;
        } while (temp != current);
    }

    void displayBackward() const {
        if (isEmpty()) { cout << "Album is empty.\n"; return; }
        Photo* temp = current;
        do {
            printPhoto(temp);
            temp = temp->prev;
        } while (temp != current);
    }

    void search(int id) const {
        Photo* p = findById(id);
        if (p) printPhoto(p);
        else cout << "Photo " << id << " not found.\n";
    }

    int count() const {
        if (isEmpty()) return 0;
        int c = 0;
        Photo* temp = head;
        do {
            c++;
            temp = temp->next;
        } while (temp != head);
        return c;
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

void readPhoto(int& id, string& name, string& date, string& loc) {
    id = readInt("Photo ID: ");
    name = readLine("Photo Name: ");
    date = readLine("Date Taken: ");
    loc = readLine("Location: ");
}

int main() {
    Album album;
    int id;
    string name, date, loc;

    int n = readInt("Enter number of photos: ");
    for (int i = 0; i < n; i++) {
        cout << "\nPhoto " << i + 1 << ":\n";
        readPhoto(id, name, date, loc);
        album.addPhoto(id, name, date, loc);
    }

    int choice;
    do {
        cout << "\n===== Photo Album =====\n"
             << "1. Add Photo\n"
             << "2. Insert Photo After Current\n"
             << "3. Remove Photo by ID\n"
             << "4. Remove Current Photo\n"
             << "5. Move Next\n"
             << "6. Move Previous\n"
             << "7. Display Album Forward\n"
             << "8. Display Album Backward\n"
             << "9. Search Photo\n"
             << "10. Count Photos\n"
             << "0. Exit\n";
        choice = readInt("Enter choice: ");

        switch (choice) {
            case 1: readPhoto(id, name, date, loc); album.addPhoto(id, name, date, loc); break;
            case 2: readPhoto(id, name, date, loc); album.insertAfterCurrent(id, name, date, loc); break;
            case 3: album.removeById(readInt("Photo ID to remove: ")); break;
            case 4: album.removeCurrent(); break;
            case 5: album.moveNext(); break;
            case 6: album.movePrevious(); break;
            case 7: album.displayForward(); break;
            case 8: album.displayBackward(); break;
            case 9: album.search(readInt("Photo ID to search: ")); break;
            case 10: cout << "Total photos: " << album.count() << "\n"; break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
