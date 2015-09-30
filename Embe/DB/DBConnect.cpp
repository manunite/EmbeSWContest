#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <mysql_connection.h>
#include <driver.h>
#include <exception.h>
#include <resultset.h>
#include <statement.h>
#include <sstream>

using namespace sql;
using namespace std;
int flag = 0;

template <class T>
const string& operator+=(string &str, const T &_ty)
{
	ostringstream os;
	os << _ty;
	str += os.str();
	return str;
}

int DBcon(int value,int job,int Id,int Pos_X,int Pos_Y,int Pos_Z)
{
try{
	sql::Driver *driver;
	sql::Connection *con;
	Statement * stmt;
	ResultSet * rs;
	
	printf("\nI am DBConnect Function\n");
	driver = get_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306/Fairi2","root","1111"); //DB 커넥터 생성
	//con->setSchema(Fairi2);
	cout << "SUCCESS Connection" << endl;
	if(job == 1) // Heart
	{
		cout << "SUCCESS_Heart" << endl;
		string StrQuery = "update userTable set BPM = ";
                StrQuery += value;
	       StrQuery += " where UserId = ";
	       StrQuery += Id;
	       StrQuery += "";
		cout << StrQuery << endl;
		stmt = con->createStatement();
		stmt->executeUpdate(StrQuery);
	}
	else if(job == 2) // Position_X,Y,Z
	{
		cout << "SUCCESS_Position" << endl;
		string StrQuery = "update userTable set Pos_X = ";
               StrQuery += Pos_X;
	       StrQuery += " , ";
	       StrQuery += " Pos_Y = ";
	       StrQuery += Pos_Y;
	       StrQuery += " , ";
	       StrQuery += " Pos_Z = ";
	       StrQuery += Pos_Z;
	       StrQuery += " where UserId = ";
	       StrQuery += Id;
	       StrQuery += "";
		cout << StrQuery << endl;
		stmt = con->createStatement();
		stmt->executeUpdate(StrQuery);
	}
/*	con->close();
	delete con;
	con = driver->connect("tcp://127.0.0.1:3306/Fairi2","root","1111"); //DB 커넥터 생성*/

	//
	string StrQuery = "select S_Time from userTable where UserId = ";
	StrQuery += Id;
	StrQuery += "";
	cout << StrQuery << endl;
	//stmt = con->createStatement();
	//stmt->executeUpdate(StrQuery);
	rs = stmt->executeQuery(StrQuery);
	int temp = 0;
	rs->next();
	temp = rs->getInt("S_Time");
	time_t now = time(NULL);
	struct tm *lt = localtime(&now);
	if(temp == 0)
	{
		cout << lt->tm_hour << " " << lt->tm_min << " " << lt->tm_sec << endl;
		int currentTime = lt->tm_hour*3600 + lt->tm_min*60 + lt->tm_sec;
		StrQuery = "update userTable set S_Time = ";
		StrQuery += currentTime;
		StrQuery += " where UserId = ";
		StrQuery += Id;
		StrQuery += "";
		cout << StrQuery << endl;
		stmt = con->createStatement();
		stmt->executeUpdate(StrQuery);
	}
	if(flag == 0)
	{
		cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
		StrQuery = "update userTable set S_Time = 0 where UserId = ";
		StrQuery += Id;
		StrQuery += "";
		stmt = con->createStatement();
		stmt->executeUpdate(StrQuery);
		flag = 999;
	}
	/////////////////////////////////////////////////////////////
		//con->Disconnect();	
		delete rs;
		delete stmt;
		delete con;
		cout << "ABC" << endl;

	} catch (sql::SQLException &e) {
	  	cout << "# ERR: SQLException in " << __FILE__;
	  	cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
	  	cout << "# ERR: " << e.what();
	  	cout << " (MySQL error code: " << e.getErrorCode();
	  	cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
	//con->Disconnect();
	//mysql_close($con);
/*	con->close();
	con = NULL;
	delete con;
	delete stmt;
	delete rs;*/
	
	//시간따오는것 추가해야함
	return 0;
}
