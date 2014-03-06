#include "ReadH.h"
#include <stdio.h>
#include <stdlib.h>

CReadH::CReadH(string name)
{
	Hname = name;
	getclass();
}

int CReadH::getclass()
{
	string allContent = readallfile(Hname);
	int pos = allContent.find("\nclass ");      //�ȼ��������ǣ�Ҫ��
	while(pos!=string::npos)
	{
		string classname =  getclassname(pos,allContent);
		string classbody  =  getclassbody(pos,allContent);
		classdef.insert(pair <string,string>(classname,classbody));
		pos = allContent.find("\nclass ",pos+strlen("\nclass "));
	}
	return 1;
}

string CReadH::getclassname(int pos, std::string content)
{
	string ans = "";
	int i = pos+strlen("\nclass");
	while(content.at(i)==' '||content.at(i)=='\t')
		i++;

	for(;(content.at(i)>=65&&content.at(i)<=90)||(content.at(i)>=97&&content.at(i)<=122)||(content.at(i)>=48&&content.at(i)<=57);i++)
	{
		ans += content.at(i);
	}
	
	return ans;
	
}

string CReadH::getclassbody(int pos, std::string content)
{
	int ileft = 0;
	int bodystart = content.find("{");
	if(bodystart!=string::npos)
	{
		ileft ++;

		int i;
		for(i = bodystart+1;i<content.length();i++)
		{
			if(content.at(i)=='{')
				ileft++;
			else if(content.at(i)=='}')
				ileft--;

			if(ileft == 0)
				break;
		}
		string ans = content.substr(pos,i-pos+1);
		return ans;
	}
	return "";
}

string CReadH::readallfile(string name)
{
    FILE * pFile;
    long lSize;
    char * buffer;
    size_t result;
    
    /* ��Ҫһ��byte��©�ض��������ļ���ֻ�ܲ��ö����Ʒ�ʽ�� */ 
	pFile = fopen (name.c_str(), "rb" );
    if (pFile==NULL)
    {
        fputs ("File error",stderr);
        exit (1);
    }

    /* ��ȡ�ļ���С */
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    /* �����ڴ�洢�����ļ� */ 
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL)
    {
        fputs ("Memory error",stderr); 
        exit (2);
    }

    /* ���ļ�������buffer�� */
    result = fread (buffer,1,lSize,pFile);
    if (result != lSize)
    {
        fputs ("Reading error",stderr);
        exit (3);
    }
    /* ���������ļ��Ѿ���buffer�У����ɱ�׼�����ӡ���� */
    //printf("%s", buffer); 

    /* ������ʾ���ر��ļ����ͷ��ڴ� */
	string ans = string(buffer);
    fclose (pFile);
    free (buffer);
    return ans;
}
