#pragma once
#include <vector>
#include "Header.h"
//IMPORTANTE [FILAS][COLUMNAS]
class Matriz
{
public:
	Matriz();
	void init();
	void NortWest();
	void MinorCost();
	void print();
private:
	float getMenor(float a, float b);
	float getMenor(Vector2f posFilCol);
	Vector2f getBorders(Vector2f posFilCol);
	void restToBorders(Vector2f posFilCol, float cant);
	bool isborderCero(Vector2f posFilCol);
	bool allBorderCero();
	Vector2f minorPos();
	std::vector<std::vector<int>> _MatrizOriginal;
	std::vector<std::vector<int>> _MatrizAuxiliar;
	std::vector<std::vector<bool>> _MatrizFuncional;
	std::vector<std::vector<int>> _MatrizFinal;
	float _CostoFinal;

};

