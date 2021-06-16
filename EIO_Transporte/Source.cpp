#include <iostream>
#include <vector>
#include "Vector2.h"





int main()
{

	std::vector<std::vector<float>> matriz =
	{
		{10,2 ,20,11},
		{12,7 ,9 ,20},
		{4 ,14,16,18}
	};
	std::vector<float>
		oferta=
		{15,25,10},

		demanda=
		{5,15,15,15};


	std::cout << matriz[0][1];
	//testeo lectura de matriz completa
	for (auto e : matriz)
	{
		for (auto f : e)
		{
			//std::cout << f<<std::endl;
		}
	}



	//Menor costo
	//copia de la matriz









	return 0;
}