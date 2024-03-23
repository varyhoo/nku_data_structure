#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
void fun(char*arr,int n,int len)
{
	if(n==0)
	{
		for(int i=0;i<len;i++)
		{
			if(arr[i]!='0')
			{
			    cout<<arr[i]<<" ";
			}
		}
			cout<<endl;
			return;
	}
	for(int j=0;j<=1;j++)
	{
		char*temp= new char[len];
		for(int i=0;i<len;i++)
		{
			temp[i]=arr[i];
		}
		if(j==0)
		{
		    temp[n-1]='0';
		}
		fun(temp,n-1,len);
	}
}
int main()
{
	char arr[30];
	int num;
	ifstream infile("input.txt");
	infile>>num;
	infile.close();
	if(num>0&&num<=26)
	{
	for(int i=0;i<num;i++)
	{
		arr[i]='a'+i;
	}
	fun(arr,num,num);
	}
	else cout<<"WRONG";
	system("PAUSE");
}
