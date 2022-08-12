#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <conio.h>

using namespace std;

class Matrix {
	/// <summary>
	/// Content of the matrix represented by a 2d vector
	/// </summary>
	vector<vector<int>> numbers;

	/// <summary>
	/// Return vector of indexes of negative numbers from columns of 2d vector of matrixes numbers (used for formatted matrix print)
	/// </summary>
	/// <param name="column"></param>
	/// <returns></returns>
	vector<int> GetVectorOfHorizontalIndexesWithNegativeNumberIn2DVector()
	{
		vector<int> negativeIndexes;
		for (int i = 0; i < numbers.size(); i++)
		{
			for (int j = 0; j < numbers[i].size(); j++)
			{
				if (numbers[i][j] < 0)
				{
					negativeIndexes.push_back(j);
				}
			}
		}
		return negativeIndexes;
	}

	/// <summary>
	/// Return 2d vector of horizontal indexes and number of digits of the biggest number from a column in 2d vector of matrixes numbers (indexes are stored in the first row and number of digits in the second row)
	/// </summary>
	/// <param name="nums"></param>
	/// <returns></returns>
	vector<vector<int>> GetVectorOfIndexesOfMultipleDigitsFrom2DVector()
	{
		vector<vector<int>> multipleDigits;
		multipleDigits.resize(2);
		for (int i = 0; i < numbers.size(); i++)
		{
			for (int j = 0; j < numbers[i].size(); j++)
			{
				if (numbers[i][j] > 9 || numbers[i][j] < -9)
				{
					multipleDigits[0].push_back(j);
					multipleDigits[1].push_back(NumberOfDigits(numbers[i][j]));
				}
			}
		}
		return multipleDigits;
	}

	int NumberOfDigits(int number)
	{
		return (number < 0) ? to_string(number).length() - 1 : to_string(number).length();
	}

	/// <summary>
	/// Return index of the largest number from second row depending on the first row 
	/// </summary>
	/// <param name="vect"></param>
	/// <returns></returns>
	int FindLargestElementIn2DVector(vector<vector<int>> vect, int firstRowIndex)
	{
		int largestNumber = 0, indexWitLargestNumber = 0;
		for (int i = 0; i < vect[0].size(); i++)
		{
			if (vect[0][i] == firstRowIndex)
			{
				if (vect[1][i] > largestNumber)
				{
					largestNumber = vect[1][i];
					indexWitLargestNumber = i;
				}
			}
		}
		return indexWitLargestNumber;
	}

public:

	Matrix() { }

	Matrix(vector<vector<int>> input)
	{
		for (int i = 0; i < input.size(); i++)
		{
			numbers.resize(numbers.size() + 1);
			for (int j = 0; j < input[i].size(); j++)
			{
				numbers[i].push_back(input[i][j]);
			}
		}
	}

	/// <summary>
	/// Return true if two matrices have the same number of rows and columns
	/// </summary>
	/// <param name="firstMatrix"></param>
	/// <param name="secondMatrix"></param>
	/// <returns></returns>
	static bool AreMatricesValidForAdditionAndSubtraction(Matrix firstMatrix, Matrix secondMatrix)
	{
		if (firstMatrix.numbers.size() == secondMatrix.numbers.size())
		{
			if (firstMatrix.numbers[0].size() == secondMatrix.numbers[0].size())
			{
				return true;
			}
		}
		return false;
	}

	/// <summary>
	/// Return true if the first matrix have the same number of rows as the second matrix number of columns
	/// </summary>
	/// <param name="firstMatrix"></param>
	/// <param name="secondMatrix"></param>
	/// <returns></returns>
	static bool AreMatricesValidForMultiplication(Matrix firstMatrix, Matrix secondMatrix)
	{
		if (firstMatrix.numbers[0].size() == secondMatrix.numbers.size())
		{
			return true;
		}
		return false;
	}

	void Print()
	{
		vector<int> negativeIndexes = GetVectorOfHorizontalIndexesWithNegativeNumberIn2DVector();
		vector<vector<int>> multipleDigitIndexes = GetVectorOfIndexesOfMultipleDigitsFrom2DVector();
		int indexWithLargeNumber = 0;

		for (int i = 0; i < numbers.size(); i++)
		{
			for (int j = 0; j < numbers[i].size(); j++)
			{
				if (count(negativeIndexes.begin(), negativeIndexes.end(), j) && numbers[i][j] >= 0)
				{
					cout << " ";
				}
				if (count(multipleDigitIndexes[0].begin(), multipleDigitIndexes[0].end(), j))
				{
					indexWithLargeNumber = FindLargestElementIn2DVector(multipleDigitIndexes, j);
					for (int k = NumberOfDigits(numbers[i][j]); k < multipleDigitIndexes[1][indexWithLargeNumber]; k++)
					{
						cout << " ";
					}
				}
				cout << numbers[i][j] << " ";
			}
			cout << endl;
		}
	}

