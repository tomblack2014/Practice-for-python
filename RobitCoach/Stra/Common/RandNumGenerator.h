/*********************************************************************
 *	@file		RandNumGenerator.h
 *	@brief		Class RandNumGenerator, for generating random number.
 *
 *	Date        Name        Description
 *	11/12/14	MYLS		Creation.
 *	02/03/15	MYLS		Add method SetBound.
 *
 *********************************************************************/

#pragma once

#include <algorithm>
#include <unordered_map>
#include <random>

/**
 *	\brief	随机数生成器，用于生成平均分布的随机数，暂时只支持整数
 */
template <typename T> class RandNumGenerator {

public:

	/**
	 *	\brief	Get a random T
	 *	|return	返回运输结果
	 */
	T Rand()
	{
		return _Distribution(_Engine);
	}

	/**
	 *	\brief	Set Bound Of Range
	 *
	 *	\param	min
	 *	\param	max
	 */
	void SetBound(T min, T max)
	{
		_Distribution.a = min;
		_Distribution.b = max;
	}

public:

	/**
	 *	\brief Constructor
	 *
	 *	\param	min
	 *	\param	max
	 */
	RandNumGenerator(const T & min, const T & max) :
		_Engine(std::random_device()()),
		_Distribution(min, max)
	{}

private:

	std::mt19937 _Engine;								/**< random device */
	std::uniform_int_distribution<T> _Distribution;		/**< uniform int distribution, [a, b] */
};

