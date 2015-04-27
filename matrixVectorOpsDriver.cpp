/* Brent Hyman
 * April 26, 2015
 * CSCI 2270
 * Final Project
 * References:
 * -> http://www.cplusplus.com/reference/string/string/
 * Description: The matrix-vector ops driver.  
*/
#include <iostream>
#include <string>
#include <vector>
#include "matrixVectorOps.h"

using namespace std;

int main()
{
	cout << "*************************************************" << endl << endl;
	cout << "Welcome to the Matrix Vector Operations Program!" << endl;
	cout << "   -> created by Brent Hyman" << endl;
	cout << endl << "*************************************************" << endl;
	//set up an instance of the matrixVectorOps class
	matrixVectorOps MVO = matrixVectorOps(NULL);
	//decrlere variables for running the operations
	vector<double> newVector;
	vector<vector<double>> newMatrix;
	vector<double> solnVector;
	matrix matrixAdd;
	matrix matSoln;
	mathVector vectorAdd;
	BSTnode *temp;
	BSTnode *nodeOutput;
	BSTnode *vectorNode;
	BSTnode *vectorNode2;
	BSTnode *matrixNode;
	int delimiter;
	double soln;
	//declare varables for displaying the menu
	string userInput;
	int input;
	bool inOperation = true;
	while(inOperation) //while program in operation
	{
		// Main Menu Display
		cout << endl << "======Main Menu======" << endl;
		cout << "1. Input a vector" << endl;
		cout << "2. Input a matrix" << endl;
		cout << "3. Print a vector" << endl;
		cout << "4. Print a matrix" << endl;
		cout << "5. Print all vectors and matrices" << endl;
		cout << "6. Implement an inner product (vector-vector multiply) " << endl;
		cout << "7. Implement a matrix-vector multiply" << endl;
		cout << "8. Implement a Conjugate Gradient method on a linear system" << endl;
		cout << "9. Quit" << endl;
		//user picks an option		
		getline(cin,userInput);
		input = stoi(userInput); 	
		switch (input)
		{
			//===Input a vector===
			case 1:
			{
				cout << "Please input a vector" << endl;
				cout << "  ex) :5,8,9" << endl;
				cout << "     _   _" << endl;
				cout << "    |  5  |" << endl;
				cout << " -> |  8  |" << endl; 
				cout << "    |_ 9 _|" << endl;
				cout << " :"; 
				getline(cin,userInput);
				newVector = MVO.stringToVector(userInput);
				cout << "Variable name for this vector (lower case letter): " << endl;
				getline(cin,userInput);
				// add create and add mathVector to the BST
				vectorAdd.vectorName = userInput;
				vectorAdd.vectorElmts = newVector;
				vectorAdd.dim = newVector.size();
				temp = new BSTnode;
				temp->b = vectorAdd;
				temp->aMathVector = true;
				temp->aMatrix = false;
				MVO.addNode(temp);
				break;
			}
			//===Input a matrix===
			case 2:
			{
				cout << "Please input a matrix" << endl;
				cout << "  ex) :5,8,9|7,2,1|6,3,4" << endl;
				cout << "     _       _" << endl;
				cout << "    |  5 8 9  |" << endl;
				cout << " -> |  7 2 1  |" << endl; 
				cout << "    |_ 6 3 4 _|" << endl;
				cout << " :"; 
				getline(cin,userInput);
				newMatrix = MVO.stringToMatrix(userInput);
				cout << "Variable name for this matrix (upper case letter): " << endl;
				getline(cin,userInput);
				// add create and add matrix to the BST	
				matrixAdd.matrixName = userInput;
				matrixAdd.matrixElmts = newMatrix;
				matrixAdd.dim = newMatrix.size();
				temp = new BSTnode;
				temp->A = matrixAdd;
				temp->aMatrix = true;
				temp->aMathVector = false;
				MVO.addNode(temp);										
				break;
			}			
			//===Print a vector===
			case 3:
			{		
				cout << "Enter vector name: ";
				getline(cin,userInput);
				nodeOutput = MVO.BSTsearch(userInput);
				if(nodeOutput)
				{
					cout << endl;
					for(unsigned int i = 0; i < nodeOutput->b.vectorElmts.size(); i++)
					{
						cout << "   " << nodeOutput->b.vectorElmts.at(i) << endl;
					}					
				}
				else
				{
					cout << "Vector not found" << endl;
				}
				break;	
			}
			//===Print a matrix===
			case 4:
			{
				cout << "Enter matrix name: ";
				getline(cin,userInput);
				nodeOutput = MVO.BSTsearch(userInput);
				if(nodeOutput)
				{
					cout << endl;
					for(unsigned int j = 0; j < nodeOutput->A.matrixElmts.size(); j++)
					{
						cout << "   "; 
						for(unsigned int k = 0; k < nodeOutput->A.matrixElmts.size(); k++)
						{
							cout << nodeOutput->A.matrixElmts[j][k] << " ";
						}
						cout << endl;
					}					
				}
				else
				{
					cout << "Matrix not found" << endl;
				}
				break;			
			}
			//===Print all vectors and matrices===
			case 5:
			{
				cout << endl;
				MVO.printInventory(MVO.getRoot());
				break;				
			}
			//===inner product===
			case 6:
			{
				cout << "Enter a vector-vector product expression" << endl;
				cout << "ex) :c*b" << endl;
				cout << " :";
				getline(cin,userInput);
				delimiter = userInput.find("*");
				vectorNode = MVO.BSTsearch(userInput.substr(0,delimiter));
				vectorNode2 = MVO.BSTsearch(userInput.substr(delimiter+1,userInput.size()));				
				soln = MVO.innerProduct(vectorNode->b.vectorElmts, vectorNode2->b.vectorElmts);
				cout << endl << "   " << soln << endl;
				break;
			}
			//===Implement a matrix-vector multiply===
			case 7:
			{
				cout << "Enter a matrix-vector product expression" << endl;
				cout << "ex) :A*b" << endl;
				cout << " :";
				getline(cin,userInput);
				delimiter = userInput.find("*");
				matrixNode = MVO.BSTsearch(userInput.substr(0,delimiter));
				vectorNode = MVO.BSTsearch(userInput.substr(delimiter+1,userInput.size()));
				solnVector = MVO.matrixVectMult(matrixNode->A.matrixElmts, vectorNode->b.vectorElmts);
				cout << endl;
				for(unsigned int index = 0; index < solnVector.size(); index++)
				{
					cout << "   " << solnVector.at(index) << endl;
				}
				break;
			}
			//===Implement a Conjugate Gradient method on a linear system===
			case 8:
			{
				cout << "Enter an existing matrix-vector pair" << endl;
				cout << "ex) :A|b" << endl;
				cout << "  -> to solve for x in the system Ax = b" << endl;
				cout << " :";
				getline(cin,userInput);
				delimiter = userInput.find("|");
				matrixNode = MVO.BSTsearch(userInput.substr(0,delimiter));
				vectorNode = MVO.BSTsearch(userInput.substr(delimiter+1,userInput.size()));
				MVO.conjugateGradient(matrixNode->A.matrixElmts,vectorNode->b.vectorElmts);
				break;
			}
			//===Quit===		
			case 9:
				//stop the program
				inOperation = false;
				//free up allocated memory
				MVO.deleteTree(MVO.getRoot());
				//say goodbye
				cout << "Goodbye!" << endl;			
				break;							
			default:
			{
				cout << "Invalid Input" << endl;
				break;
			}
		}
	}	
	return 0;
}