	void Transpose()
	{
		vector<vector<int>> transposedMatrix;
		for (int i = 0; i < numbers.size(); i++)
		{
			for (int j = 0; j < numbers[i].size(); j++)
			{
				if (transposedMatrix.size() < numbers[0].size())
				{
					transposedMatrix.resize(transposedMatrix.size() + 1);
				}
				transposedMatrix[j].push_back(numbers[i][j]);
			}
		}
		numbers = transposedMatrix;
	}

	void MultiplyByNumber(int multiplyBy)
	{
		for (int i = 0; i < numbers.size(); i++)
		{
			for (int j = 0; j < numbers[i].size(); j++)
			{
				numbers[i][j] *= multiplyBy;
			}
		}
	}

	static Matrix AddMatrices(Matrix firstMatrix, Matrix secondMatrix)
	{
		vector<vector<int>> sumOfMatrices;
		if (!AreMatricesValidForAdditionAndSubtraction(firstMatrix, secondMatrix))
		{
			return sumOfMatrices;
		}
		for (int i = 0; i < firstMatrix.numbers.size(); i++)
		{
			sumOfMatrices.resize(sumOfMatrices.size() + 1);
			for (int j = 0; j < firstMatrix.numbers[i].size(); j++)
			{
				sumOfMatrices[i].push_back(firstMatrix.numbers[i][j] + secondMatrix.numbers[i][j]);
			}
		}
		return Matrix(sumOfMatrices);
	}

	static Matrix SubtractMatrices(Matrix firstMatrix, Matrix secondMatrix)
	{
		vector<vector<int>> subOfMatrices;

		if (!AreMatricesValidForAdditionAndSubtraction(firstMatrix, secondMatrix))
		{
			return subOfMatrices;
		}
		for (int i = 0; i < firstMatrix.numbers.size(); i++)
		{
			subOfMatrices.resize(subOfMatrices.size() + 1);
			for (int j = 0; j < firstMatrix.numbers[i].size(); j++)
			{
				subOfMatrices[i].push_back(firstMatrix.numbers[i][j] - secondMatrix.numbers[i][j]);
			}
		}
		return Matrix(subOfMatrices);
	}

	static Matrix MultiplyMatrices(Matrix firstMatrix, Matrix secondMatrix)
	{
		vector<vector<int>> mutiplicationOfMatrices;
		Matrix tempForSwap;
		int multiplicationOfRowAndColumn = 0;

		if (!AreMatricesValidForMultiplication(firstMatrix, secondMatrix))
		{
			return mutiplicationOfMatrices;
		}
		if (firstMatrix.numbers[0].size() < secondMatrix.numbers[0].size())
		{
			tempForSwap = firstMatrix;
			firstMatrix = secondMatrix;
			secondMatrix = tempForSwap;
		}
		for (int i = 0; i < firstMatrix.numbers.size(); i++)
		{
			mutiplicationOfMatrices.resize(mutiplicationOfMatrices.size() + 1);
			for (int j = 0; j < secondMatrix.numbers[0].size(); j++)
			{
				for (int k = 0; k < firstMatrix.numbers[0].size(); k++)
				{
					multiplicationOfRowAndColumn += firstMatrix.numbers[i][k] * secondMatrix.numbers[k][j];
				}
				mutiplicationOfMatrices[i].push_back(multiplicationOfRowAndColumn);
				multiplicationOfRowAndColumn = 0;
			}
		}
		return Matrix(mutiplicationOfMatrices);
	}
};

bool IsStringNumber(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]) && str[i] != '-')
		{
			return false;
		}
	}
	return true;
}

/// <summary>
/// At address of variable count entered as parameter writes the count of numbers in string (separated by spaces)
/// </summary>
/// <param name="str"></param>
/// <param name="count"></param>
void CountOfNumbersInString(string str, int& count)
{
	count = 0;
	bool isNumberInString = false;
	for (int i = 0; i < str.length(); i++)
	{
		if (isalnum(str[i]))
		{
			if (isdigit(str[i]))
			{
				isNumberInString = true;
			}
		}
		else
		{
			if (isNumberInString)
			{
				count += 1;
			}
			isNumberInString = false;
		}
	}
	if (isNumberInString)
	{
		count += 1;
	}
}

