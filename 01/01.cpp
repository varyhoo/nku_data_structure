#include<iostream>
#include<fstream>
using namespace std;
long long temp[200];
long long fun(int n)
{
	if(n<2)
	{
		return 1;
	}
	if(temp[n]>0)
	{
		return temp[n];
	}
	temp[n]=fun(n-1)+fun(n-2);
	return temp[n];
}
int main()
{
	int num;
	ifstream text("input.txt");
	text>>num;
	if(num>90||num<0)
	{
		cout<<"WRONG"<<endl;
	}
	else 
	{
		long long temp1=fun(num);
		cout<<temp1<<endl;
	}
	text.close();
	system("PAUSE");
}