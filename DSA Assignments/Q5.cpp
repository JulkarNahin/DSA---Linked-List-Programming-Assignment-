#include <iostream>
using namespace std;

/*
    Node class represents a single train carriage
*/
class Node {
public:
    int carriageNo;
    int capacity;
    Node* next;

    Node(int cNo, int cap) {
        carriageNo = cNo;
        capacity = cap;
        next = NULL;
    }
};

/*
    List class manages the train as a singly linked list
*/
class List {
private:
    Node* head;

public:
    // Constructor: initialize empty list
    List() {
        head = NULL;
    }

    // Destructor: free all nodes
    ~List() {
        Node* temp;
        while (head != NULL) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Check if list is empty
    bool IsEmpty() {
        return (head == NULL);
    }

    // Insert node in ascending order of carriage number
    void InsertNode(int carriageNo, int capacity) {
        Node* newNode = new Node(carriageNo, capacity);

        // Case 1: empty list or insert at beginning
        if (head == NULL || carriageNo < head->carriageNo) {
            newNode->next = head;
            head = newNode;
            cout << "Carriage added successfully.\n";
            return;
        }

        // Case 2: insert in middle or end
        Node* current = head;
        while (current->next != NULL && current->next->carriageNo < carriageNo) {
            current = current->next;
        }

        // Prevent duplicate carriage numbers
        if (current->carriageNo == carriageNo ||
            (current->next != NULL && current->next->carriageNo == carriageNo)) {
            cout << "Carriage number already exists.\n";
            delete newNode;
            return;
        }

        newNode->next = current->next;
        current->next = newNode;

        cout << "Carriage added successfully.\n";
    }

    // Search for a carriage by number
    void FindNode(int carriageNo) {
        if (IsEmpty()) {
            cout << "Train is empty.\n";
            return;
        }

        Node* current = head;
        while (current != NULL) {
            if (current->carriageNo == carriageNo) {
                cout << "Carriage " << carriageNo
                     << " found with capacity " << current->capacity << ".\n";
                return;
            }
            current = current->next;
        }

        cout << "Carriage not found.\n";
    }

    // Delete a carriage by number
    void DeleteNode(int carriageNo) {
        if (IsEmpty()) {
            cout << "Train is empty.\n";
            return;
        }

        // Case 1: delete head
        if (head->carriageNo == carriageNo) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Carriage deleted successfully.\n";
            return;
        }

        // Case 2: delete from middle or end
        Node* current = head;
        while (current->next != NULL && current->next->carriageNo != carriageNo) {
            current = current->next;
        }

        if (current->next == NULL) {
            cout << "Carriage not found.\n";
            return;
        }

        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
        cout << "Carriage deleted successfully.\n";
    }

    // Display train layout
    void DisplayList() {
        if (IsEmpty()) {
            cout << "Train is empty.\n";
            return;
        }

        Node* current = head;
        cout << "Train Layout:\n";
        while (current != NULL) {
            cout << "Carriage " << current->carriageNo
                 << " (Capacity " << current->capacity << ")";
            if (current->next != NULL)
                cout << " -> ";
            current = current->next;
        }
        cout << endl;
    }
};

/*
    Main function with menu-driven system
*/
int main() {
    List train;
    int choice, carriageNo, capacity;

    do {
        cout << "\n===== Train Carriage Management =====\n";
        cout << "1. Add Carriage\n";
        cout << "2. Find Carriage\n";
        cout << "3. Delete Carriage\n";
        cout << "4. Display Train\n";
        cout << "5. Check if Train is Empty\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter carriage number: ";
            cin >> carriageNo;
            cout << "Enter capacity: ";
            cin >> capacity;
            train.InsertNode(carriageNo, capacity);
            break;

        case 2:
            cout << "Enter carriage number to find: ";
            cin >> carriageNo;
            train.FindNode(carriageNo);
            break;

        case 3:
            cout << "Enter carriage number to delete: ";
            cin >> carriageNo;
            train.DeleteNode(carriageNo);
            break;

        case 4:
            train.DisplayList();
            break;

        case 5:
            if (train.IsEmpty())
                cout << "Train is empty.\n";
            else
                cout << "Train is not empty.\n";
            break;

        case 6:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}