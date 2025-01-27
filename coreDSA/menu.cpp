#include <iostream>
using namespace std;


struct menu
{
    string data;
    float price;
    menu *next;

void insertItem(string data, float price, menu *&head)
{
    menu *temp = new menu;
    temp->data = data;
    temp->price = price;
    temp->next = NULL;
    if(head == NULL)
    {
        head = temp;
    }
    else
    {
        menu *temp1 = head;
        while(temp1->next != NULL)
        {
            temp1 = temp1->next;
        }
        temp1->next = temp;
    }
}
void displayMenu(menu *&head)
{
    menu *temp = head;
    while(temp != NULL)
    {
        cout << temp->data << " " << temp->price << endl;
        temp = temp->next;
    }
    
}
menu* getMiddle(menu* head)
 {
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
    // Helper function to find the middle of the list
menu* mergeP(menu* left, menu* right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }

    menu* result = nullptr;

    // Compare based on the price
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
        return head; // Base case: 0 or 1 node is already sorted
    }

    // Split the list into two halves
    menu* middle = getMiddle(head);
    menu* nextToMiddle = middle->next;

    middle->next = nullptr; // Break the list into two halves

    // Recursively sort both halves
    menu* left = mergeSortP(head);
    menu* right = mergeSortP(nextToMiddle);

    // Merge the sorted halves
    return mergeP(left, right);
}
 // Helper function to merge two sorted linked lists
    menu* mergeA(menu* left, menu* right) {
        if (left == nullptr) {
            return right;
        }
        if (right == nullptr) {
            return left;
        }

        menu* result = nullptr;

        // Compare based on the `data` field (alphabetical order)
        if (left->data <= right->data) {
            result = left;
            result->next = mergeA(left->next, right);
        } else {
            result = right;
            result->next = mergeA(left, right->next);
        }

        return result;
    }
    // Merge sort function
    menu* mergeSortA(menu* head) {
        if (head == nullptr || head->next == nullptr) {
            return head; // Base case: 0 or 1 node is already sorted
        }

        // Split the list into two halves
        menu* middle = getMiddle(head);
        menu* nextToMiddle = middle->next;
        middle->next = nullptr; // Break the list into two halves

        // Recursively sort both halves
        menu* left = mergeSortA(head);
        menu* right = mergeSortA(nextToMiddle);

        // Merge the sorted halves
        return mergeA(left, right);
    }
void sortInPrice(menu *head)
{

    head = mergeSortP(head);
    displayMenu(head);

}
 void sortInAlphabet(menu* &head)
 {

    head = mergeSortA(head);
    displayMenu(head);
}
 void deleteItem(string data, menu *&head)
 {
    menu *temp=head;
    while(temp->next->data !=data)
    {
        temp=temp->next;
    }
    menu *temp1=temp->next;
    temp->next=temp->next->next;
    delete temp1;    
 }

};

int main()
{
    menu* head = NULL;
    menu m;
    m.data = "Burger";
    m.price = 5.99;
    m.insertItem(m.data, m.price, head);
    m.data = "Pizza";
    m.price = 7.99;
    m.insertItem(m.data, m.price, head);
    m.data = "Pasta";
    m.price = 6.99;
    m.insertItem(m.data, m.price, head);
    m.data = "Sandwich";
    m.price = 4.99;
    m.insertItem(m.data, m.price, head);
    m.displayMenu(head);
    cout << "After sorting in price" << endl;
    m.sortInPrice(head);
    cout << "After sorting in Alphabet" << endl;
    m.sortInAlphabet(head);
    cout << "After deleting an item" << endl;
    m.deleteItem("Pizza", head);
    m.displayMenu(head);
    return 0;

}
