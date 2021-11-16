#include <iostream>

using namespace std;

template <class Type>
class vertex
{
	struct node
	{
		Type item;
		node* link;
	};
public:
	class edgeIterator
	{
	public:
		friend class vertex;
		edgeIterator();
		edgeIterator(node*);
		edgeIterator operator ++(int);
		Type operator *();
		bool operator ==(const edgeIterator&);
			bool operator !=(const edgeIterator&);
	private:
		node* current;
	};
	vertex();
	vertex(const vertex <Type>&);
	const vertex& operator =(const vertex <Type>&);
	~vertex();
	edgeIterator begin();
	edgeIterator end();
	void addEdge(const Type&);
private:
	node* neighbors;
};

//default constructor, sets current to NULL
template <class Type>
vertex<Type>::edgeIterator::edgeIterator()
{
	current = NULL;
}

//assign edge to current
template <class Type>
vertex<Type>::edgeIterator::edgeIterator(vertex<Type>::node* edge)
{
	current = edge;
}

//sets the iterator to point to the next node object
//sets current to point to the next node
template <class Type>
typename vertex<Type>::edgeIterator vertex<Type>::edgeIterator::operator++(int)
{
	current = current->link;
	return *this;
}

//return the item field current points to
template <class Type>
Type vertex<Type>::edgeIterator::operator*()
{
	return this->current->item;
}

//comarares the nodes of iterator and rhs, return true if equal, false if not
template <class Type>
bool vertex<Type>::edgeIterator::operator==(const vertex<Type>::edgeIterator& rhs)
{
	if (this->current == rhs.current)
	{
		return true;
	}
	else
		return false;
}

//compares the nodes of the iterator and rhs, return false if equal, true if not
template <class Type>
bool vertex<Type>::edgeIterator::operator!=(const vertex<Type>::edgeIterator& rhs)
{
	if (this->current == rhs.current)
	{
		return false;
	}
	else
		return true;
}

//constructor that sets neighbors to NULL
template <class Type>
vertex<Type>::vertex()
{
	neighbors = NULL;
}

//deep copys object into the this pointer
template <class Type>
vertex<Type>::vertex(const vertex<Type>& copy)
{
	*this = copy;
}

//deep copys rhs into this pointer
template <class Type>
const vertex<Type>& vertex<Type>::operator=(const vertex<Type>& rhs)
{
	node* temp = rhs->neighbors;
	this->neighbors->item = temp->item;
	if (rhs.neighbors == NULL)
	{
		neighbors = NULL;
	}

	while (temp != NULL)
	{
		addEdge(temp->item);
		temp = temp->link;
	}

	neighbors = temp;
}

//destructor to deallocate all of the nodes
template <class Type>
vertex<Type>::~vertex()
{
	node* temp = neighbors;
	while (neighbors != NULL)
	{
		temp = temp->link;
		delete neighbors;
		neighbors = temp;
	}
}

//returns the current object
template <class Type>
typename vertex<Type>::edgeIterator vertex<Type>::begin()
{
	vertex<Type>::edgeIterator A1;	//make a new edgeIterator
	A1.current = neighbors;
	return A1;
}

//assign the current object to NULL
template <class Type>
typename vertex<Type>::edgeIterator vertex<Type>::end()
{
	vertex<Type>::edgeIterator A1;	//make a new edgeIterator
	A1.current = NULL;
	return A1;
}

//insert node, aka head insert
template <class Type>
void vertex<Type>::addEdge(const Type& edge)
{
	node* temp = new node;
	temp->item = edge;
	temp->link = NULL;
	
	if (neighbors == NULL)
	{
		neighbors = temp;
	}
	else
	{
		temp->link = neighbors;
		neighbors = temp;
	}
}