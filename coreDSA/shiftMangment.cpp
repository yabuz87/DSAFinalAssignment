struct shiftManagment
{
    int shiftId;
    string shiftName;
    string shiftTime;
    int numberOfEmployees;
    shiftManagment *next;

    void addShift(string shiftName,string shiftTime,int numberOfEmployees,int shiftId,shiftManagment *&first)
    {
        shiftManagment *temp = new shiftManagment;
        temp->shiftName = shiftName;
        temp->shiftTime = shiftTime;
        temp->numberOfEmployees = numberOfEmployees;
        employee *n=new employee[numberOfEmployees];
        int id;
        for(int i=0;i<numberOfEmployees;i++)
        {
            cout<<"enter Id of employee in the shift\n";
            cin>>id;
            if(head==nullptr)
            {
                cout<<"No employee to assign\n";
            }
            else
            {
                employee *temp1=head;
                while(temp1->id!=id)
                {
                    temp1=temp1->next;
                }
                n[i]=*temp1;
            }

            
        }

        temp->shiftId = shiftId;
        temp->next=NULL;

        if(head==nullptr)
        {
            head=temp;
        }
        else
        {
            shiftManagment *temp1=head;
            while(temp1->next!=nullptr)
            {
                temp1=temp1->next;
            }
            temp1->next=temp;
        }
    }

};