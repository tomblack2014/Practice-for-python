/*********************************************************************
 *
 *	@file		Calculation.cpp
 *	@brief		 Some algorithms
 *
 *
 *	Date		    Name			  Description
 *	08/02/15	    tomblack		  Creation.
 *
 *********************************************************************/

#include <climits>
#include <algorithm>

#include "Calculation.h"


int Calculation::
Kuhn_Munkres(const int weight[], const int n, int ret[])
{
	int m = n;
	int * lx = new int[m], *ly = new int[n];
	bool * visX = new bool[m], *visY = new bool[n];

	std::fill(lx, lx + m, INT_MIN);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			lx[i] = std::max(lx[i], weight[i * m + j]);

	std::fill(ly, ly + n, 0);
	std::fill(ret, ret + m, -1);

	for (int k = 0; k < n; k++) {
		while (true) {

			std::fill(visX, visX + m, false);
			std::fill(visY, visY + n, false);
			if (DFS_ForKM(k, m, weight, visX, visY, lx, ly, ret))
				break;

			int minWeight = INT_MAX;
			for (int i = 0; i < n; i++)
				if (visX[i])
					for (int j = 0; j < m; j++)
						if (!visY[j])
							minWeight = std::min(minWeight, lx[i] + ly[j] - weight[i * m + j]);

			for (int i = 0; i < n; i++)
				if (visX[i])
					lx[i] -= minWeight;

			for (int j = 0; j < m; j++)
				if (visY[j])
					ly[j] += minWeight;
		}
	}

	delete[] lx;
	delete[] ly;
	delete[] visX;
	delete[] visY;

	int ans = 0;
	for (int j = 0; j < m; j++)
		if (ret[j] >= 0)
			ans += weight[ret[j] * m + j];

	return ans;
}


inline int Calculation::
Log2(int n)
{
	static_assert(sizeof(unsigned int) == 4, " ");
	return (debruijn[((unsigned int)(((n)& -(n)) * 0x077CB531U)) >> 27]);
}


bool Calculation::
DFS_ForKM(const int i, const int m, const int weight[], bool visX[], bool visY[], const int lx[], const int ly[], int ret[])
{
	visX[i] = true;
	for (int j = 0; j < m; j++)
		if (!visY[j] && lx[i] + ly[j] == weight[i * m + j]) {
		visY[j] = true;
		if (ret[j] == -1 || DFS_ForKM(ret[j], m, weight, visX, visY, lx, ly, ret)) {
			ret[j] = i;
			return true;
		}
		}
	return false;
}


const double Calculation::PI = 3.14159265358979323;
const float Calculation::PIf = 3.141592653f;
const double Calculation::EPS = 1e-7;
const float Calculation::EPSf = 1e-7f;

const int debruijn[32] = {
	0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
	31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
};