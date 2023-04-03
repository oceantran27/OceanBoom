#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <ctime>
#include <random>
#include <string>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;

void mapInit();
void setMine();
void setNum(const int& i, const int& j);
void display(bool over);
void gameProcess();
bool isOpen(const int& i, const int& j);
bool gameOver(const int& i, const int& j);
bool Win();
void spread(const int& i, const int& j);


int m = 0, n = 0, k = 0;
int remain;
vector<vector<char>> mineMap;
vector<vector<int>> numMap;

#endif // !FUNCTION_H
