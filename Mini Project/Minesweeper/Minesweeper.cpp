#include "Minesweeper.h"

int main()
{
	srand(time(0));
	mapInit();
	remain = m * n;
	setMine();
	gameProcess();

	return 0;
}

void mapInit()
{
	cout << "Number of row and column of matrix you want (mxn): \n";
	cin >> m >> n;
	system("cls");
	cout << "Number of mine you want: \n";
	cin >> k;
	for (int i = 0; i < m; i++) 
	{
		vector<int> u;
		vector<char> v;
		for (int j = 0; j < n; j++) 
		{
			u.push_back(0);
			v.push_back('.');
		}
		numMap.push_back(u);
		mineMap.push_back(v);
	}
}

void setMine()
{
	int i, j;
	int tmp = k;
	while (tmp > 0)
	{
		i = rand() % m;
		j = rand() % n;
		if (numMap[i][j] == -1) continue;
		else
		{
			numMap[i][j] = -1;
			//mineMap[i][j] = '*';
			setNum(i, j);
			tmp--;
		}
	}
}

void setNum(const int& i, const int& j)
{
	int tmp1, tmp2;
	for (int h = -1; h <= 1; h++) 
	{
		for (int p = -1; p <= 1; p++) 
		{
			tmp1 = i + h;
			tmp2 = j + p;
			if (tmp1 < 0 || tmp1 >= m || tmp2 < 0 || tmp2 >= n) continue;
			else if (numMap[tmp1][tmp2] != -1) numMap[tmp1][tmp2]++;
		}
	}
}

void display(bool over)
{
	char tmp;
	system("cls");
	for (int i = 0; i <= m; i++)
	{
		if (i == 0) cout << setw(4) << setfill(' ') << right << " ";
		else cout << setw(3) << setfill(' ') << right << i;
	}
	cout << endl;
	int size = (m + 1) * 3;
	cout << setw(size) << setfill('-') << left << "     " << endl;

	for (int i = 0; i < m; i++)
	{
		for (int j = -1; j < n; j++) 
		{
			if (j == -1)
			{
				cout << setw(3) << setfill(' ') << right << i+1 << "|";
			}
			else
			{
				if (over)
				{
					if (numMap[i][j] == -1) tmp = '*';
					else tmp = numMap[i][j] + '0';
				}
				else tmp = mineMap[i][j];
				cout << setw(3) << setfill(' ') << right << tmp;
			}
		}
		cout << endl;
	}
	/*
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++) {
			cout << numMap[i][j] << " ";
		}
		cout << endl;
	
	}
	*/
}

void gameProcess()
{
	int i, j;
	bool loop = true;
	while (loop)
	{
		int count = 1;
		display(false);
		do
		{
			if (count == 1) cout << "Let's choose 1 box: ";
			else cout << "This box has already been opened. Try another!";
			cin >> i >> j;
			i--; j--;
			count++;
		} while (!isOpen(i, j));
		if (gameOver(i, j))
		{
			display(true);
			loop = false;
		}
		else
		{
			mineMap[i][j] = numMap[i][j] + '0';
			remain--;
			if (numMap[i][j] == 0) spread(i,j);
		}
		if (Win())
		{
			system("cls");
			cout << "Congratulation. You win!";
			loop = false;
		}
	}
}

void spread(const int& i, const int& j)
{
	int tmp1, tmp2;
	for (int h = -1; h <= 1; h++)
	{
		for (int p = -1; p <= 1; p++)
		{
			tmp1 = i + h;
			tmp2 = j + p;
			if (tmp1 < 0 || tmp1 >= m || tmp2 < 0 || tmp2 >= n || (h == 0 && p == 0)) continue;
			else if (mineMap[tmp1][tmp2] == '.')
			{
				mineMap[tmp1][tmp2] = numMap[tmp1][tmp2] + '0';
				remain--;
				if (numMap[tmp1][tmp2] == 0) spread(tmp1, tmp2);
			}
		}
	}
}

bool isOpen(const int& i,const int& j)
{
	if (mineMap[i][j] == '.' || numMap[i][j] == -1) return true;
	return false;
}

bool gameOver(const int& i, const int& j)
{
	if (numMap[i][j] == -1) return true;
	return false;
}
bool Win()
{
	if (remain == k) return true;
	return false;
}
