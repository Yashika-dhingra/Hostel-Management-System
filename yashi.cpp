//hostel accomodation system in c++ using mysql & oops

#include<iostream>
#include<mysql.h>
#include<mysqld_error.h>
#include<windows.h>
#include<sstream>

using namespace std;
using namespace std;
const char* HOST= "localhost";
const char* USER= "root";
const char* PW= "yashika@2";
const char* DB= "mydb";

class hostell{
	private:
		string Name;
		int Bed, Fee;
	public:
		hostell(string name, int bed, int fee){
			Name=name;
			Bed= bed;
			Fee= fee;
		}
	    string getName(){
	    	return Name;
		}
		int getBed(){
			return Bed;
		}
		int getFee(){
			return Fee;
		}
};

int main(){
	MYSQL* conn;
	conn= mysql_init(NULL);
	if(!mysql_real_connect(conn,HOST,USER,PW,DB,3306,NULL, 0)){  //PORT,POINTER,FLAG
        cout<<"ERROR: "<<mysql_error(conn)<<endl;
	}
	else{
		cout<<"logged in database"<<endl;
	}
	Sleep(3000);


	hostell h("3star",5, 5000);
	
	int intB= h.getBed();
	stringstream ss;
	ss<<intB;
	string strB= ss.str();
	
	int intF=h.getFee();
	stringstream as;
	as<<intF;
	string strF=ss.str();
	string insert="INSERT INTO hostell (Name,Bed, fee) VALUES ('"+h.getName()+"','"+strB+"','"+strF+"' )";
	if(mysql_query(conn,insert.c_str())){
		cout<<"ERROR: "<<mysql_error(conn)<<endl;
	}
	else{
		cout<<"data inserted"<<endl;
	}
	bool exit =false;
	
	while(!exit){
		system("cls"); //clearscreen
		cout<<"WELCOME TO HOSTEL MANAGEMENT SYSTEM"<<endl ;
		cout<<"***********************************"<<endl;
		cout<<"1. Reserve Bed: "<<endl;
		cout<<"2. Exit: "<<endl;
		cout<<"Enter your choice: ";
		int val;
		cin>>val;
		
		if(val==1){
			string n;
			cout<<"enter Student Name: ";
			cin>>n;
			int totalB;
		string check = "SELECT Bed FROM hostell WHERE Name = '" + h.getName() + "'";// Name: primary key
		if(mysql_query(conn,check.c_str())){
		cout<<"ERROR: "<<mysql_error(conn)<<endl;
    	}
    	else{
			MYSQL_RES* res; //result 
			res=mysql_store_result(conn);  //ap func
			if(res){
				MYSQL_ROW row=mysql_fetch_row(res);  //structure: MYSQL_ROW
				if(row){
					totalB = atoi(row[0]);
				}
				mysql_free_result(res);
			}
		}
		if(totalB>0){
			totalB--;
			stringstream zs;
			zs<<totalB;
			string strT=zs.str();
		string update = "UPDATE hostell SET Bed = '" + strT + "' WHERE Name = '" + h.getName() + "'";
		if(mysql_query(conn,update.c_str())){
		cout<<"ERROR: "<<mysql_error(conn)<<endl;
    	}
    	else{
    	cout<<"Bed is reserved in "<<h.getName()<<"Hostel for student "<<n<<endl;
    	cout<<"please pay "<<h.getFee()<<" rupees. "<<endl;
		}
		}
		else if(totalB==0){
			cout<<"Sorry! No Bed Available"<<endl;
		}
		Sleep(8000);
		}//if
		else if(val==2){
			exit=true;
			cout<<"good luck"<<endl;
			Sleep(3000);
		}
		else{
			cout<<"INVALID INPUT"<<endl;
			Sleep(3000);
		}
	}//while
	mysql_close(conn);
	return 0;
	
}













