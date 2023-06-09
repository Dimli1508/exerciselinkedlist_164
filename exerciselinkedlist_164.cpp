#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int rollNumber;
    string name;
    Node* next;
};

class CircularLinkedList {
private:
    Node* LAST;

public:
    CircularLinkedList() {
        LAST = NULL;
    }

    void addNode();
    bool search(int rollno, Node** islamy, Node** dimas);
    bool listEmpty();
    bool delNode();
    void traverse();
};

void CircularLinkedList::addNode() {
    int rollNo;
    string name;
    cout << "Enter roll number: ";
    cin >> rollNo;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);

    Node* newnode = new Node();
    newnode->rollNumber = rollNo;
    newnode->name = name;

    if (LAST == NULL) { 
        newnode->next = newnode;
        LAST = newnode;
    }
    else if (newnode->rollNumber < LAST->rollNumber) { //step 1
        newnode->next = LAST->next;//step 2
        LAST->next = newnode;//step 3
    }
    else if (newnode->rollNumber > LAST->rollNumber) { //step 4
        newnode->next = LAST->next;//step 5
        LAST->next = newnode;//step 6
        LAST = newnode;//step 7
    }
    else { 
        Node* islamy = LAST->next;//step 8
        Node* dimas = LAST->next;
        while (dimas != LAST && dimas->rollNumber < newnode->rollNumber) {//step 9
            islamy = dimas;
            dimas = dimas->next;
        }
        islamy->next = newnode;//step 10
        newnode->next = dimas;
    }

    cout << "Record added successfully!" << endl;
}

bool CircularLinkedList::search(int rollno, Node** islamy, Node** dimas) {
    *islamy = LAST->next;
    *dimas = LAST->next;
    while (*dimas != LAST) {
        if (rollno == (*dimas)->rollNumber) {
            return true;
        }
        *islamy = *dimas;
        *dimas = (*dimas)->next;
    }
    if (rollno == LAST->rollNumber) {
        return true;
    }
    else {
        return false;
    }
}

bool CircularLinkedList::listEmpty() {
    return LAST == NULL;
}

bool CircularLinkedList::delNode() {
    if (listEmpty()) {
        cout << "\nList is empty\n";
        return false;
    }

    int rollNo;
    cout << "Enter the roll number to delete: ";
    cin >> rollNo;

    Node* islamy = NULL;// step 1
    Node* dimas = NULL;
    if (search(rollNo, &islamy, &dimas)) {//step 2
        if (islamy == dimas) { //step 3
            LAST = NULL;
            delete dimas;
        }
        else if (dimas == LAST) { //step 4
            islamy->next = LAST->next;//step 5
            delete LAST;
            LAST = islamy;
        }
        else { // step 6
            islamy->next = dimas->next;
            delete dimas;
        }
        cout << "Record deleted successfully!" << endl;
        return true;
    }
    else {
        cout << "Record not found!" << endl;
        return false;
    }
}

void CircularLinkedList::traverse() {
    if (listEmpty()) {
        cout << "\nList is empty\n";
    }
    else {
        cout << "\nRecords in the list are:\n";
        Node* dimasNode = LAST->next;
        while (dimasNode != LAST) {
            cout << dimasNode->rollNumber << " " << dimasNode->name << endl;
            dimasNode = dimasNode->next;
        }
        cout << LAST->rollNumber << " " << LAST->name << endl;
    }
}

int main() {
    CircularLinkedList obj;
    while (true) {
        try {
            cout << "\nMenu" << endl;
            cout << "1. Add a record to the list" << endl;
            cout << "2. Delete a record from the list" << endl;
            cout << "3. View all the records in the list" << endl;
            cout << "4. Exit" << endl;
            cout << "\nEnter your choice (1-4): "; //fixed typo
            char ch;
            cin >> ch;

            switch (ch) {
            case '1': {
                obj.addNode();
                break;
            }
            case '2': {
                obj.delNode();
                break;
            }
            case '3': {
                obj.traverse();
                break;
            }
            case '4': {
                return 0;
            }
            default: {
                cout << "Invalid option" << endl;
                break;
            }
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}
