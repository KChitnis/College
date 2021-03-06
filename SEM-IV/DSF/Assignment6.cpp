//Kshitij Chitnis
//SE-IT
//S2 Batch
//ROLL NO.8016

//Last edited on:13/03/2020

// ASSIGNMENT 6

// PROBLEM STATEMENT
// Consider a friends’ network on facebook social site. Model it as a graph to represent each node as a user and a link
// to represent the fried relationship between them. Store data such as date of birth, number of comments for each user.
//   1. Find who is having maximum friends
//   2. Find whose has post maximum and minimum comments
//   3. Find users having birthday in this month


#include<iostream>
#include<string.h>
using namespace std;

class node
{
	int ver;
	char name[30];
	int dd, mm, yy;
	int no_c;
	int totalFriends;
	node *next;
	friend class graph;
};

class queue
{
	int array[10], r, f;
	
	public:
		queue();
		int isEmpty();
		void enqueue(int);
		int dequeue();
};

class graph
{
	int n;
	int visited[20];
	node *arr[10];
	char nm[30][10];
	int noc[10], bmon[10];
	
	public:
		void create(int,int,char*,int,int,int);
		void display(int);
		void read_g();
		void print_g();
		int dfs_maxc(int);
		int dfs_minc(int);
		void network();
		void bfs_bday(int,int);
		int dfs_maxf(int);
		void fren();
};


void graph::create(int num,int v,char *nm,int noc,int mom,int tot)
{	
	node *p,*temp;
	
	temp=new node;
	temp->ver=v;
	temp->no_c=noc;
	temp->mm=mom;
	temp->totalFriends=tot;
	strcpy(temp->name,nm);
	temp->next=NULL;

	if(arr[num]==NULL)
		arr[num]=temp;
		
	else	
	{
		p=arr[num];
		while(p->next!=NULL)
			p=p->next;						
				
		p->next=temp;		
	}	
	
}

void graph::read_g()
{
	int i, j, ans, noc1, noc2, tot;
	
	cout<<"\nEnter total number of friends in the network : ";
	cin>>n;
	

	for(i=0;i<n;i++)
	{
		cout<<"\nEnter name : ";
		cin>>nm[i];
		cout<<"\nEnter total comments : ";
		cin>>noc[i];
		cout<<"\nEnter birth month : ";
		cin>>bmon[i];
		
		while(bmon[i]>12)
		{
			cout<<"\nINVALID MONTH..Enter birth month again : ";
			cin>>bmon[i];
		}
		
		arr[i]=NULL;
	}
	
	for(i=0; i<n; i++)
	{	
		tot=0;
		for(j=0; j<n; j++)
		{
			if(!(i>=j))	
			{
				cout<<"\nAre "<<nm[i]<<" and "<<nm[j]<<" friends? \nPress (1/0) : ";
				cin>>ans;
				
				if(ans==1)
				{
					tot++;
					create(i,j,nm[j],noc[j],bmon[j],tot);
					create(j,i,nm[i],noc[i],bmon[i],tot);
				}	
			}
		}
	}
}


void graph::display(int i)
{
	node *p;
	p=arr[i];
	while(p!=NULL)
	{
		cout << "\n" << p->name;
		p=p->next;
	}
}

void graph::print_g()
{
	int i;
	for(i=0; i<n; i++)
	{
		cout << "\n" << nm[i] <<"'s Friends\n";
		display(i);
		cout << "\n----------------------------------\n";
	}
}


void graph :: network()
{
	int i, max, min;
	
	for(i=0; i<n; i++)
	{
		visited[i]=0;
	}	
	max=dfs_maxc(0);

	for(i=0; i<n; i++)
	{
		visited[i]=0;
	}
	min=dfs_minc(0);
	
	cout << "\nMaximum comments: " << max;
	cout << "\nMinimum comments: " << min;
}


void graph :: fren()
{
	int i,us,mf;
	
	
	for(i=0;i<n;i++)
		visited[i]=0;
		
	
	cout<<"\nMax friends are : ";
					
	mf=dfs_maxf(us);
	cout<<mf;
}


int graph :: dfs_maxc(int i)
{
	static int MAX=0;
	node *p;
	p=arr[i];
	visited[i]=1;
	//cout<<"\n"<<nm[i];
	
	
	while(p!=NULL)
	{	
		if(p->no_c > MAX)
			MAX=p->no_c;	
		i=p->ver;
		if(!visited[i])
			MAX=dfs_maxc(i);
		p=p->next;
	}
	return MAX;
}

