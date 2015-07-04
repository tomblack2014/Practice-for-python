/*********************************************************************
 *	@file		DataCollector.h
 *	@brief		�����ռ�һ������ͬ�����ݣ����ؾ�ֵ֮��ġ�
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
	 *	\param	maxOfSamples	���Ĳ�������
	 */
	DataCollector(const unsigned int maxOfSamples)
		: _MaxOfSamples(maxOfSamples)
		, _Sum()
		, _Samples()
	{}

	/**
	 *	\brief ��������
	 */
	~DataCollector() {}

public:

	/*==========================================================================*/
	/*	���з���																	*/
	/*==========================================================================*/

	/**
	 *	\brief ����������Ƿ��ռ���
	 *
	 *	\param	btName ��Ϊ���ڵ��������ڴ������ڵ㡣(�ݹ鹹����)
	 *
	 *	\return	true ����, false δ��
	 */
	bool IsReady()
	{
		return (_Samples.size() >= _MaxOfSamples);
	}

	/**
	 *	\brief ���ȫ������
	 */
	void Clear()
	{
		while (!_Samples.empty())
			_Samples.pop();
		_Sum = T();
	}

	/**
	 *	\brief ���һ�����ݣ�����������������ޣ��������ɵ����ݿ�ʼɾ��
	 *
	 *	\param	data �����������
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
	 *	\brief ��ȡ��ֵ
	 *
	 *	\return ��ֵ������ռ����ݲ�������õ��Ѿ��Ѽ��Ĳ��ֵľ�ֵ
	 */
	T GetAverage()
	{
		return (_Sum / _Samples.size());
	}



private:

	/*==========================================================================*/
	/*	˽�� ��Ա����\����														*/
	/*==========================================================================*/

	const unsigned int _MaxOfSamples;		/**< ���ȡ���� */

	T _Sum;									/**< �Ѿ��Ѽ������ݵ��ܺ� */
	std::queue<T> _Samples;					/**< ���������Ķ��� */

};

