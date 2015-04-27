/* Brent Hyman
 * April 26, 2015
 * CSCI 2270
 * Final Project
 * Description: Declares the matrix, mathVector, and BSTnode structs. 
 * The code library is in the form of a BST and each node stores either
 * a vector or a matrix.  
*/
#ifndef MATRIXVECTOROPS_H
#define MATRIXVECTOROPS_H
#include <vector>
#include <string>

struct matrix
{
	std::string matrixName;
	std::vector<std::vector<double>> matrixElmts;
	int dim;
};

struct mathVector
{
	std::string vectorName;
	std::vector<double> vectorElmts;
	int dim;
};

struct BSTnode
{
	//nodes in the BST represent either a vector or a matrix
	matrix A;
	bool aMatrix;
	mathVector b;
	bool aMathVector;
	//parent and children of the node
	BSTnode *parent = NULL;
	BSTnode *rightChild = NULL;
	BSTnode *leftChild = NULL;
};

class matrixVectorOps
{
    private:
		BSTnode *root; 
    public:
		//Class structure functs
		matrixVectorOps(BSTnode *node);
		BSTnode *getRoot();
		void deleteTree(BSTnode *root);
		//BST operations
		void addNode(BSTnode *node);
		BSTnode *BSTsearch(std::string nodeLabel);
		void printInventory(BSTnode *root);
		//Matrix-Vector ops
		double innerProduct(std::vector<double> a, std::vector<double> b); 
		std::vector<double> matrixVectMult(std::vector<std::vector<double>> A, std::vector<double> b);
		void conjugateGradient(std::vector<std::vector<double>> A, std::vector<double> b);
		//helper functs
		bool keyCompare(std::string one, std::string two);
		std::vector<double> stringToVector(std::string line);
		std::vector<std::vector<double>> stringToMatrix(std::string line);
		std::vector<double> vectorScale(double a, std::vector<double> b);
		std::vector<double> vectorSum(std::vector<double> a, std::vector<double> b);
		std::vector<double> vectorDiff(std::vector<double> a, std::vector<double> b);
		void vectorOutput(std::vector<double> output);
};

#endif // MATRIXVECTOROPS_H
