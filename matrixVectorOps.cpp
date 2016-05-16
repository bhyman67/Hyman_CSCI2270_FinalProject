/* Brent Hyman
 * April 26, 2015
 * CSCI 2270
 * Final Project
 * References:
 * -> http://www.cplusplus.com/reference/string/string/
 * Description: Function definitions for each of the methods in the
 * matrixVectorOps class.
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "matrixVectorOps.h"

using namespace std;

				////////////////////////////////
				//   Class structure functs   //
				////////////////////////////////
//************************************************************************
// The Constructor
//	-> Input: BSTnode (but will be a BSTnode always equal to NULL)
//      -> output: none
//	-> Description: When an instance of the matrixVectorOps class is
//         declared, the constructor gets called and automatically sets the
//         root of the BST to NULL
//************************************************************************
matrixVectorOps::matrixVectorOps(BSTnode *node)
{
	root = node;
}
//************************************************************************
// Root getter method
//	-> Input: none
//      -> output: the BSTnode in the BST that is the root
//	-> Description: gets the BST root
//************************************************************************
BSTnode *matrixVectorOps::getRoot()
{
	return root;
}
//************************************************************************
// The Destructor
//	-> Input: Root of the BST
//      -> output: none
//	-> Description: deletes the BST for deallocating memeory and
//         preventing memory leaks
//************************************************************************
void matrixVectorOps::deleteTree(BSTnode *root)
{
	if(root != NULL)
	{
		deleteTree(root->leftChild);
		delete root;
		deleteTree(root->rightChild);
	}
}
					////////////////////////
					//   BST operations   //
					////////////////////////
//************************************************************************
// Add node funct
//	-> Input: BSTnode to be added into the BST
//      -> output: none
//	-> Description: Adds given BSTnode into BST. VECTOR VARIABLE NAMES
//         NEED TO BE IN LOWER CASE AND MATRIX VARIABLE NAMES NEED TO BE
//         UPPER CASEED.
//************************************************************************
void matrixVectorOps::addNode(BSTnode *node)
{
	BSTnode *y = NULL;
	BSTnode *x = root;
	if(node->aMathVector)
	{
		while(x != NULL)
		{
			y = x;
			if(x->aMathVector)
			{
				if(keyCompare(node->b.vectorName, x->b.vectorName))
				{
					x = x->leftChild;
				}
				else
				{
					x = x->rightChild;
				}
			}
			else
			{
				if(keyCompare(node->b.vectorName, x->A.matrixName))
				{
					x = x->leftChild;
				}
				else
				{
					x = x->rightChild;
				}
			}
		}
		node->parent = y;
		if(y == NULL)
		{
			root = node;
		}
		else if(y->aMathVector)
		{
			if(keyCompare(node->b.vectorName, y->b.vectorName))
			{
				y->leftChild = node;
			}
			else
			{
				y->rightChild = node;
			}
		}
		else
		{
			if(keyCompare(node->b.vectorName, y->A.matrixName))
			{
				y->leftChild = node;
			}
			else
			{
				y->rightChild = node;
			}
		}
	}
	else
	{
		while(x != NULL)
		{
			y = x;
			if(x->aMathVector)
			{
				if(keyCompare(node->A.matrixName, x->b.vectorName))
				{
					x = x->leftChild;
				}
				else
				{
					x = x->rightChild;
				}
			}
			else
			{
				if(keyCompare(node->A.matrixName, x->A.matrixName))
				{
					x = x->leftChild;
				}
				else
				{
					x = x->rightChild;
				}
			}
		}
		node->parent = y;
		if(y == NULL)
		{
			root = node;
		}
		else if(y->aMathVector)
		{
			if(keyCompare(node->A.matrixName, y->b.vectorName))
			{
				y->leftChild = node;
			}
			else
			{
				y->rightChild = node;
			}
		}
		else
		{
			if(keyCompare(node->A.matrixName, y->A.matrixName))
			{
				y->leftChild = node;
			}
			else
			{
				y->rightChild = node;
			}
		}
	}
}
//************************************************************************
// BST search funct
//	-> Input: name (in form of a string) of matrix or vector the user is
//         searching for
//      -> output: BSTnode of the matched matrix or vector
//	-> Description: Searchs for the desired matrix or vector in the BST
//************************************************************************
BSTnode *matrixVectorOps::BSTsearch(string nodeLabel)
{
	//iterative binary tree search algorithm
	bool match = false;
	BSTnode *foundNode = root;
	while(foundNode != NULL && !match)
	{
		if(foundNode->aMathVector)
		{
			if(!nodeLabel.compare(foundNode->b.vectorName))
			{
				match = true;
			}
			else if(keyCompare(nodeLabel, foundNode->b.vectorName))
			{
				foundNode = foundNode->leftChild;
			}
			else
			{
				foundNode = foundNode->rightChild;
			}

		}
		else
		{
			if(!nodeLabel.compare(foundNode->A.matrixName))
			{
				match = true;
			}
			else if(keyCompare(nodeLabel, foundNode->A.matrixName))
			{
				foundNode = foundNode->leftChild;
			}
			else
			{
				foundNode = foundNode->rightChild;
			}
		}
	}
	return foundNode;
}
//************************************************************************
// Print Inventory funct
//	-> Input: BST root
//      -> output: none
//	-> Description: Prints out all of the BSTnodes (both the variable
//         variable names and the actual matrcies and vectors themselves)
//************************************************************************
void matrixVectorOps::printInventory(BSTnode *root)
{
	if(root != NULL)
	{
		printInventory(root->leftChild);
		if(root->aMathVector)
		{
			cout << " " << root->b.vectorName << ":" << endl;
			cout << endl;
			for(unsigned int i = 0; i < root->b.vectorElmts.size(); i++)
			{
				cout << "   " << root->b.vectorElmts.at(i) << endl;
			}
		}
		else
		{
			cout << " " << root->A.matrixName << ":" << endl;
			cout << endl;
			for(unsigned int j = 0; j < root->A.matrixElmts.size(); j++)
			{
				cout << "   ";
				for(unsigned int k = 0; k < root->A.matrixElmts.size(); k++)
				{
					cout << root->A.matrixElmts[j][k] << " ";
				}
				cout << endl;
			}
		}
		printInventory(root->rightChild);
	}
}
					///////////////////////////
					//   Matrix-Vector ops   //
					///////////////////////////
//************************************************************************
// Inner product funct
//	-> Input: two vectors for the function to take the dot product of.
//      -> output: the inner product of the two vectors
//	-> Description: Calcuates the inner product between two vectors
//************************************************************************
double matrixVectorOps::innerProduct(vector<double> a, vector<double> b)
{
	double intReturn = 0;
	if(a.size() == b.size())
	{
		for(unsigned int i = 0; i < a.size(); i++)
		{
			intReturn += ( a.at(i) * b.at(i) );
		}
	}
	else
	{
		cout << "Dimensions don't agree." << endl;
	}
	return intReturn;
}
//************************************************************************
// Matrix-Vector multiplication funct
//	-> Input: A 2-dim vector, in other words a matrix, that was from the
//         input of an upper case matrix name that already exists in the BST
//         AND a vector that was from the input of a lower case vector name that
//         already exists in the BST.
//      -> output: the calculated vector solution of the matrix-vector product.
//	-> Description: Calculates the product (which will be in the form of
//         a vector) of a matrix and a vector.
//************************************************************************
vector<double> matrixVectorOps::matrixVectMult(vector<vector<double>> A, vector<double> b)
{
	if(A.size() == b.size())
	{
		vector<double> solnVector( b.size() );
		for(unsigned int i = 0; i < solnVector.size(); i++)
		{
			solnVector.at(i) = 0;
			for(unsigned int j = 0; j < solnVector.size(); j++)
			{
				solnVector.at(i) += (b.at(j)*A[i][j]) ;
			}
		}
		return solnVector;
	}
	else
	{
		cout << "Dimensions don't agree." << endl;
		vector<double> emptyVect;
		return emptyVect;
	}
}
//************************************************************************
// Linear System Solver using the CONJUGATE GRADIENT METHOD
//	-> Input: A 2-dim vector, in other words a matrix, that was from the
//         input of an upper case matrix name that already exists in the BST
//         AND a vector that was from the input of a lower case vector name that
//         already exists in the BST.
//      -> output: the calculated vector solution of the linear system.
//	-> Description: This method would be most confusing to a user who
//         is unfamiliar with numerical linear algebra. This is an algorithm
//         used for solving linear systems that consist of symetric and
//	   positive-definte matrices. It is a popular method to use for
//         solving linear systems that get derived from a finite difference
//         approximation for solving a partial diffEq problems. In the case
//         that the user is unfamiliar with these kinds of matrices, I have
//         listed a set of matrices to use for a linear system whose solution
//         can be found using this method:
//		           _      _          _       _
//			  |  4  1  |        |  2  -1  |
//		   	  |_ 1  3 _|        |_ -1  2 _|
//                                 _      _
//                                |  3  2  |
//                                |_ 2  6 _|
//************************************************************************
void matrixVectorOps::conjugateGradient(vector<vector<double>> A, vector<double> b)
{
    if(A.size() == b.size())
    {
        int i = 0;
        double alpha;
        double beta;
        double oldDelta;
        vector<double> q;
        vector<double> x;
        for(unsigned int j = 0; j < b.size(); j++)
        {
            x.push_back(0);
        }
        vector<double> r = vectorDiff(b,matrixVectMult(A,x));
        vector<double> v = r;
        double delta = innerProduct(r,r);
        while(i < 100 && innerProduct(v,v) > 0.1 && innerProduct(r,r) > 0.1)
        {
            q = matrixVectMult(A,v);
            alpha = (delta) / (innerProduct(v,q));
            x = vectorSum(x,vectorScale(alpha,v));
            r = vectorDiff(r,vectorScale(alpha,q));
            oldDelta = delta;
            delta = innerProduct(r,r);
            beta = delta/oldDelta;
            v = vectorSum(r,vectorScale(beta,v));
            i++;
        }
        cout << endl;
        for(unsigned int k = 0; k < x.size(); k++)
        {
            cout << "   " << x.at(k) << endl;
        }
    }
	else
	{
		cout << "Dimensions don't agree." << endl;
	}
}
					///////////////////////
					//   helper functs   //
					///////////////////////
//************************************************************************
// key Compare funct
//	-> Input: two string parameters
//      -> output: true if the first string is "less than" the second,
//         else false.
//	-> Description: This function is used for comparing the ASCII code of
//         the variable names of the vectors and matricies for maintaing the
//         BST property when adding them into the BST
//************************************************************************
bool matrixVectorOps::keyCompare(string one, string two)
{
	bool inequality = false;
	int i = 0;
	while(one[i] == two[i])
	{
		i++;
	}
	if(one[i] < two[i])
	{
		inequality = true;
	}
	return inequality;
}
//************************************************************************
// String to vector function
//	-> Input: input string (from the user) for creating a vector
//      -> output: the actual math vector (one dimensional c++ vector) that
//         the user intended to input
//	-> Description: takes the users string vector input and actually
//         turns it into a vector
//************************************************************************
vector<double> matrixVectorOps::stringToVector(string line)
{
	vector<double> vectorReturn;
	string num;
	int numInt;
	int oldDelimiter;
	int lastCommaPos = line.find_last_of(",");
	int delimiter = line.find(",");
	num = line.substr(0,delimiter);
	numInt = stoi(num);
	vectorReturn.push_back(numInt);
	bool EOL = false; //End Of Line
	while(!EOL)
	{
		if(delimiter == lastCommaPos)
		{
			EOL = true;
		}
		oldDelimiter = delimiter+1;
		delimiter = line.find(",",oldDelimiter);
		num = line.substr(oldDelimiter, delimiter-oldDelimiter);
		numInt = stoi(num);
		vectorReturn.push_back(numInt);
	}
	return vectorReturn;
}
//************************************************************************
// String to matrix function
//	-> Input: input string (from the user) for creating a matrix
//      -> output: the actual matrix (two dimensional c++ vector) that
//         the user intended to input
//	-> Description: takes the users string matrix input and actually
//         turns it into a matrix
//************************************************************************
vector<vector<double>> matrixVectorOps::stringToMatrix(string line)
{
	//variables and vectors used in this function
	bool EOL; //End Of Line
	int numInt;
	int delimiter;
	int lastCommaPos;
	int oldDelimiter;
	vector<double> row;
	vector<int> delimiterVector;
	vector<vector<double>> vectorReturn;
	//need to separate the rows
	int amtOfRows = 0;
	for(unsigned int i = 0; i <= line.size(); i++)
	{
		if(line[i] == '|')
		{
			delimiterVector.push_back(i);
			amtOfRows++;
		}
	}
	amtOfRows++;
	delimiterVector.push_back(line.size());
	// -> this is the first row. The remaining rows will be put as this string as the loop runs
	string matrixRow = line.substr(0,delimiterVector.at(0));
	for(int j = 0; j < amtOfRows; j++)
	{
		//for each row, need to extract the numbers out of the string and put them in the matrix row
		lastCommaPos = matrixRow.find_last_of(",");
		delimiter = matrixRow.find(",");
		string num = matrixRow.substr(0,delimiter);
		numInt = stoi(num);
		row.push_back(numInt);
		EOL = false;
		while(!EOL)
		{
			if( delimiter == lastCommaPos )
			{
				EOL = true;
			}
			oldDelimiter = delimiter+1;
			delimiter = matrixRow.find(",",oldDelimiter);
			string num = matrixRow.substr(oldDelimiter, delimiter-oldDelimiter );
			numInt = stoi(num);
			row.push_back(numInt);
		}
		vectorReturn.push_back(row);
		row.clear();
		if(j != amtOfRows-1)
		{
			matrixRow = line.substr(delimiterVector.at(j)+1,(delimiterVector.at(j+1)-(delimiterVector.at(j)+1)));
		}
	}
	return vectorReturn;
}
//************************************************************************
// Vector scale funct
//	-> Input: a scaler number (of type double) and a vector
//      -> output: the scaled vector
//	-> Description: scales a vector
//************************************************************************
vector<double> matrixVectorOps::vectorScale(double a, vector<double> b)
{
	vector<double> vectorReturn;
	for(unsigned int i = 0; i < b.size(); i++)
	{
		vectorReturn.push_back(a*b.at(i));
	}
	return vectorReturn;
}
//************************************************************************
// Vector sum funct
//	-> Input: two vectors
//      -> output: a vector
//	-> Description: adds two vectors
//************************************************************************
vector<double> matrixVectorOps::vectorSum(vector<double> a, vector<double> b)
{
	vector<double> vectorReturn;
	for(unsigned int i = 0; i < a.size(); i++)
	{
		vectorReturn.push_back(a.at(i) + b.at(i));
	}
	return vectorReturn;
}
//************************************************************************
// Vector diff funct
//	-> Input: two vectors
//      -> output: a vector
//	-> Description: subtracts two vectors
//************************************************************************
vector<double> matrixVectorOps::vectorDiff(vector<double> a, vector<double> b)
{
	vector<double> vectorReturn;
	for(unsigned int i = 0; i < a.size(); i++)
	{
		vectorReturn.push_back(a.at(i) - b.at(i));
	}
	return vectorReturn;
}
//************************************************************************
// Vector output funct
//	-> Input: a vector
//      -> output: none
//	-> Description: for in case there is a need to output the vector
//         (maybe for graphing reasons...)
//************************************************************************
void matrixVectorOps::vectorOutput(std::vector<double> output)
{
	ofstream outputFile;
	outputFile.open("outputFile.dat");
	for(unsigned int i = 0; i < output.size(); i++)
	{
		outputFile << output.at(i) << endl;
	}
	outputFile.close();
}
