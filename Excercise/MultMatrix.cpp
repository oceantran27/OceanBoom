#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> readMatrix();
vector<vector<int>> multMatrix(vector<vector<int>> matrix1, vector<vector<int>> matrix2);
void printMatrix(vector<vector<int>> matrix);

int main() 
{
	
	vector<vector<int>> matrix1, matrix2, r_matrix;
	matrix1 = readMatrix();
	matrix2 = readMatrix();
	for (int i = 2; i <= 10; i++)
	{
		r_matrix = multMatrix(matrix1, matrix2);
		matrix1 = r_matrix;
		cout << "mu " << i << ":" << endl;
		printMatrix(r_matrix);
	}

	return 0;
}

vector<vector<int>> readMatrix() 
{
	int m, n, tmp; cin >> m >> n;
	vector<vector<int>> matrix;
	for (int i = 0; i < m; i++) 
	{
		matrix.push_back(vector<int>());
		for (int j = 0; j < n; j++) 
		{
			cin >> tmp;
			matrix[i].push_back(tmp);
		}
	}
	return matrix;
}

vector<vector<int>> multMatrix(vector<vector<int>> matrix1, vector<vector<int>> matrix2)
{
	int m, n, tmp; 
	m = matrix1.size();
	n = matrix2.size();
	vector<vector<int>> r_matrix;
	for (int i = 0; i < m; i++)
	{
		r_matrix.push_back(vector<int>());
		for (int j = 0; j < m; j++)
		{
			tmp = 0;
			for (int k = 0; k < n; k++)
			{
				tmp += matrix1[i][k]*matrix2[k][j];
			}
			r_matrix[i].push_back(tmp);
		}
	}
	return r_matrix;
}

void printMatrix(vector<vector<int>> matrix)
{

	for(auto i: matrix)
	{
		for (auto j: i)
		{
			cout << j << " ";
		}
		cout << endl;
	}
		cout << endl;
}