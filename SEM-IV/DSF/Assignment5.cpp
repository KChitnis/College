/*
Kshitij Chitnis
SE IT 
8016
S2 BATCH

 Last edited on: 13/03/2020

   ASSIGNMENT 5
*/
/*
// PROBLEM STATEMENT
// Implement binary search tree and perform following operations:
//   a. Insert
//   b. Delete
//   c. Search
//   d. Mirror image
//   e. Display
//   f. Display level wise
//
*/

#include<iostream>
using namespace std;

class treeNode
{
	public:
	int data;
	treeNode *left,*right;
	public:
	treeNode()
	{
		left=NULL;
		right=NULL;
	}
};
class tree
{
	treeNode *root;
	void destroy(treeNode*);
	void pre_disp(treeNode*);
	void in_disp(treeNode*);
	void post_disp(treeNode*);
	treeNode* copy(treeNode*);
public:
	void insert(int);
	void create(void);
	void pre_disp();
	void in_disp();
	void post_disp();
	int search(int);
	void BFT();
	void mirror(tree);
	void del(int);
	int is_empty();
	void destroy();
	tree()
	{
		root=NULL;
	}
	~tree()
	{
		destroy(root);
	}
};
template<class my>
class Node
{
	public:
	my data;
	Node<my>* next;
	public:
	Node()
	{
		next=NULL;
	}
};
template<class my>
class queue
{
	Node<my> *front,*rear;
	void destroy();
	public:
	queue()
	{
		front=NULL;
		rear=NULL;
	}
	my* remove();
	void insert(my);
	int is_empty();
	Node<my>* get_top();
	~queue()
	{
		destroy();
	}
};
template<class my>
int queue<my>::is_empty()
{
	if(front==NULL)
		return 1;
	else
		return 0;
}
template<class my>
void queue<my>::insert(my data)
{
	Node<my>* temp;
	temp=new Node<my>;
	temp->data=data;
	if(rear==NULL)
	{
		rear=temp;
		front=temp;
	}
	else
	{
		rear->next=temp;
		rear=temp;
	}
}
template<class my>
Node<my>* queue<my>::get_top()
{
	if(front==NULL)
		return NULL;
	else
		return front;
}
template<class my>
my* queue<my>::remove()
{
	int ch;
	my* ret;
	Node<my> *temp;
	if(front==NULL)
		return NULL;
	else
	{
		ret=new my;
		*ret=front->data;
		temp=front;
		front=front->next;
		delete temp;
		if(front==NULL)
			rear=NULL;
		return ret;
	}
}
template<class my>
void queue<my>::destroy()
{
	my* temp;
	while(!is_empty())
	{
		temp=remove();
		delete temp;
	}
}
void tree::destroy(treeNode *rt)
{
	if(rt!=NULL)
	{
		destroy(rt->left);
		destroy(rt->right);
		delete rt;
	}
}
void tree::destroy()
{
	destroy(root);
	root=NULL;
}
void tree::pre_disp(treeNode *root)
{
	if(root != NULL)
	{
		cout<<root -> data<<"\t";
		pre_disp(root -> left);
		pre_disp(root ->right);
	}
}
void tree::in_disp(treeNode *root)
{
	if(root != NULL)
	{
		in_disp(root -> left);
		cout<<root -> data<<"\t";
		in_disp(root ->right);
	}
}
void tree::post_disp(treeNode *root)
{
	if(root != NULL)
	{
		post_disp(root -> left);
		post_disp(root ->right);
		cout<<root -> data<<"\t";
	}
}
void tree::insert(int new_data)
{
	treeNode *temp,*pwalk,*parent;
	temp=new treeNode;
	temp->data=new_data;
	if(root==NULL)
		root=temp;
	else
	{
		pwalk=root;
		while(pwalk!=NULL)
		{
			parent=pwalk;
			if(temp->data<pwalk->data)
				pwalk=pwalk->left;
			else if(temp->data>pwalk->data)
				pwalk=pwalk->right;
			else
				break;
		}
		if(pwalk==parent)
			cout<<"The data already exists!!\n";
		else if(temp->data<parent->data)
			parent->left=temp;
		else
			parent->right=temp;
	}
}
void tree::create()
{
	int ch,data;
	do
	{
		cout<<"Do you wish to add Node\n1:Yes\n2:No\nEnter choice:";
		cin>>ch;
		if(ch==1)
		{
			cout<<"Enter data:";
			cin>>data;
			insert(data);
		}
		else if(ch!=2)
			cout<<"Wrong choice!!\n";
	}while(ch!=2);
}
void tree::pre_disp()
{
	pre_disp(root);
}
void tree::in_disp()
{
	in_disp(root);
}
void tree::post_disp()
{
	post_disp(root);
}
int tree::search(int key)
{
	treeNode *pwalk;
	pwalk=root;
	while(pwalk!=NULL)
	{
		if(pwalk->data==key)
			return 1;
		else if(key<pwalk->data)
			pwalk=pwalk->left;
		else
			pwalk=pwalk->right;
	}
	return 0;
}
void tree::BFT()
{
	treeNode *dis;
	queue<treeNode>Q;
	if(root!=NULL)
		Q.insert(*root);
	while(!Q.is_empty())
	{
		dis=Q.remove();
		cout<<dis->data<<",";
		if(dis->left!=NULL)
			Q.insert(*dis->left);
		if(dis->right!=NULL)
			Q.insert(*dis->right);
	}
}
treeNode* tree::copy(treeNode* rt)
{
	treeNode* tr=new treeNode;
	tr->data=rt->data;
	if(rt->left!=NULL)
		tr->left=copy(rt->left);
	if(rt->right!=NULL)
		tr->right=copy(rt->right);
	return tr;
}
void tree::mirror(tree tr)
{
	treeNode *dis,*temp;
	queue<treeNode*>Q;
	root=copy(tr.root);
	if(root!=NULL)
		Q.insert(root);
	while(!Q.is_empty())
	{
		dis=*Q.remove();
		temp=dis->left;
		dis->left=dis->right;
		dis->right=temp;
		if(dis->left!=NULL)
			Q.insert(dis->left);
		if(dis->right!=NULL)
			Q.insert(dis->right);
	}
	tr.root=NULL;
}
void tree::del(int key)
{
	int flag=0,data;
	treeNode *pwalk,*parent,*p,*pre;
	pwalk=root;
	while(parent!=NULL && flag==0)
	{
		if(pwalk->data==key)
			flag=1;
		else if(pwalk->data>key)
		{
			parent=pwalk;
			pwalk=pwalk->left;
		}
		else
		{
			parent=pwalk;
			pwalk=pwalk->right;
		}
	}
	if(flag==0)
	{
		cout<<"Data not found!!";
		return;
	}
	else if(pwalk->left==NULL && pwalk->right==NULL)
	{
		if(pwalk==root)
		{
			root=NULL;
		}
		else
		{
			if(pwalk==parent->left)
				parent->left=NULL;
			else
				parent->right=NULL;
		}
		delete pwalk;
	}
	else if(pwalk->left==NULL)
	{
		if(pwalk==root)
		{
			root=pwalk->right;
		}
		else
		{
			if(parent->left==pwalk)
				parent->left=pwalk->right;
			else
				parent->right=pwalk->right;
		}
		delete pwalk;
	}
	else if(pwalk->right==NULL)
	{
		if(pwalk==root)
		{
			root=pwalk->left;
		}
		else
		{
			if(parent->left==pwalk)
				parent->left=pwalk->left;
			else
				parent->right=pwalk->left;
		}
		delete pwalk;
	}
	else
	{
		pre=pwalk;
		p=pwalk->right;
		while(p->left!=NULL)
		{
			pre=p;
			p=p->left;
		}
		data=p->data;
		if(pre==pwalk)
		{
			if(p->right==NULL)
			{
				pre->right=NULL;
				delete p;
			}
			else
			{
				pre->right=p->right;
				delete p;
			}
		}
		else if(p->right==NULL)
		{
			pre->left=NULL;
			delete p;
		}
		else
		{
			pre->left=p->right;
			delete p;
		}
		pwalk->data=data;
	}
	cout<<"Data has been deleted!!";
}
int tree::is_empty()
{
	if(root==NULL)
		return 1;
	else return 0;
}
int main()
{
	int choice, data, res;
	tree T, M;
	T.create();
	do
	{
		cout<<"\n1. Insert\n2. Search\n3. Delete\n4. Display\n5. BFT\n6. Mirror Image\n7. Exit\nEnter choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1:	cout<<"Enter data to be inserted: ";
					cin>>data;
					T.insert(data);
					break;
			case 2:	cout<<"Enter data to be searched: ";
					cin>>data;
					res=T.search(data);
					if(res==0)
						cout<<data<<" is not in the tree!!";
					else
						cout<<data<<" is found in the tree!!";
					break;
			case 3:	cout<<"Enter data to be deleted: ";
					cin>>data;
					T.del(data);
					break;
			case 4:	cout<<"Preorder traversal:\n\t";
					T.pre_disp();
					cout<<"\nInorder traversal:\n\t";
					T.in_disp();
					cout<<"\nPostorder traversal:\n\t";
					T.post_disp();
					break;
			case 5:	cout<<"Breadth First Traversal of the tree is:\n\t";
					T.BFT();
					break;
			case 6:	M.destroy();
					M.mirror(T);
					cout<<"Preorder traversal of mirror image:\n\t";
					M.pre_disp();
					cout<<"\nInorder traversal of mirror image:\n\t";
					M.in_disp();
					cout<<"\nPostorder traversal of mirror image:\n\t";
					M.post_disp();
					break;
			case 7:	break;
			default:	cout<<"Invalid choice!!";
		}
	}
	while(choice!=7);
	return 0;
}


