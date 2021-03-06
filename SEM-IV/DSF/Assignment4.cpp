/*
// ASSIGNMENT 4
//
// PROBLEM STATEMENT
// Construct and expression tree from postfix/prefix expression and perform recursive and non-recursive
// in-order, pre-order and post-order traversals
//
*/

#include<iostream>
#include<string.h>	

using namespace std;

class tree	
{
	public:
		char data;
		tree *left;
		tree *right;
		int flag;
		tree();			
};

class node		
{
	public:
		tree *t;
		node *next;
		node();
};

class stack  		
{
	private:
		 node *top;

	public:
		stack();
		void push(tree *temp);
		tree* pop();
		node* empty();
};

class expression		
{
	private:
		char post[100];
		char pre[100];
		stack s;

	public:
		void insertPostfix();
		void insertPrefix();
		void NRinorder();
		void NRprefix();
		void NRpostfix();
		void Rinorder(tree*);
		void Rpostorder(tree*);
		void Rpreorder(tree*);
		void RI();
		void RPR();
		void RPO();
};

int main()
{
	expression E;		
	int choice;
	
	do
	{
		cout << "\n1. Postfix\n2. Prefix\n3. Exit\nEnter your choice: "; 
		cin >> choice;
		switch(choice)
		{
			case 1:
				{
					E.insertPostfix();
			
					cout<<"\nRECURSIVE TRAVERSALS\n";
					cout<<"\nInorder Traversal: ";
					E.RIN();
					cout<<"\nPostorder Traversal: ";
					E.RPO();
					cout<<"\nPreorder Traversal: ";
					E.RPR();
				
					cout<<"\nNON-RECURSIVE TRAVERSALS\n";
					cout<<"\nInorder Traversal: ";
					E.NRinorder();
					cout<<"\nPostorder Traversal: ";
					E.NRpostfix();
					cout<<"\nPreorder Traversal: ";
					E.NRprefix();
			
					break;
				}
			case 2:
				{
					E.insertPrefix();
			
					cout<<"\nRECURSIVE TRAVERSALS\n";
					cout<<"\nInorder Traversal: ";
					E.RIN();
					cout<<"\nPostorder Traversal: ";
					E.RPO();
					cout<<"\nPreorder Traversal: ";
					E.RPR();
				
					cout<<"\nNON-RECURSIVE TRAVERSALS\n";
					cout<<"\nInorder Traversal: ";
					E.NRinorder();
					cout<<"\nPostorder Traversal: ";
					E.NRpostfix();
					cout<<"\nPreorder Traversal: ";
					E.NRprefix();
					
					break;
				}
			case 3:	break;
			default:
				{
					cout << "\nInvalid input!";
					break;
				}
		}
	}
	while(choice!=3);
	
	return 0;
}

tree::tree()
{
	left=NULL;
	right=NULL;
	data=0;
	flag=0;
}

node::node()
{
	t=NULL;
	next=NULL;
}

stack::stack()
{
	top=NULL;
}

void stack::push(tree *temp)		
{
	node *p=new node;
			
	if(top==NULL)
	{
		top=new node;
		p->t=temp;
		p->next=NULL;
		top=p;
	}
	else
	{
		p->t=temp;
		p->next=top;
		top=p;	
	}
}

tree* stack::pop()		
{
	node *p=new node;
	tree *t=new tree;
			
	if(top==NULL)
	{
		cout<<"\nEnter the equation: ";
	}
			
	p=top;
	top=top->next;
			
	return p->t;
}

node* stack::empty()		
{
	return top;
}

void expression::insertPostfix()		
{
	int i=0;
	cout << "\nEnter postfix expression: ";
	cin >> post;
	while(post[i]!='\0')
	{
		tree *p=new tree;
		p->data=post[i];
		s.push(p);

		if((p->data=='+')||(p->data=='-')||(p->data=='*')||(p->data=='/'))
		{
			tree *temp= new tree;
			temp=s.pop();
			temp->right=s.pop();
			temp->left=s.pop();		
			s.push(temp);
		}
		i++;
	}
}

void expression::insertPrefix()		
{
	int i=0;
	int k;
	cout << "\nEnter prefix expression: ";
	cin >> pre;
	k=strlen(pre);
	i=k-1;
	while(i>=0)		
	{
		tree *p=new tree;
		p->data=pre[i];
		s.push(p);

		if((p->data=='+')||(p->data=='-')||(p->data=='*')||(p->data=='/'))
		{
			tree *temp= new tree;
			temp=s.pop();
			temp->left=s.pop();
			temp->right=s.pop();		
			s.push(temp);	
		}
		i--;
	}
}

void expression::NRinorder()	
{
	tree* t;
	stack w;
	t=s.pop();
	s.push(t);
	while(t!=NULL)
	{
		w.push(t);
		t=t->left;
	}
	t=w.pop();
	cout<<t->data;
	while(w.empty()!=NULL)
	{
		t=w.pop();
		cout<<t->data;
		
		t=t->right;
		while(t!=NULL)
		{
			w.push(t);
			t=t->left;
		}
	}
}

void expression::NRprefix()	
{
	tree *t;
	stack w;
	
	t=s.pop();
	s.push(t);
	while(t!=NULL)
	{
		cout<<t->data;
		w.push(t);
		t=t->left;
	}
	
	while(w.empty()!=NULL)
	{
		t=w.pop();
		t=t->right;
		
		while(t!=NULL)
		{
			cout<<t->data;
			w.push(t);
			t=t->left;
		}
	}
}

void expression::NRpostfix()	
{
	tree *t;
	t=s.pop();
	s.push(t);
	stack st1,st2;
	st1.push(t);
	while(st1.empty()!=NULL)
	{
		t=st1.pop();
		st2.push(t);
		
		if((t->left)!=NULL)
        	st1.push(t->left);
			
		
		if((t->right)!=NULL)
    		st1.push(t->right);
       
	}
	while(st2.empty()!=NULL)
	{
		t=st2.pop();
		cout<<t->data;
	}
}

void expression::RIN()	
{
	tree *t;
	t=s.pop();
	s.push(t);
	Rinorder(t);
}

void expression::Rinorder(tree* r)		
{
	if(r!=NULL)
	{
		Rinorder(r->left);
		cout<<r->data;
		Rinorder(r->right);
	}
}

void expression::RPO()		
{
	tree *t;
	t=s.pop();
	s.push(t);
	Rpostorder(t);
}

void expression::Rpostorder(tree *r) 
{
	if(r!=NULL)
	{
		Rpostorder(r->left);
		Rpostorder(r->right);
		cout<<r->data;
	}
}

void expression::RPR()		
{
	tree *t;
	t=s.pop();
	s.push(t);
	Rpreorder(t);
}

void expression::Rpreorder(tree *r) 
{
	if(r!=NULL)
	{
		cout<<r->data;
		Rpreorder(r->left);
		Rpreorder(r->right);
	}
}