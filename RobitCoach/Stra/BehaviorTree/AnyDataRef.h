/*********************************************************************
 *	@file		AnyDataRef.h
 *	@brief		Class AnyDataRef, ref to any data type.
 *
 *
 *	Date        Name        Description
 *	01/03/15	MYLS		Creation.
 *	10/03/15				
 *
 *********************************************************************/

#pragma once

#include <assert.h>

class Data
{
public:
	
	virtual ~Data(){};

	template<typename T>
	T& GetRealData(){
		AnyDataRef<T>* ret = dynamic_cast<AnyDataRef<T>*>(this);
		assert(ret != nullptr);
		return ret->GetRealData();
	}

	template<typename T>
	const T& GetRealData() const{
		const AnyDataRef<T>* ret = dynamic_cast<const AnyDataRef<T>*>(this);
		assert(ret != nullptr);
		return ret->GetRealData();
	}

protected:
	Data(){};
	
};


template<typename T>
class AnyDataRef : public Data
{
public:

	AnyDataRef(T& data)
		: Data()
		, m_RealData(&data)
	{}

	~AnyDataRef()
	{}

	T& GetRealData(){
		return *m_RealData;
	}

	const T& GetRealData() const{
		return *m_RealData;
	}

	AnyDataRef& operator =(T& data)
	{
		Set(data);
		return *this;
	}

private:

	void Set(T& data)
	{
		m_RealData = &data;
	}

private:

	T* m_RealData;
};

typedef Data BehaviorTreeInput;
typedef Data BehaviorTreeOutput;