/*
OUTPUT:
 ./a.out
Do you wish to add Node
1:Yes
2:No
Enter choice:1
Enter data:1  
Do you wish to add Node
1:Yes
2:No
Enter choice:1
Enter data:2
Do you wish to add Node
1:Yes
2:No
Enter choice:1
Enter data:3
Do you wish to add Node
1:Yes
2:No
Enter choice:2

1. Insert
2. Search
3. Delete
4. Display
5. BFT
6. Mirror Image
7. Exit
Enter choice: 1
Enter data to be inserted: 3
The data already exists!!

1. Insert
2. Search
3. Delete
4. Display
5. BFT
6. Mirror Image
7. Exit
Enter choice: 1
Enter data to be inserted: 4

1. Insert
2. Search
3. Delete
4. Display
5. BFT
6. Mirror Image
7. Exit
Enter choice: 2
Enter data to be searched: 2
2 is found in the tree!!
1. Insert
2. Search
3. Delete
4. Display
5. BFT
6. Mirror Image
7. Exit
Enter choice: 3
Enter data to be deleted: 1
Data has been deleted!!
1. Insert
2. Search
3. Delete
4. Display
5. BFT
6. Mirror Image
7. Exit
Enter choice: 4
Preorder traversal:
	2	3	4	
Inorder traversal:
	2	3	4	
Postorder traversal:
	4	3	2	
1. Insert
2. Search
3. Delete
4. Display
5. BFT
6. Mirror Image
7. Exit
Enter choice: 5
Breadth First Traversal of the tree is:
	2,3,4,
1. Insert
2. Search
3. Delete
4. Display
5. BFT
6. Mirror Image
7. Exit
Enter choice: 6
Preorder traversal of mirror image:
	2	3	4	
Inorder traversal of mirror image:
	4	3	2	
Postorder traversal of mirror image:
	4	3	2	
1. Insert
2. Search
3. Delete
4. Display
5. BFT
6. Mirror Image
7. Exit
Enter choice: 7

*/
