/*********************************************************************
 *	@file		INIFile.h
 *	@brief		类INIFile，用于读取ini文件
 *
 *
 *	Date        Name        Description
 *	04/03/15	MYLS		Creation.
 *
 *********************************************************************/

#pragma once

#include <map>
#include <string>
#include <fstream>

/**
 *	\brief	类 INIFile，用于读取ini文件(只读)
 */
class INIFile {

public:

	/**
	 *	\brief Constructor
	 */
	INIFile();

	/**
	 *	\brief	Destructor
	 */
	~INIFile();

public:

	/**
	 *	\brief	OpenFile, 读取一个文件，数据将会被储存
	 *
	 *	\param	filePath	文件的路径
	 *
	 *	\return	true, 读取成功; false, 读取失败。
	 */
	bool openFile(const std::string & filePath);

	/**
	 *	\brief	GetString, 获取ini中[section][key]对应的值
	 *
	 *	\param	section	"[section]"
	 *	\param	key		"key = value"
	 *
	 *	\return	value, 对应值，如果出现异常，将会返回空字符串
	 */
	std::string getString(const std::string & section, const std::string & key) const;

	/**
	 *	\brief	Print, 遍历并打印map内容
	 *			主要用于debug.
	 */
	void print();

public:

	/**
	 *	\brief	禁止"拷贝构造函数"操作
	 */
	INIFile(const INIFile&) = delete;

	/**
	 *	\brief	禁止"赋值运算"操作
	 */
	INIFile & operator=(const INIFile &) = delete;

private:

	/**
	 *	\brief	Trim，去掉字符串首尾的空格
	 *
	 *	\param	str		待处理的字符串
	 *
	 *	\return	std::string	处理结果
	 */
	std::string& trim(std::string & str) const;

private:

	/*==========================================================================*/
	/*	私有 成员变量															*/
	/*==========================================================================*/
	std::ifstream _File;												/**< 加载的文件 */
	std::map<std::string, std::map<std::string, std::string>> _Table;	/**< 映射表, _Table[section][key] = value */

};

