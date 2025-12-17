#include <iostream>
#include <string>
using namespace std;

/*
    Node class represents a patient in the clinic
*/
class Node {
public:
    int patientID;
    string name;
    Node* next;

    Node(int id, string n) {
        patientID = id;
        name = n;
        next = NULL;
    }
};

/*
    List class manages the clinic waiting list
*/
class List {
private:
    Node* head;

public:
    // Constructor
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

    // Insert patient at the end (queue behavior)
    void InsertNode(int patientID, string name) {
        Node* newNode = new Node(patientID, name);

        // If list is empty
        if (head == NULL) {
            head = newNode;
            cout << "Patient added to waiting list.\n";
            return;
        }

        // Traverse to last node
        Node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = newNode;
        cout << "Patient added to waiting list.\n";
    }

    // Find patient by ID
    void FindNode(int patientID) {
        if (IsEmpty()) {
            cout << "Waiting list is empty.\n";
            return;
        }

        Node* current = head;
        while (current != NULL) {
            if (current->patientID == patientID) {
                cout << "Patient found: " << current->name << endl;
                return;
            }
            current = current->next;
        }

        cout << "Patient not found.\n";
    }

    // Delete patient by ID (or serve next patient if first node)
    void DeleteNode(int patientID) {
        if (IsEmpty()) {
            cout << "Waiting list is empty.\n";
            return;
        }

        // Case 1: delete first patient
        if (head->patientID == patientID) {
            Node* temp = head;
            head = head->next;
            cout << "Patient served/removed: " << temp->name << endl;
            delete temp;
            return;
        }

        // Case 2: delete from middle or end
        Node* current = head;
        while (current->next != NULL && current->next->patientID != patientID) {
            current = current->next;
        }

        if (current->next == NULL) {
            cout << "Patient not found.\n";
            return;
        }

        Node* temp = current->next;
        current->next = temp->next;
        cout << "Patient served/removed: " << temp->name << endl;
        delete temp;
    }

    // Display waiting list
    void DisplayList() {
        if (IsEmpty()) {
            cout << "Waiting list is empty.\n";
            return;
        }

        Node* current = head;
        cout << "Clinic Waiting List:\n";
        while (current != NULL) {
            cout << "[ID: " << current->patientID
                 << ", Name: " << current->name << "]";
            if (current->next != NULL)
                cout << " -> ";
            current = current->next;
        }
        cout << endl;
    }
};

/*
    Main function with menu-driven interface
*/
int main() {
    List clinic;
    int choice, patientID;
    string name;

    do {
        cout << "\n===== Clinic Waiting List Menu =====\n";
        cout << "1. Add Patient\n";
        cout << "2. Find Patient\n";
        cout << "3. Serve/Delete Patient\n";
        cout << "4. Display Waiting List\n";
        cout << "5. Check if List is Empty\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter patient ID: ";
            cin >> patientID;
            cout << "Enter patient name: ";
            cin.ignore();
            getline(cin, name);
            clinic.InsertNode(patientID, name);
            break;

        case 2:
            cout << "Enter patient ID to find: ";
            cin >> patientID;
            clinic.FindNode(patientID);
            break;

        case 3:
            cout << "Enter patient ID to serve/delete: ";
            cin >> patientID;
            clinic.DeleteNode(patientID);
            break;

        case 4:
            clinic.DisplayList();
            break;

        case 5:
            if (clinic.IsEmpty())
                cout << "Waiting list is empty.\n";
            else
                cout << "Waiting list is not empty.\n";
            break;

        case 6:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}