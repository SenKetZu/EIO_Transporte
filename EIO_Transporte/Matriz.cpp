#include "Matriz.h"
#include <iostream>
//IMPORTANTE [FILAS][COLUMNAS]
Matriz::Matriz() :_MatrizOriginal({
	{ 8,6,10,9,35 },
	{9,12,13,7,50 },
	{14,9,16,5,40},
	{45,20,30,30,0}
	})
{
}

void Matriz::init()
{
	_MatrizAuxiliar = _MatrizOriginal;
	for (size_t i = 0; i < _MatrizAuxiliar.size()-1; i++)
	{
		for (size_t j = 0; j < _MatrizAuxiliar[0].size()-1; j++)
		{
			_MatrizAuxiliar[i][j] = 0;
		}
	}




	//_MatrizAuxiliar.clear();
	_MatrizFuncional.clear();

	std::vector<bool> auxbool;
	//std::vector<float> aux;

	for (auto e : _MatrizOriginal)
	{
		auxbool.clear();
		//aux.clear();
		for (auto f : e)
		{
			auxbool.push_back(true);
			//aux.push_back(0);
		}
		//_MatrizAuxiliar.push_back(aux);
		_MatrizFuncional.push_back(auxbool);
	}
}

void Matriz::NortWest()
{
	init();
	bool finish=false;

	
		for (size_t i = 0; i < _MatrizOriginal.size()-1; i++)
		{
			for (size_t j = 0; j < _MatrizOriginal[0].size()-1; j++)
			{
				Vector2f pos = { i,j };

				if (isborderCero(pos))continue;
				if (_MatrizFuncional[i][j])
				{					
					float cant = getMenor(getBorders(pos));
					restToBorders(pos, cant);
					_MatrizAuxiliar[i][j] = cant;
				}
			}
		}

		
		print();
}

void Matriz::MinorCost()
{
	init();

	while (!allBorderCero())
	{
		Vector2f pos = minorPos();
		float cant = getMenor(getBorders(pos));
		restToBorders(pos, cant);
		_MatrizAuxiliar[pos.x][pos.y] = cant;
		_MatrizFuncional[pos.x][pos.y] = false;	

	}


	




	print();

}

void Matriz::print()
{
	for (size_t i = 0; i < _MatrizOriginal.size() - 1; i++)
	{
		for (size_t j = 0; j < _MatrizOriginal[0].size() - 1; j++)
		{
			std::cout << "|" << _MatrizOriginal[i][j] << "|";
		}
		std::cout << std::endl;
	}
	
	std::cout << "---------------------------------" << std::endl;



	for (size_t i = 0; i < _MatrizAuxiliar.size()-1; i++)
	{
		for (size_t j = 0; j < _MatrizAuxiliar[0].size()-1; j++)
		{
			std::cout << "|" << _MatrizAuxiliar[i][j] << "|";
		}
		std::cout << std::endl;
	}

	std::cout << "---------------------------------" << std::endl;




	_MatrizFinal.clear();
	std::vector<int> aux;
	for (size_t i = 0; i < _MatrizOriginal.size() - 1; i++)
	{
		aux.clear();
		for (size_t j = 0; j < _MatrizOriginal[0].size() - 1; j++)
		{
			int cant;
			cant = _MatrizOriginal[i][j] * _MatrizAuxiliar[i][j];
			aux.push_back(cant);
		}
		_MatrizFinal.push_back(aux);
	}


	for (auto e : _MatrizFinal)
	{
		for (auto f : e)
		{
			std::cout << "|" << f << "|";
		}
		std::cout << std::endl;
	}
	std::cout << "---------------------------------" << std::endl;



	int total = 0;

	for (auto e : _MatrizFinal)
	{
		for (auto f : e)
		{
			total += f;
		}
	}

	std::cout << "Total: $" << total<<std::endl;
	std::cout << "---------------------------------" << std::endl;

	_MatrizAuxiliar.clear();
}

float Matriz::getMenor(float a, float b)
{
	if (a < b)return a;
	if (b < a)return b;
	return a;
}

float Matriz::getMenor(Vector2f posFilCol)
{
	if (posFilCol.x < posFilCol.y)return posFilCol.x;
	if (posFilCol.y < posFilCol.x)return posFilCol.y;
	return posFilCol.x;
}

Vector2f Matriz::getBorders(Vector2f posFilCol)
{
	Vector2f aux;
	aux.x = _MatrizAuxiliar[_MatrizOriginal.size() - 1][posFilCol.y];
	aux.y = _MatrizAuxiliar[posFilCol.x][_MatrizOriginal[0].size() - 1];

	return aux;
}

void Matriz::restToBorders(Vector2f posFilCol, float cant)
{
	_MatrizAuxiliar[_MatrizOriginal.size() - 1][posFilCol.y] -= cant;
	_MatrizAuxiliar[posFilCol.x][_MatrizOriginal[0].size() - 1] -= cant;
}

bool Matriz::isborderCero(Vector2f posFilCol)
{
	return !getMenor(getBorders(posFilCol));
}

bool Matriz::allBorderCero()
{
	bool flag = true;

	for (size_t i = 0; i < _MatrizAuxiliar.size()-1; i++)
	{
		for (size_t j = 0; j < _MatrizAuxiliar[0].size()-1; j++)
		{
			Vector2f pos = { i,j };
			if (!isborderCero(pos))flag=false;
		}
	}
	return flag;
}

Vector2f Matriz::minorPos()
{
	int minor;
	Vector2f pos;

	bool flag = true;
	for (size_t i = 0; i < _MatrizFuncional.size()-1; i++)
	{
		for (size_t j = 0; j < _MatrizFuncional[0].size() - 1; j++)
		{
			if (_MatrizFuncional[i][j]&&flag)
			{
				minor = _MatrizOriginal[i][j];
				pos.x = i;
				pos.y = j;
				flag = false;

			}
		}
	}


	

	for (size_t i = 0; i < _MatrizOriginal.size()-1; i++)
	{
		for (size_t j = 0; j < _MatrizOriginal[0].size() - 1; j++)
		{
			if (_MatrizOriginal[i][j] < minor&&_MatrizFuncional[i][j])
			{
				minor = _MatrizOriginal[i][j];
				pos.x = i;
				pos.y = j;
			}
		}
	}
	return pos;
}

