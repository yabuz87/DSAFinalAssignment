#include <iostream>
#include <limits>

using namespace std;

// Colors
const string RED = "\033[31m";    // Red color
const string GREEN = "\033[32m";  // Green color
const string YELLOW = "\033[33m"; // Yellow color
const string BLUE = "\033[34m";   // Blue color
const string RESET = "\033[0m";
const string WHITE = "\033[37m";  // White color
const string ORANGE = "\033[38;5;214m"; // Orange color

// Menu Struct
struct Menu {
    string data;
    float price;
    int id;
    string category;
    Menu* next;
    static int next_id;
};

// Initialize ID counter
int Menu::next_id = 0;

// Insert Item
void insertItem(Menu*& head, string data, float price, string category) {
    Menu* temp = new Menu;
    temp->data = data;
    temp->price = price;
    temp->category = category;
    temp->next = nullptr;
    temp->id = ++Menu::next_id;

    if (head == nullptr) {
        head = temp;
    } else {
        Menu* temp1 = head;
        while (temp1->next != nullptr) {
            temp1 = temp1->next;
        }
        temp1->next = temp;
    }
}

// Display Menu
void displayMenu(const Menu* head) {
    if (head == nullptr) {
        cout << RED << "Empty List\n" << RESET;
        return;
    }

    cout << "---------------------------------------------------------------------------\n";
    cout << GREEN << "Name" << "\t\t" << RED << "Price" << "\t\t" << BLUE << "Category" << "\t\t" << YELLOW << "ID" << RESET << endl;

    const Menu* temp = head;
    while (temp != nullptr) {
        cout << GREEN << temp->data << "\t\t" << RED << temp->price << "\t\t" << BLUE << temp->category << "\t\t" << YELLOW << temp->id << RESET << endl;
        temp = temp->next;
    }

    cout << WHITE << "---------------------------------------------------------------------------\n";
}

// Search Function (Checks if name is a substring)
void search(string name, Menu* head) {
    Menu* temp = head;
    bool found = false;

    while (temp != nullptr) {
        if (temp->data.find(name) != string::npos) {
            cout << temp->data << " " << temp->price << " " << temp->category << " " << temp->id << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << RED << "No matching items found!\n" << RESET;
    }
}

// Merge Sort Helper Functions
Menu* getMiddle(Menu* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    Menu* slow = head;
    Menu* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

Menu* mergeP(Menu* left, Menu* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    Menu* result = nullptr;

    if (left->price <= right->price) {
        result = left;
        result->next = mergeP(left->next, right);
    } else {
        result = right;
        result->next = mergeP(left, right->next);
    }

    return result;
}

Menu* mergeSortP(Menu* head) {
    if (head == nullptr || head->next == nullptr) return head;

    Menu* middle = getMiddle(head);
    Menu* nextToMiddle = middle->next;

    middle->next = nullptr;

    Menu* left = mergeSortP(head);
    Menu* right = mergeSortP(nextToMiddle);

    return mergeP(left, right);
}

Menu* mergeA(Menu* left, Menu* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    Menu* result = nullptr;

    if (left->data <= right->data) {
        result = left;
        result->next = mergeA(left->next, right);
    } else {
        result = right;
        result->next = mergeA(left, right->next);
    }

    return result;
}

Menu* mergeSortA(Menu* head) {
    if (head == nullptr || head->next == nullptr) return head;

    Menu* middle = getMiddle(head);
    Menu* nextToMiddle = middle->next;
    middle->next = nullptr;

    Menu* left = mergeSortA(head);
    Menu* right = mergeSortA(nextToMiddle);

    return mergeA(left, right);
}

// Sorting Functions
void sortInPrice(Menu*& head) {
    head = mergeSortP(head);
    displayMenu(head);
}

void sortInAlphabet(Menu*& head) {
    head = mergeSortA(head);
    displayMenu(head);
}

// Delete Item
void deleteItem(string data, Menu*& head) {
    if (head == nullptr) {
        cout << RED << "Empty Menu List\n" << RESET;
        return;
    }

    if (head->data == data) {
        Menu* temp = head;
        head = head->next;
        delete temp;
        cout << GREEN << "Item deleted successfully!\n" << RESET;
        return;
    }

    Menu* temp = head;
    while (temp->next != nullptr && temp->next->data != data) {
        temp = temp->next;
    }

    if (temp->next == nullptr) {
        cout << RED << "Item not found!\n" << RESET;
        return;
    }

    Menu* temp1 = temp->next;
    temp->next = temp->next->next;
    delete temp1;
}

// Edit Menu (Handles Invalid ID)
void editMenu(Menu*& head, int id) {
    Menu* temp = head;

    while (temp != nullptr && temp->id != id) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << RED << "Error: No menu item found with ID " << id << "!\n" << RESET;
        return;
    }

    cout << "Editing item: " << temp->data << "\n";
    cout << "1. Edit Name\n2. Edit Category\n3. Edit Price\n";
    int option;
    string name, category;
    float price;
    cin >> option;

    switch (option) {
        case 1:
            cout << "Enter New Name: ";
            cin.ignore();
            getline(cin, name);
            temp->data = name;
            cout << GREEN << "Name updated successfully!\n" << RESET;
            break;
        case 2:
            cout << "Enter New Category: ";
            cin.ignore();
            getline(cin, category);
            temp->category = category;
            cout << GREEN << "Category updated successfully!\n" << RESET;
            break;
        case 3:
            cout << "Enter New Price: ";
            cin >> price;
            temp->price = price;
            cout << GREEN << "Price updated successfully!\n" << RESET;
            break;
        default:
            cout << RED << "Invalid option.\n" << RESET;
    }
}

// Menu Selection
void MenuChoose(Menu*& head);

void back(Menu*& head) {
    cout << "Would you like to go back to the menu? (Enter y/n): ";
    char answer;
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
        cout << "\033[2J\033[H"; // Cross-platform screen clear
        MenuChoose(head);
    }
}

// Main Menu
void MenuChoose(Menu*& head) {
    cout << "<<<<<<<<<<<<<<<<<<<< MENU >>>>>>>>>>>>>>>>>\n";
    cout << "1. Add Menu Item\n2. Remove Menu Item\n3. Sort by Alphabet\n4. Sort by Price\n";
    cout << "5. Search Menu Item\n6. Edit Menu Item\n";

    int option, id;
    string name, category;
    float price;
    cin >> option;

    switch (option) {
        case 1:
            cout << "Enter Item Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Category: ";
            getline(cin, category);
            cout << "Enter Price: ";
            cin >> price;
            insertItem(head, name, price, category);
            break;
        case 2:
            cout << "Enter Item Name to Remove: ";
            cin.ignore();
            getline(cin, name);
            deleteItem(name, head);
            break;
        case 3: sortInAlphabet(head); break;
        case 4: sortInPrice(head); break;
        case 5:
            cout << "Enter name: ";
            cin >> name;
            search(name, head);
            break;
        case 6:
            cout << "Enter ID: ";
            cin >> id;
            editMenu(head, id);
            break;
    }
    back(head);
}

int main() {
    Menu* head = nullptr;
    MenuChoose(head);
    return 0;
}
