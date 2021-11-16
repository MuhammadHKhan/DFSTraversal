#include <iostream>

template <class Type>
class myStack
{
public:
	myStack();
	myStack(const myStack<Type>&);
	const myStack<Type>& operator=(const myStack<Type>&);
	~myStack();

	void push(const Type&);
	void pop();
	Type top() const;
	bool isEmpty() const;

private:
	struct node
	{
		Type item;
		node* next;
	};

	node* topOfmyStack;
};

//sets the node to null, this is 
//a default constructor
template <class Type>
myStack<Type>::myStack()
{
	topOfmyStack = NULL;
}

//makes a copy of the this item into the copy 
template <class Type>
myStack<Type>::myStack(const myStack<Type>& copy)
{
	*this = copy;
}

//operator overload for the assignment operator
template<class Type>
const myStack<Type>& myStack<Type>::operator=(const myStack<Type>& rhs)
{
	if (*this != rhs)
	{
		*this = rhs;
	}

	return *this;
}

//destructor that deallocates the nodes in the stack class
template<class Type>
myStack<Type>::~myStack()
{
	node* temp = topOfmyStack;
	while (topOfmyStack != NULL)
	{
		temp = temp->next;
		delete topOfmyStack;
		topOfmyStack = temp;
	}
}

//pushes the nodes in reverse order, aka headInsert
template <class Type>
void myStack<Type>::push(const Type& insert)
{//aka headInsert
	node* temp = new node;
	temp->item = insert;
	temp->next = topOfmyStack;
	topOfmyStack = temp;
}

//pops the head node, aka headRemove
template <class Type>
void myStack<Type>::pop()
{//aka headRemove
	if (topOfmyStack == NULL)
	{
		return;
	}

	node* temp = topOfmyStack;
	topOfmyStack = topOfmyStack->next;
	delete temp;
	return;
}

//returns the top of the stack node
template <class Type>
Type myStack<Type>::top() const
{
	return topOfmyStack->item;
}

//checks to see if the stack is empty
template <class Type>
bool myStack<Type>::isEmpty() const
{
	if (topOfmyStack != NULL)
	{
		return false;
	}
	else
		return true;
}
