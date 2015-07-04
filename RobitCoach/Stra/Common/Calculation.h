/*********************************************************************
 *
 *	@file		Calculation.h
 *	@brief		the class of methods to calculate.
 *
 *
 *	Date		    Name			  Description
 *	08/02/15	    tomblack		  Creation.
 *	23/03/15		MYLS			  Add Kuhn_Munkres
 *
 *********************************************************************/

#pragma once


class Calculation {

public:

	/**
	 *	\brief	Kuhn Munkres 算法
	 *			用于任务分配
	 *
	 *  \param  score		score[n*n], 机器i做j任务时的估分即：score[i * n + j]
	 *  \param  size		size == 机器数目 == 任务数量 == n.
	 *  \param  ret			返回结果的数组：下标i为任务编号，对应ret[i]为机器编号。
	 *
	 *	\return	maxScore	最优方案得分
	 */
	static int Kuhn_Munkres(const int score[], const int size, int ret[]);


	/**
	 *	\brief	来自Quake III的神奇方法
	 *
	 *  \param  n			待计算的数n
	 *
	 *	\return	int			计算log2的结果
	 */
	inline static int Log2(int n);

private:

	// TO BE EDITED...
	static bool DFS_ForKM(const int i, const int m, const int weight[], bool x[], bool y[], int const lx[], int const ly[], int ret[]);


public:

	static const double PI;							/**< 圆周率常数PI */
	static const float PIf;							/**< 圆周率常数PI(float) */
	static const double EPS;						/**< 误差范围 */
	static const float EPSf;						/**< 误差范围(float) */
	static const int debruijn[32];					/**< 来自Quake III的计算log2的神奇数组 */
};


