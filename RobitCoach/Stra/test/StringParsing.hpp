/*
**********************************************************************
*	Copyright (C) 2015.
*	All Rights Reserved.
**********************************************************************
*
*	@file		StringParsing.h
*	@brief		the class to analyze string of output
*
*	Date		    Name			  Description
*	15/03/15	    tomblack		  Creation.
*   28/03/15        tomblack          完成字符串解析和通讯的接口连接
*********************************************************************/

#include <string>

#include "DataLayer/UDPDataHandling.h"

class StringParsing
{
public:
	StringParsing(){};

	~StringParsing(){};

	void GetString(std::string str){
		m_String = str;

		Execute();
	}

private:
	void Execute(){
		//TODO:解析字符串
                int length = static_cast<int>(m_String.length()),mode = 0;
		std::string temp = "";
		CUDPDataHandling datahandler;

		std::string op = "";									/*具体操作，编号0*/
		int ID = 0, x = 0, y = 0, angle = 0, dis = 0;			/*机器ID(编号1)，x、y坐标(编号2、3)，角度(编号4)，距离(编号5)*/


		for (int i = 0; i < length; i++){
			if (m_String[i] == '*'){
				if (op == "MOVETO"){
					//TODO:发送MOVETO指令
				}
				else if (op == "ATTACK"){
					//TODO:发送ATTACK指令
				}
				else {/*default*/
				
				}

				temp = ""; op = ""; ID = 0; x = 0; y = 0; angle = 0; dis = 0; mode = 0;
			}
			else if (m_String[i] == ' '){
				if (!temp.empty())
					switch (mode){
					case 0:op = temp; temp = ""; mode++; break;
					case 1:ID = StringToInt(temp); temp = ""; mode++; break;
					case 2:x = StringToInt(temp); temp = ""; mode++; break;
					case 3:y = StringToInt(temp); temp = ""; mode++; break;
					case 4:angle = StringToInt(temp); temp = ""; mode++; break;
					case 5: dis = StringToInt(temp); temp = ""; mode++; break;
				}
			}
			else 
				temp += m_String[i];
		}
	}

	int StringToInt(std::string temp){
                int length =  static_cast<int>(temp.length());
		int ret = 0;

		for (int i = 0; i < length; i++){
			if (temp[i] >= '0' && temp[i] <= '9')
				ret = ret * 10 + temp[i] - '0';
		}

		return ret;
	}

	std::string m_String;
};
