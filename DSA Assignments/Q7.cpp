#include <iostream>
#include <string>
using namespace std;

/*
    Node class represents a product in the inventory
*/
class Node {
public:
    int code;
    string name;
    int quantity;
    Node* next;

    Node(int c, string n, int q) {
        code = c;
        name = n;
        quantity = q;
        next = NULL;
    }
};

/*
    List class manages the product inventory
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

    // Check if inventory is empty
    bool IsEmpty() {
        return (head == NULL);
    }

    // Insert product at the end of the list
    void InsertNode(int code, string name, int quantity) {
        Node* newNode = new Node(code, name, quantity);

        // If list is empty
        if (head == NULL) {
            head = newNode;
            cout << "Product added successfully.\n";
            return;
        }

        // Traverse to the last node
        Node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = newNode;
        cout << "Product added successfully.\n";
    }

    // Find product by code
    void FindNode(int code) {
        if (IsEmpty()) {
            cout << "Inventory is empty.\n";
            return;
        }

        Node* current = head;
        while (current != NULL) {
            if (current->code == code) {
                cout << "Product Found:\n";
                cout << "Code: " << current->code
                     << " | Name: " << current->name
                     << " | Qty: " << current->quantity << endl;
                return;
            }
            current = current->next;
        }

        cout << "Product not found.\n";
    }

    // Delete product by code
    void DeleteNode(int code) {
        if (IsEmpty()) {
            cout << "Inventory is empty.\n";
            return;
        }

        // Case 1: delete first node
        if (head->code == code) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Product deleted successfully.\n";
            return;
        }

        // Case 2: delete from middle or end
        Node* current = head;
        while (current->next != NULL && current->next->code != code) {
            current = current->next;
        }

        if (current->next == NULL) {
            cout << "Product not found.\n";
            return;
        }

        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
        cout << "Product deleted successfully.\n";
    }

    // Display inventory list
    void DisplayList() {
        if (IsEmpty()) {
            cout << "Inventory is empty.\n";
            return;
        }

        Node* current = head;
        cout << "Product Inventory:\n";
        while (current != NULL) {
            cout << "Code: " << current->code
                 << " | Name: " << current->name
                 << " | Qty: " << current->quantity << endl;
            current = current->next;
        }
    }
};

/*
    Main function with menu-driven interface
*/
int main() {
    List inventory;
    int choice, code, quantity;
    string name;

    do {
        cout << "\n===== Product Inventory Menu =====\n";
        cout << "1. Add Product\n";
        cout << "2. Find Product\n";
        cout << "3. Delete Product\n";
        cout << "4. Display Inventory\n";
        cout << "5. Check if Inventory is Empty\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter product code: ";
            cin >> code;
            cout << "Enter product name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter quantity: ";
            cin >> quantity;
            inventory.InsertNode(code, name, quantity);
            break;

        case 2:
            cout << "Enter product code to find: ";
            cin >> code;
            inventory.FindNode(code);
            break;

        case 3:
            cout << "Enter product code to delete: ";
            cin >> code;
            inventory.DeleteNode(code);
            break;

        case 4:
            inventory.DisplayList();
            break;

        case 5:
            if (inventory.IsEmpty())
                cout << "Inventory is empty.\n";
            else
                cout << "Inventory is not empty.\n";
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