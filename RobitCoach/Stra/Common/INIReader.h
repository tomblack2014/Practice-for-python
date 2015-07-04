/*********************************************************************
 *
 *	@file		INIReader.h
 *	@brief		载入一个ini文件，可以查询里面的数据
 *
 *
 *	Date        Name        Description
 *	06/03/15	MYLS		Creation.
 *
 *********************************************************************/

#pragma once

#include <string>
#include <vector>
#include <map>

#include "INIFile.h"


/**
 *	\brief  这里将载入一个ini文件，用于对一些量的初始化
 */
class INIReader{

public:

	/**
	 *	\brief	Reload, 重新载入这个文件
	 *
	 *	\param	filePath	需要读取的文件的路径
	 *
	 *	\return	true 读取成功, false 读取失败
	 */
	bool reload(const std::string & filePath);

	/**
	 *	\brief	获取字符串
	 *
	 *	\param	section	主键
	 *	\param	key		副键
	 *
	 *	\return	= 之后的字符串
	 */
	std::string getString(const std::string & section, const std::string & key);

	/**
	 *	\brief	获取一个数据
	 *
	 *	\param	section	主键
	 *	\param	key		副键
	 *	\param	value	值的引用
	 *
	 *	\return	查找是否成功
	 */
	template <typename T> bool getValue(const std::string & section, const std::string & key, T & value) const;

	/**
	 *	\brief 获取一组数
	 *
	 *	\param	section	[section]
	 *	\param	key		key = value
	 *	\param	tArray	储存目标
	 *
	 *	\return 成功则为true，否则为false
	 */
	template <typename T> bool getValue(const std::string & section, const std::string & key, std::vector<T> & tArray) const;

public:

	/**
	 *	\brief 构造函数
	 */
	INIReader(const std::string & filePath = DEFAULT_FILE_PATH);

	/**
	 *	\brief 析构函数
	 */
	~INIReader();

private:

	static const std::string DEFAULT_FILE_PATH;		/**< 默认的文件路径 */
	INIFile _iniFile;								/**< 用于读取指定ini文件 */
};


template <typename T> bool INIReader::
getValue(const std::string & section, const std::string & key, T & value) const
{
	std::string str = _iniFile.getString(section, key);
	if (str.empty())
		return false;

	// TODO: 健壮性测试？
	std::istringstream buffer(str);
	buffer >> value;
	return !buffer.fail();
}


template <typename T> bool INIReader::
getValue(const std::string & section, const std::string & key, std::vector<T> & tArray) const
{
	std::string str = _iniFile.getString(section, key);
	if (str.empty())
		return false;

	T element;
	std::istringstream buffer(str);
	while (buffer >> element) {
		if (buffer.fail())
			return false;
		tArray.push_back(element);
	}
	return true;
}


