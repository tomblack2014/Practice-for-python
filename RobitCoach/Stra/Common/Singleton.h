/*********************************************************************
 *
 *	@file		Singleton.h
 *	@brief		Singleton模板类, 暂不支持多线程
 *
 *
 *	Date		    Name			  Description
 *	23/04/15	    MYLS			  Creation.
 *
 *********************************************************************/

#pragma once

/**
 *	\brief	单例模式的模板类
 *
 *			对于需要作为单例的类，需要继承: public Singleton<T>，
 *			并添加 friend class Singleton<T> 至其私有部分。
 */
template<class T> class Singleton {

public:

	/**
	 *	\brief	单例模式的接口
	 *	\return	<T> 的静态指针
	 */
	static T* Instance();

public:

	/**
	 *	\brief	不可拷贝构造
	 */
	Singleton(const Singleton &) = delete;

	/**
	 *	\brief	不可拷贝
	 */
	Singleton & operator= (const Singleton &) = delete;

protected:

	/**
	 *	\brief	默认构造函数
	 */
	Singleton() {};

	/**
	 *	\brief	虚析构函数
	 */
	virtual ~Singleton() {};

private:

	static T * _Instance;		/**< 用于单例模式 */
};



template <class T> T* Singleton<T>::
Instance()
{
	if (_Instance == nullptr) {
		_Instance = new T();
	}
	return _Instance;
}


template <class T> T* Singleton<T>::_Instance = nullptr;