int graph :: dfs_minc(int i)
{
	static int MIN=9999;
	node *p;
	p=arr[i];
	visited[i]=1;
	//cout<<"\n"<<nm[i];
		
	
	while(p!=NULL)
	{
		if(p->no_c < MIN)
		MIN=p->no_c;
	
		i=p->ver;
		if(!visited[i])
			MIN=dfs_minc(i);
		p=p->next;
	}
	return MIN;
}

int graph :: dfs_maxf(int i)
{
	static int MAX=0;
	node *p;
	p=arr[i];
	visited[i]=1;
	//cout<<"\n"<<nm[i];
	
	
	while(p!=NULL)
	{	
		if(p->totalFriends > MAX)
			MAX=p->totalFriends;	
		i=p->ver;
		if(!visited[i])
			MAX=dfs_maxf(i);
		p=p->next;
	}
return MAX;
}

void graph :: bfs_bday(int x,int mon)
{
	queue q;
	node *p;
	p=arr[x];	
	int i,w;
	
	for(i=0;i<n;i++)
		visited[i]=0;
		
	q.enqueue(x);

	visited[x]=1;
	
	
	while(!q.isEmpty())
	{
		x=q.dequeue();
		
		for(p=arr[x];p!=NULL;p=p->next)
		{
			w=p->ver;
			
			if(visited[w]==0)
			{
				q.enqueue(w);
				visited[w]=1;
			}
			
			else
			{
				if(p->mm==mon)
					cout<<"\n"<<nm[w];
			}
		}
	}
}


int main()
{
	int i,mon,choice,us,mf,f;
	graph g;
	
	g.read_g();
	
	do
	{
		cout<<"\n1. Display Friend List\n2. Maximum and minimum comments in the network\n3. Birthdays in same month\n4. Maximum Friends\n5. Exit\nEnter your choice : ";
		cin>>choice;
		
		switch(choice)
		{
			case 1:
				{
					g.print_g();
					break;
				}
			case 2:
				{
					g.network();
					break;
				}
			case 3:
				{
					cout<<"\nEnter Month to check : ";
					cin>>mon;
					cout<<"\nFriends in the network with Birthdays falling in the month "<<mon<<" are :";
					g.bfs_bday(0,mon);
					break;
				}
			case 4:
				{
					g.fren();
					break;
				}
			case 5:	break;
			default:
				{
					cout<<"\nInvalid Choice";
					break;
				}	
		}
	}
	while(choice!=5);
	
	return 0;
}

queue::queue()
{
	r=f=-1;
}

int queue::isEmpty()
{
	if(r==-1)
	{
		return 1;
	}
	return 0;
}

void queue::enqueue(int data)
{
	if(isEmpty())
	{
		r=f=0;
	}
	else
	{
		r++;
	}
	array[r]=data;	
}

int queue::dequeue()
{
	int data;
	data=array[f];
	
	if(r==f)
	{
		r=f=-1;
	}
	else
	{
		f++;
	}
	return data;
}




/*
OUTPUT:

./a.out

Enter total number of friends in the network : 2

Enter name : shivani

Enter total comments : 2

Enter birth month : 2

Enter name : laksh

Enter total comments : 1

Enter birth month : 5

Are shivani and laksh friends? 
Press (1/0) : 1

1. Display Friend List
2. Maximum and minimum comments in the network
3. Birthdays in same month
4. Maximum Friends
5. Exit
Enter your choice : 1

shivani's Friends

laksh
----------------------------------

laksh's Friends

shivani
----------------------------------

1. Display Friend List
2. Maximum and minimum comments in the network
3. Birthdays in same month
4. Maximum Friends
5. Exit
Enter your choice : 2

Maximum comments: 2
Minimum comments: 1
1. Display Friend List
2. Maximum and minimum comments in the network
3. Birthdays in same month
4. Maximum Friends
5. Exit
Enter your choice : 3

Enter Month to check : 2

Friends in the network with Birthdays falling in the month 2 are :
shivani
1. Display Friend List
2. Maximum and minimum comments in the network
3. Birthdays in same month
4. Maximum Friends
5. Exit
Enter your choice : 4

Max friends are : 1
1. Display Friend List
2. Maximum and minimum comments in the network
3. Birthdays in same month
4. Maximum Friends
5. Exit
Enter your choice : 5

*/
