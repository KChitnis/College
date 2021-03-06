/*
// ASSIGNMENT 2
//
// PROBLEM STATEMENT
// Implement priority queue as ADT using single linked list for servicing patients in an hospital with priorities as
//   i) Serious (top priority)
//   ii) Medium (medium priority)
//   iii) General (Least priority).
//
*/

#include <iostream>

using namespace std;

class node /*class to store patient information*/
{
    public:
        char name[30];
        int priority;
        node *next;
        node();
};

class seriousQueue /*class to create a priority queue*/
{
        node *front, *rear;
    public:
        seriousQueue();
        void enqueue();
        void dequeue();
        void display();
};

class moderateQueue /*class to create a priority queue*/
{
        node *front, *rear;
    public:
        moderateQueue();
        void enqueue();
        void dequeue();
        void display();
};

class generalQueue /*class to create a priority queue*/
{
        node *front, *rear;
    public:
        generalQueue();
        void enqueue();
        void dequeue();
        void display();
};

int main()
{
    seriousQueue spatient;
    moderateQueue mpatient;
    generalQueue gpatient;

    int choice;

    do
    {
        cout << "\n1. Admit Patient\n2. Release Patient\n3. Display Patient Queue\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                {
                    patient.enqueue();
                    break;
                }
            case 2:
                {
                    patient.dequeue();
                    break;
                }
            case 3:
                {
                    patient.display();
                    break;
                }
            case 4: break;
            default:
                {
                    cout << "\nInvalid Input!\n";
                    break;
                }
        }
    }
    while(choice!=4);

    return 0;
}

void priorityQueue::display() /*function to display patients' queue*/
{
    if(front==NULL) /*check for empty queue*/
    {
        cout << "\nEmpty Queue!\n";
    }
    else /*display patient data priority-wise*/
    {
        int sr=1;
        node *temp=front;
        cout << "\n-------------------------------------";
        cout << "\nSr\tName\t\tPriority";
        cout << "\n-------------------------------------";
        while(temp!=NULL)
        {
            cout << "\n" << sr << "\t" << temp->name << "\t\t";
            if(temp->priority==1)
            {
                cout << "Serious\n";
            }
            else if(temp->priority==2)
            {
                cout << "Moderate\n";
            }
            else
            {
                cout << "General\n";
            }
            sr++;
            temp=temp->next;
        }
    }
}

void priorityQueue::dequeue() /*function to release a patient (remove from queue)*/
{
    if(front==NULL) /*check for empty queue*/
    {
        cout << "\nEmpty Queue!\n";
    }
    else
    {
        cout << "\nPatient released!\n";
        cout << "\nName: " << front->name << endl;
        cout << "Illess: ";
        switch(front->priority)
        {
            case 1:
                {
                    cout << "Serious\n";
                    break;
                }
            case 2:
                {
                    cout << "Moderate\n";
                    break;
                }
            case 3:
                {
                    cout << "General\n";
                    break;
                }
        }

        node *temp=front; /*delete node and set front to the next node*/
        front=front->next;
        delete temp;
    }
}

void priorityQueue::enqueue() /*function to admit a patient (add to queue)*/
{
    node *patient=new node;
    cout << "\nEnter patient's name: ";
    cin.ignore();
    cin.getline(patient->name, 30);
    cout << "\n1. Serious\n2. Moderate\n3. General\nSelect the condition: ";
    cin >> patient->priority;



    if(rear==NULL) /*check if queue is empty*/
    {
        patient->next=NULL;
        front=rear=patient;
    }
    else if(patient->priority < front->priority) /*check if node should be added at the front*/
    {
        patient->next=front;
        front=patient;
    }
    else /*insert node at appropriate position*/
    {
        node *temp=front, *prev;
        while((temp->priority <= patient->priority) && temp->next!=NULL) /*find position*/
        {
            prev=temp;
            temp=temp->next;
        }
        if(temp->next==NULL && (temp->priority <= patient->priority)) /*if patient is the last element in the queue*/
        {
            temp->next=patient;
            patient->next=NULL;
            rear=patient;
        }
        else
        {
            patient->next=temp;
            prev->next=patient;
        }
    }
    cout << "\nPatient enqueued!\n";
}

priorityQueue::priorityQueue() /*constructor for priority queue*/
{
    front=rear=NULL;
}

node::node() /*constructor for node*/
{
    name[0]='\0';
    priority=-1;
    next=NULL;
}
