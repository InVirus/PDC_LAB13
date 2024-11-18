#include "pch.h"
#include "CppUnitTest.h"
#include"../PDC_LAB13/source.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

void graphColoring(int** adjacencyMatrix, int n);

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
        TEST_METHOD(ValidGraphColoring)
        {
            int n = 4;
            int** adjacencyMatrix = new int* [n];
            for (int i = 0; i < n; ++i) {
                adjacencyMatrix[i] = new int[n] { 0 };
            }
            adjacencyMatrix[0][1] = adjacencyMatrix[1][0] = 1;
            adjacencyMatrix[1][2] = adjacencyMatrix[2][1] = 1;
            adjacencyMatrix[2][3] = adjacencyMatrix[3][2] = 1;
            adjacencyMatrix[3][0] = adjacencyMatrix[0][3] = 1;
            adjacencyMatrix[0][2] = adjacencyMatrix[2][0] = 1;

            graphColoring(adjacencyMatrix, n);

            for (int i = 0; i < n; ++i) {
                delete[] adjacencyMatrix[i];
            }
            delete[] adjacencyMatrix;
        }
    };
}
