// ������12345678.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "StdAfx.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include<fstream>
#include <vector>
#include <deque>
#include <stack>
#include <stdio.h>
#define maxl 4 
using namespace std;
typedef long long ll;
ofstream Question("Exercises.txt");
ofstream Answers("Answers.txt");
char Op[] = {'+', '-', '*', '/'};
char ss[8][8] ={{'>','>','<','<','<','<','>','>'},
                {'>','>','<','<','<','<','>','>'},
                {'>','>','>','>','>','<','>','>'},
                {'>','>','>','>','>','<','>','>'},
                {'>','>','>','>','>','<','>','>'},
                {'<','<','<','<','<','<','=','0'},
                {'>','>','>','>','>','0','>','>'},
                {'<','<','<','<','<','<','0','='}};
//�����֮������ȹ�ϵ
 void create(int argc,char *argv[],string &r)
{
	for(int i=1;i<argc;i++)
	{
		string s(argv[i]);
		if(s=="-r")
		{
			if(i+1<argc)
			{
				string str(argv[i+1]);
				if(str!="-n" && str!="-r" && str!="-e" && str!="-a")
				{
					r=str;
				}
				if(r=="")
				{
					cout<<"����-r��ֵ��";
						break;
				}
			}
		}
	}
	int R=atoi(r.c_str());
	int length;
	do{
		length = rand()%maxl;
	}while(length < 2);
		bool div = false; //������ֹ���ֳ�0���� 
	int brack_cnt = 0; //��¼δƥ��������Ÿ��� 
	int num=0, op=0;
	for (int i = 1; i < length; i++) //ѭ��������ʽ 
	{
		if (div) //����ʱ��Ҫ���ɵ�����ǰ�ĸ�����'/'������Ҫ���д˴����ɵ����ֲ���Ϊ0 
		{
		div = false;
		do{
			num = rand()%R;
		}while(num == 0);
			Question<<num;
		}
		else
			Question<<rand()%R; //����ֱ������������� 
		int tmpcnt = brack_cnt;
		for (int j = 0; j < tmpcnt; j++) //����ǰ��δƥ��������ţ�������һ�������� 
		{
			if ((rand()%5) > 2) //���������Ÿ���Ϊ0.6
			{
				brack_cnt--;
				Question<<")";
			}
		}
		op = rand()%4; //��������� 
		Question<<Op[op];
		if (op == 3) //�������˳��ţ�����Ҫ����Ӧ��־λ 
			div = true;
		if (!(rand()%3)) //��һ���������������ţ�����Ϊ1/3 
		{
			Question<<"(";
			brack_cnt++;
			Question<<rand()%R; //���������ź��������һ�����ֺ����������Ȼ���ܳ���(15)�����Ĵ��� 
			op = rand()%4;
			Question<<Op[op];
			if (op == 3)
				div = true;
		}
	}
	if (div) //�������һ�����֣������ֺ���Ҫ������� 
	{
		div = false;
		do{
			num = rand()%R;
		}while(num == 0);
			Question<<num;
	}
	else
		Question<<rand()%R;
	while(brack_cnt--) //��ȫ������ 
		Question<<")";
}
 void getRowCol (const char stackCh, const char ch, int& row, int& col)
{
    switch (stackCh)
    {
    case '+':
        row = 0;
        break;
    case '-':
        row = 1;
        break;
    case '*':
        row = 2;
        break;
    case '/':
        row = 3;
        break;
    case '%':
        row = 4;
        break;
    case '(':
        row = 5;
        break;
    case ')':
        row = 6;
        break;
    case '=':
        row = 7;
        break;
    }
    switch (ch)
    {
    case '+':
        col = 0;
        break;
    case '-':
        col = 1;
        break;
    case '*':
        col = 2;
        break;
    case '/':
        col = 3;
        break;
    case '%':
        col = 4;
        break;
    case '(':
        col = 5;
        break;
    case ')':
        col = 6;
        break;
    case '=':
        col = 7;
        break;
    }

}
//д���ļ�
void write(vector<int>& iAnswer)
{
    for(vector<int>::size_type ix = 0; ix != iAnswer.size(); ix++)
    {
        Answers<< iAnswer[ix] << '\n';
    }
    Answers.close();
}
void count(vector<int>& iAnswer, string& str)
{
    int temp = 0;
    int row = 0 ,col = 0;
    stack<int> iStk;            //�������ݶ�
    stack<char> cStk;            //�����ַ���
    char stackCh = '\0';
    char ch = '\0';
    cStk.push('=');             //�Ȱ�=ѹ���ַ����У��Ա�ƥ��Ⱥ�
    for (string::size_type ix = 0; ix != str.size(); ix++)
    {
        //��������֣����ж���һ���ַ��Ƿ�Ҳ�����֣�������ǣ���ѹ�����ݶ���
        if (str[ix] >= '0' && str[ix] <= '9')
        {
            temp = str[ix] - '0' + temp * 10;
            if (str[ix + 1] < '0' || str[ix + 1] > '9')
            {
                iStk.push(temp);
            }
        }
        else
        {
/*            iStk.push(temp);*/
            temp = 0;
            stackCh = cStk.top();       //�����ַ��ѵĶѶ��ַ�
            ch = str[ix];                //��ȡ�ַ����е��ַ�
            if (ch == '=' || ch == ')') //���� = �ţ����ߣ�����ִ���ж�
            {
                ix--;
            }
            getRowCol(stackCh,ch,row,col); ////���ַ�ת������Ӧ���к���
            switch(ss[row][col])
            {
            case '=':  //�������������
                if ( ch == '=')
                {
                    iAnswer.push_back(iStk.top());
                    return ;
                }
                else
                {
                    cStk.pop();
                    ix++;
                }

                break;
            case '>':  //����
                {
                    int num2 = iStk.top();
                    iStk.pop();
                    int num1 = iStk.top();
                    iStk.pop();
                    stackCh = cStk.top();
                    cStk.pop();
                    if (ch != '=' && ch != ')')
                    {
                        cStk.push(ch);
                    }
                    switch(stackCh)
                    {
                    case '+':
                        num1 += num2;
                        break;
                    case '-':
                        num1 -= num2;
                        break;
                    case '*':
                        num1 *= num2;
                        break;
                    case '/':
                        num1 /= num2;
                        break;
                    case '%':
                        num1 %= num2;
                        break;
                    }
                    iStk.push(num1);
                    break;
                }
            case '<': //ѹ�����
                cStk.push(ch);
                break;
            case '0': //���ʽ����
                cout << "error arithmetic" << endl;
                return ;
            }
        }
    }
}
void Math()

