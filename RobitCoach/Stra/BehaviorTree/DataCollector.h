/*********************************************************************
 *	@file		DataCollector.h
 *	@brief		用于收集一定量的同个数据，返回均值之类的。
 *
 *	Date        Name        Description
 *	16/04/15	MYLS		Creation.
 *
 *********************************************************************/

#pragma once

#include <queue>

template <typename T>
class DataCollector {

public:

	/*==========================================================================*/
	/*	public Constructor \ Destructor											*/
	/*==========================================================================*/

	/**
	 *	\brief Constructor
	 *
	 *	\param	maxOfSamples	最大的采样数量
	 */
	DataCollector(const unsigned int maxOfSamples)
		: _MaxOfSamples(maxOfSamples)
		, _Sum()
		, _Samples()
	{}

	/**
	 *	\brief 析构函数
	 */
	~DataCollector() {};

public:

	/*==========================================================================*/
	/*	公有方法																	*/
	/*==========================================================================*/

	/**
	 *	\brief 检查数据量是否收集满
	 *
	 *	\param	btName 行为树节点名，用于创建跟节点。(递归构建树)
	 *
	 *	\return	true 已满, false 未满
	 */
	bool IsReady()
	{
		return (_Samples.size() >= _MaxOfSamples);
	}

	/**
	 *	\brief 清空全部数据
	 */
	void Clear()
	{
		while (!_Samples.empty())
			_Samples.pop();
		_Sum = T();
	}

	/**
	 *	\brief 添加一个数据，如果数据量超过上限，将会从最旧的数据开始删除
	 *
	 *	\param	data 待加入的数据
	 */
	void Push(const T & data)
	{
		_Sum += data;
		_Samples.push(data);
		while (_Samples.size() > _MaxOfSamples) {
			_Sum -= _Samples.front();
			_Samples.pop();
		}
	}

	/**
	 *	\brief 获取均值
	 *
	 *	\return 均值，如果收集数据不够，会得到已经搜集的部分的均值
	 */
	T GetAverage()
	{
		return (_Sum / _Samples.size());
	}



private:

	/*==========================================================================*/
	/*	私有 成员变量\常量														*/
	/*==========================================================================*/

	const unsigned int _MaxOfSamples;		/**< 最大取样数 */

	T _Sum;									/**< 已经搜集的数据的总和 */
	std::queue<T> _Samples;					/**< 保存样本的队列 */

};

