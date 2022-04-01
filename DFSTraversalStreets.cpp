#include <iostream>
#include <unordered_map>
#include <fstream>
#include "vertex.h"
#include "stack.h"


using namespace std;

//function declaration prototype
//contains the current string, "Start street"
//final destination, "End street"
//graph adjacency list, used to traverse through each nodes neighbors
//nodesInPath, will mark the node as true if there is a path, false otherwsie
//recStack, will contain the nodes in the path so they can be used for output
	//when current = finalDestination
//pathNo is the amount of paths in the list
//and use will keep track of the starting street
bool getPaths(string current, string finalDestination,
	unordered_map<string, vertex<string>>& graph,
	unordered_map<string, bool>& nodesInPath,
	myStack<string>& recStack, int& pathNo, string use);

int main()
{
	string source = " ";									//variable to read in the starting street
	string dest = " ";										//variable to read in destination street
	unordered_map<string, vertex<string>> adjList;			//adjacency list by using an unordered map
	unordered_map<string, bool> nop;						//unorderpath for the number of paths in the list
	myStack<string> A;										//stack to keep track of path
	int pathNum = 0;										//to keep track of the amount of paths in the list

	//file variables to help open file
	//try to open the file
	ifstream infile;										
	bool check = true;
	string name = "";
	string one = " ";
	string two = " ";

	while (check)
	{
		cout << "Last one ): ";
		cin >> name;
		infile.open(name);
		if (infile)
			check = false;
	}

	cout << endl;

	infile >> source >> dest;		//read in the source and destination string

	//cout << source << dest << endl;

	while (infile >> one >> two)	//a single edge (from and to street name)
	{
		adjList[one].addEdge(two);
	}

	bool solve = getPaths(source, dest, adjList, nop, A, pathNum, source);
	
	/*vertex<string>::edgeIterator it;
	vertex<string>::edgeIterator nil;
	nil = adjList["Last"].end();
	//nodes in path are true

	for (it = adjList["Last"].begin(); it != nil; it++)
	{
		cout << *it << endl;
	}
	*/
	return 0;
}

//returns true if a path existed
//returns false if no such path from start to end
//string current is similar to int c in DFS function
//nodes in path marks what strings are in our path
//outputs the path number and the path from current to finalDestination
bool getPaths(string current, string finalDestination,
	unordered_map<string, vertex<string>>& graph,
	unordered_map<string, bool>& nodesInPath,
	myStack<string>& recStack, int& pathNo, string use)
{   
	//base case to check if current equals finalDestination, if it does
	//create a temporary stack and copy recStack into it
	//and output the path number, along with the path
	if (current == finalDestination)				//base case we have found a //solution
	{
		//increment pathNo
		pathNo++;
		cout << "Path " << pathNo << ": ";
		myStack<string> temp;
		while (recStack.isEmpty() == false)
		{
			temp.push(recStack.top());
			recStack.pop();
		}

		if (pathNo > 1)
		{
			cout << use << " <=> ";
		}

		//output the path in the list
		if (temp.isEmpty() == false)
		{
			while (temp.isEmpty() == false)
			{
				if (temp.top() == finalDestination)
				{
					cout << temp.top() << endl;
				}
				else
				{
					cout << temp.top() << " <=> ";
				}
				temp.pop();
			}
			cout << finalDestination << endl;
		}

		else
		{
			cout << "No path was found :(" << endl;
		}

		return true;
	}

	nodesInPath[current] = true;
	recStack.push(current);

	//Create three edge iterators to iterate throught the nodes neighbors
	//to see if a path exists in the function, and if it does not, pop the recStack
	//and make nodesInPath[current] = false, and then return false.
	//If a case is found, create a bool variable and set it equal to getPaths by passing
	//in the iterator by using the dereference operator.
	
	vertex<string>::edgeIterator it;
	vertex<string>::edgeIterator nil;
	vertex<string>::edgeIterator it_2;

	nil = graph[current].end();			//will help us iterate throught the adjacency list

	for (it = graph[current].begin(); it != nil; it++)
	{
		if (nodesInPath[*it] == false)						//see if a node is in our path, if not, then execute the 
		{													//if statement
			for (it_2 = graph[*it].begin(); it_2 != NULL; it_2++)
			{
				if (*it_2 == current)		//to see if a two way path exists, then we use recrusion to call getPaths
				{
					//means that path was found, so use recursion and pass in the iterator
					bool checkIt = getPaths(*it, finalDestination, graph, nodesInPath, recStack, pathNo, use);
				}
			}
		}
	}

	//if no path was found, pop the stack, set the node equal to false, and return false
	recStack.pop();
	nodesInPath[current] = false;
	return false;
}
















/*
		vertex<string>::edgeIterator it;
		vertex<string>::edgeIterator nil;
		nil = graph[current].end();

		for (it = graph[current].begin(); it != nil; it++)
		{
			if (nodesInPath[*it] == false)
			{
				vertex<string>::edgeIterator it_2;
				vertex<string>::edgeIterator nil_2;
				nil_2 = graph[*it].end();

				for (it_2 = graph[*it].begin(); it_2 != nil_2; it_2++)
				{
					if (*it_2 == current)
					{
						nodesInPath[*it] = true;
						recStack.push(*it);
						return true;
					}
*/

	