{
     ifstream ifs("Exercises.txt");
	if (!ifs.is_open())
    {
        ifs.clear();
        fstream fs("Exercises.txt",ios_base::out); //�����ʧ�ܾʹ����ļ�Exercises.txt
        fs.close();
        ifs.open("Exercises.txt");
    }
    string temp;
    deque<string> sDeq;
    while (!ifs.eof())
    {
        getline(ifs,temp);                //���ж�ȡ���ݣ��洢��˫�˶�����
        sDeq.push_back(temp);
    }
    ifs.close();
    vector<int> iAnswer;
    for (deque<string>::size_type ix = 0; ix != sDeq.size(); ix++)
    {
        string str;
        str = sDeq.front();
        sDeq.pop_front();
        ix--;
        //������ʽ
        count(iAnswer,str);
    }
    write(iAnswer);
}
int main(int argc,char *argv[])
{
	string Str[4];
	string n,r,e,a;
	for(int i=1;i<argc;i++)
	{
		string s(argv[i]);
		if(s=="-n")
		{
			if(i+1<argc)
			{
				string str(argv[i+1]);
				if(str!="-n" && str!="-r" && str!="-e" && str!="-a")
				{
					n=str;
				}
				if(n=="")
				{
					cout<<"����-n��ֵ��";
					break;
				}
			}
		}
		if(s=="-r")
		{
			if(i+1<argc)
			{
				string str(argv[i+1]);
				if(str!="-n" && str!="-r" && str!="-e" && str!="-a")
				{
					r=str;
				}
				if(r=="")
				{
					cout<<"����-r��ֵ��";
					break;
				}
			}
		}
		if(s=="-e")
		{
			if(i+1<argc)
			{
				string str(argv[i+1]);
				if(str!="-n" && str!="-r" && str!="-e" && str!="-a")
				{
					e=str;
				}
				if(e=="")
				{
					cout<<"����-e��ֵ��";
					break;
				}
			}
		}
		if(s=="-a")
		{
			if(i+1<argc)
			{
				string str(argv[i+1]);
				if(str!="-n" && str!="-r" && str!="-e" && str!="-a")
				{
					a=str;
				}
				if(a=="")
				{
					cout<<"����-a��ֵ��";
					break;
				}
			}
		}
	}
	int m=1;
	int N=atoi(n.c_str());//�����Ҫ������ʽ�ĸ���
	srand(time(0));
	for (int i = 0; i < N; i++)
	{
		
		while(N--)
		{
			//Question<<m<<". ";//���
			create(argc,argv,r);
			Question<<"="<<endl;
			//m++;
		}
		Math();
	}
	cout<<"��Ŀ�������";

}

