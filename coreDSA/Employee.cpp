#include<iostream>
using namespace std;

struct employee
{
employee *next;
string name;
int id;
string department;
char gender;
float salary;
//firing
//hiring
//updating
//displaying
//searching
//sorting


 void hireEmployee(string name, string department,char geneder, float salary,int id, employee *&head)
 {
     employee *temp = new employee;
     temp->name = name;
     temp->id=id;
     temp->department = department;
     temp->salary = salary;
     temp->next=NULL;
     temp->gender=gender;

     if(head==nullptr)
        {
            head=temp;
        }
        else
        {
            employee *temp1=head;
            while(temp1->next!=nullptr)
            {
                temp1=temp1->next;
            }
            temp1->next=temp;
            cout<<"Hiring Success!\n";
     }
 }
 void fireEmployee(employee *&head,int id)
 {
    if(head==nullptr)
    {
        cout<<"No employee to fire\n";
    }
    else
    {
        employee *temp=head;
        if(temp->id==id)
        {
            head=temp->next;
            delete temp;
             cout<<"Employee Fired!\n";
        }
        else
        {
            while(temp->next->id!=id)
            {
                temp=temp->next;
            }
            employee *temp1=temp->next;
            temp->next=temp->next->next;
            delete temp1;
            cout<<"Employee Fired!\n";
        }
    }
 }
void updateName(int id,string name,employee *head)
{
    employee *temp=head;
    while(temp->id!=id)
    {
        temp=temp->next;
    }
    temp->name=name;

}
void updateSalary(int id,float salary,employee *head)
{
    employee *temp=head;
    while(temp->id!=id)
    {
        temp=temp->next;
    }
    temp->salary=salary;
}
void updateDepartment(int id,string department,employee *head)
{
    employee *temp=head;
    while(temp->id!=id)
    {
        temp=temp->next;
    }
    temp->department=department;
}

void displayEmployee(employee *head)
{
    employee *temp=head;
    cout<<"Name"<<" "<<"ID"<<" "<<"Department"<<" "<<"Salary"<<" "<<"Gender\n";
    while(temp!=nullptr)
    {
        cout<<temp->name<<" "<<temp->id<<" "<<temp->department<<" "<<temp->salary<<" "<<temp->gender<<endl;
        temp=temp->next;
    }
}
void searchEmployee(int id,employee *head)
{
    employee *temp=head;
    while(temp->id!=id)
    {
        temp=temp->next;
    }
    cout<<"Name"<<" "<<"ID"<<" "<<"Department"<<" "<<"Salary"<<" "<<"Gender\n";
    cout<<temp->name<<" "<<temp->id<<" "<<temp->department<<" "<<temp->salary<<" "<<temp->gender<<endl;
}
employee* getMiddle(employee* head)
 {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    employee* slow = head;
    employee* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}
    // Helper function to find the middle of the list
employee* mergeS(employee* left, employee* right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }

    employee* result = nullptr;

    // Compare based on the price
    if (left->salary <= right->salary) {
        result = left;
        result->next = mergeS(left->next, right);
    } else {
        result = right;
        result->next = mergeS(left, right->next);
    }

    return result;
}
employee* mergeSortS(employee* head) {
    if (head == nullptr || head->next == nullptr) {
        return head; // Base case: 0 or 1 node is already sorted
    }

    // Split the list into two halves
    employee* middle = getMiddle(head);
    employee* nextToMiddle = middle->next;

    middle->next = nullptr; // Break the list into two halves

    // Recursively sort both halves
    employee* left = mergeSortS(head);
    employee* right = mergeSortS(nextToMiddle);

    // Merge the sorted halves
    return mergeS(left, right);
}


employee* mergeN(employee* left, employee* right) {
        if (left == nullptr) {
            return right;
        }
        if (right == nullptr) {
            return left;
        }

        employee* result = nullptr;

        // Compare based on the `data` field (alphabetical order)
        if (left->name <= right->name) {
            result = left;
            result->next = mergeN(left->next, right);
        } else {
            result = right;
            result->next = mergeN(left, right->next);
        }

        return result;
    }
    // Merge sort function
    employee* mergeSortN(employee* head) {
        if (head == nullptr || head->next == nullptr) {
            return head; // Base case: 0 or 1 node is already sorted
        }

        // Split the list into two halves
        employee* middle = getMiddle(head);
        employee* nextToMiddle = middle->next;
        middle->next = nullptr; // Break the list into two halves

        // Recursively sort both halves
        employee* left = mergeSortN(head);
        employee* right = mergeSortN(nextToMiddle);

        // Merge the sorted halves
        return mergeN(left, right);
    }

void sortInSalary(employee *head)
{
    head = mergeSortS(head);
    displayEmployee(head);

}
void sortInName(employee *head)
{
    head = mergeSortN(head);
    displayEmployee(head);
}

};