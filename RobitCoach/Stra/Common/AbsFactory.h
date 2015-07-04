/*********************************************************************
 *
 *	@file		AbsFactory.h
 *	@brief		AbsFactory Method 模板类
 *
 *
 *	Date		    Name			  Description
 *	23/04/15	    MYLS			  Creation.
 *	15/05/15	    MYLS			  支持Create方法增加参数.
 *
 *********************************************************************/

#pragma once

#include <map>
#include <string>
#include <functional>
#include <type_traits>


/**
 *	\brief  对象工厂模板类
 *			使用时 T 为被构造对象的基类，Types为构造需要的参数(可以不写)，例如：
 *			ObjectFactory : public AbsFactory<Object, Type1, Type2, ...>
 */
template<class T, typename ... Types> class AbsFactory {

public:

	/**
	 *	\brief  注册需要构造的对象
	 *
	 *	\param	type	注册类型时对应的字符串
	 *
	 */
	template<typename U> void Register(const std::string & type);

	/**
	 *	\brief  根据字符串名，产生一个对象
	 *
	 *	\param	type	注册类型时对应的字符串
	 *
	 *	\return	目标对象，如果没有注册这个对象，将会返回nullptr
	 */
	T * Create(const std::string & type, Types ... args) const;

private:

	std::map<const std::string, std::function<T *(Types ... args)>> _Creator;		/**< 构造器 */

};



template<class T, typename ... Types>
template<typename U> void AbsFactory<T, Types...>::
Register(const std::string & type)
{
	static_assert(std::is_base_of<T, U>::value, "ERROR! T is not base of U.\n");

	auto creator = _Creator.find(type);
	
	if (creator == _Creator.end())
		_Creator[type] = [](Types ... args){return new U(args...); };
	else
		std::cerr << "AbsFactory:: Type : " << type << " already exists!" << std::endl;
}


template<class T, typename ... Types> T * AbsFactory<T, Types...>::
Create(const std::string & type, Types ... args) const
{
	auto creator = _Creator.find(type);

	if (creator == _Creator.end()) {
		std::cerr << "AbsFactory:: No Such Type : " << type << std::endl;
		return nullptr;
	}

	return creator->second(args...);
}