/// <summary>
/// Into adress of vector entered as the parameter add a new row of numbers from the entered string
/// </summary>
/// <param name="vector2D"></param>
/// <param name="str"></param>
void AddRowTo2DVector(vector<vector<int>>& vector2D, string str)
{
	string rowNumber;
	int count;
	CountOfNumbersInString(str, count);
	if (count != 0)
	{
		vector2D.resize(vector2D.size() + 1);
	}
	for (int i = 0; i < str.length(); i++)
	{
		if (isalnum(str[i]) || str[i] == '-')
		{
			rowNumber += str[i];
		}
		else
		{
			if (rowNumber != "")
			{
				if (IsStringNumber(rowNumber))
				{
					vector2D[vector2D.size() - 1].push_back(stoi(rowNumber));
				}
				rowNumber = "";
			}
		}
	}
	if (rowNumber != "")
	{
		if (IsStringNumber(rowNumber))
		{
			vector2D[vector2D.size() - 1].push_back(stoi(rowNumber));
		}
	}
}

Matrix CreateMatrixFromInput()
{
	int countOfInsertedNumbersInRow, prevNumbersCount = 0;
	string inputFromConsole;
	vector<vector<int>> vect2d;

	getline(cin, inputFromConsole);
	while (!inputFromConsole.empty())
	{
		CountOfNumbersInString(inputFromConsole, countOfInsertedNumbersInRow);
		if (prevNumbersCount == 0)
		{
			prevNumbersCount = countOfInsertedNumbersInRow;
		}
		if (prevNumbersCount != countOfInsertedNumbersInRow)
		{
			cout << "Rows must have the same number of elements in each row" << endl;
		}
		else
		{
			AddRowTo2DVector(vect2d, inputFromConsole);
		}
		getline(cin, inputFromConsole);
	}
	Matrix matrix(vect2d);
	return matrix;
}

void DisplayMenu()
{
	Matrix m1, m2, add, sub, mul;
	string choice, multiplyBy;
	int convertedChoice, convertedMultiplyBy;
	cout << "Enter matrix A:" << endl;
	m1 = CreateMatrixFromInput();
	cout << "What do you want to do next?" << endl;
	cout << "1 - Enter matrix B (for addition, subtraction, multiplication)" << endl;
	cout << "2 - Transpose matrix A" << endl;
	cout << "3 - Multiply matrix A by a number" << endl;
	cout << endl;
	cin >> choice;
	convertedChoice = stoi(choice);
	while (0 >= convertedChoice || convertedChoice >= 4)
	{
		cout << "Please enter a number 1 - 3" << endl;
		cin >> choice;
		convertedChoice = stoi(choice);
	}
	switch (convertedChoice)
	{
	case 1:
		cout << "Enter matrix B:" << endl;
		cin.ignore();
		m2 = CreateMatrixFromInput();
		if (Matrix::AreMatricesValidForAdditionAndSubtraction(m1, m2))
		{
			cout << "A + B:" << endl;
			add = Matrix::AddMatrices(m1, m2);
			add.Print();
			cout << "\nA - B:" << endl;
			sub = Matrix::SubtractMatrices(m1, m2);
			sub.Print();
		}
		else if (Matrix::AreMatricesValidForMultiplication(m1, m2))
		{
			cout << "A * B:" << endl;
			mul = Matrix::MultiplyMatrices(m1, m2);
			mul.Print();
		}
		else
		{
			cout << "No operations can be performed on these matrices" << endl;
		}
		break;
	case 2:
		m1.Transpose();
		cout << "Transposed matrix A:" << endl;
		cin.ignore();
		m1.Print();
		break;
	case 3:
		cout << "Enter a number you want to multiply the matrix A by" << endl;
		cout << endl;
		cin >> multiplyBy;
		convertedMultiplyBy = stoi(multiplyBy);
		cin.ignore();
		m1.MultiplyByNumber(convertedMultiplyBy);
		cout << "Matrix A multiplied by " << multiplyBy << endl;
		m1.Print();
		break;
	}
	cout << "\nDo you want to run the program again? (y/n)" << endl;
}

int main()
{
	char runAgain;

	DisplayMenu();
	runAgain = _getch();
	while (runAgain != 'y' && runAgain != 'n')
	{
		runAgain = _getch();
	}
	while (runAgain == 'y' && runAgain != 'n')
	{
		system("CLS");
		DisplayMenu();
		runAgain = _getch();
		while (runAgain != 'y' && runAgain != 'n')
		{
			runAgain = _getch();
		}
	}
	return 0;
}