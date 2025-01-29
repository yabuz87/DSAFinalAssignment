#include <iostream>
#include <limits>
using namespace std;

struct menu {
    string data;
    float price;
    int id;
    string category;
    menu *next;

    static int next_id;

    void insertItem(string data, float price, string category, menu *&head) {
        menu *temp = new menu;
        temp->data = data;
        temp->price = price;
        temp->category = category;
        temp->next = nullptr;
        temp->id = ++next_id;

        if (head == nullptr) {
            head = temp;
        } else {
            menu *temp1 = head;
            while (temp1->next != nullptr) {
                temp1 = temp1->next;
            }
            temp1->next = temp;
        }
    }

    void displayMenu(const menu *head) {
        const menu *temp = head;
        while (temp != nullptr) {
            cout << "| " << temp->data << " | " << temp->price << "| "<<temp->category<<" "<<temp->id << endl;
            temp = temp->next;
        }
    }
    void search(string name,menu*&head)
    {
      int   i=0;
        menu* temp=head;
        while(i<4)
        {
            while(temp!=nullptr)
            {
                if(temp->data[i]==name[i])
                {
                    cout<<temp->data<<" "<<temp->price<<" "<<temp->category<<" "<<temp->id<<endl;
                }
                temp=temp->next;
            }
            i++;

        }
    }

    menu* getMiddle(menu* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        menu* slow = head;
        menu* fast = head->next;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    menu* mergeP(menu* left, menu* right) {
        if (left == nullptr) {
            return right;
        }
        if (right == nullptr) {
            return left;
        }

        menu* result = nullptr;

        if (left->price <= right->price) {
            result = left;
            result->next = mergeP(left->next, right);
        } else {
            result = right;
            result->next = mergeP(left, right->next);
        }

        return result;
    }

    menu* mergeSortP(menu* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        menu* middle = getMiddle(head);
        menu* nextToMiddle = middle->next;

        middle->next = nullptr;

        menu* left = mergeSortP(head);
        menu* right = mergeSortP(nextToMiddle);

        return mergeP(left, right);
    }

    menu* mergeA(menu* left, menu* right) {
        if (left == nullptr) {
            return right;
        }
        if (right == nullptr) {
            return left;
        }

        menu* result = nullptr;

        if (left->data <= right->data) {
            result = left;
            result->next = mergeA(left->next, right);
        } else {
            result = right;
            result->next = mergeA(left, right->next);
        }

        return result;
    }

    menu* mergeSortA(menu* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        menu* middle = getMiddle(head);
        menu* nextToMiddle = middle->next;
        middle->next = nullptr;

        menu* left = mergeSortA(head);
        menu* right = mergeSortA(nextToMiddle);

        return mergeA(left, right);
    }

    void sortInPrice(menu *&head) {
        head = mergeSortP(head);
        displayMenu(head);
    }

    void sortInAlphabet(menu *&head) {
        head = mergeSortA(head);
        displayMenu(head);
    }

    void deleteItem(string data, menu *&head) {
        if (head == nullptr) return;
        if (head->data == data) {
            menu *temp = head;
            head = head->next;
            delete temp;
            return;
        }

        menu *temp = head;
        while (temp->next != nullptr && temp->next->data != data) {
            temp = temp->next;
        }

        if (temp->next == nullptr) return;

        menu *temp1 = temp->next;
        temp->next = temp->next->next;
        delete temp1;
    }
};

int menu::next_id = 0; // Initialize the static variable

void MenuChoose(menu *&head);

void back(menu*& head) {
    cout << "Would you like to go back to the menu? (Enter y/n): ";
    char answer;
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
         system("CLS");  // Avoid or handle this for platform compatibility
        MenuChoose(head);
    } else {
         system("CLS");  // Avoid or handle this for platform compatibility
        return;
    }
}

void MenuChoose(menu *&head) {
    cout << "<<<<<<<<<<<<<<<<<<<<menu>>>>>>>>>>>>>>>\n";
    cout << "1. Add Menu Item\n2. Remove Menu Item\n3. List Menu Items by Alphabet\n4. List Menu Items by Price\n";
    cout << "5. Search Menu Item\n6. Edit Menu Item\n";

    int option;
    string name;
    string category;
    float price;
    cin >> option;

    switch (option) {
        case 1:
            cout << "Please Enter the following queries\nItem Name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            getline(cin, name);
            cout << "\nCategory: ";
            getline(cin, category);
            cout << "\nPrice: ";
            cin >> price;
            head->insertItem(name, price, category, head);
            break;
        
        case 2:
            cout << "Which item do you want to remove? ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            getline(cin, name);
            // system("CLS");  // Avoid or handle this for platform compatibility
            head->deleteItem(name, head);
            break;

        case 3:
            // system("CLS");  // Avoid or handle this for platform compatibility
            head->sortInAlphabet(head);
            break;

        case 4:
            // system("CLS");  // Avoid or handle this for platform compatibility
            head->sortInPrice(head);
            break;
        case 5:
            cout<<"Enter the name\n\n";
            cin>>name;
            head->search(name,head);
            break;


        default: 
            cout << "Invalid option, please try again.\n";
            break;
    }
    
    back(head);
}

int main() {
    menu* head = nullptr;
    MenuChoose(head);
    return 0;
}
