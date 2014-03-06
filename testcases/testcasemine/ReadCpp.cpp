#include "ReadCpp.h"
#include <stdio.h>
#include <stdlib.h>
CMethodBody::CMethodBody(string method)
{
	body = method;
	next = NULL;
}
CReadCpp::CReadCpp(string name)
{
	next = NULL;
	imatch = 0;
	CppName = name;
	getrelation();
	
}

void CReadCpp::setnext(CReadCpp *p)
{
	next = p;
}
CReadCpp* CReadCpp::getnext()
{
	return next;
}
void CReadCpp::getrelation()
{
	string content = readallfile(CppName);
	
	int classnum = findclasses(0,content);
	if(classnum>0)
		getheadfile(content);

}

int CReadCpp::findclasses(int s,std::string content)    //���붥��д
{	
	string oneclassname="";
	string oneclassbody="";
	bool isclass;
	int ileft = 0;
	int pos = content.find("::",s);
	if(pos!=string::npos)
		isclass = true;
	else
		return 0;

	int i = pos+strlen("::");
	if(isclass)
	{
		while(content.at(i)!='\n')
		{
			i++;
		}
		if(content.at(i-1)==';')
			isclass = false;
	}
	i=pos;
	if(isclass)
	{
		while(content.at(i)!='\n')
		{
			i--;
			if(i<0)
				break;
		}
		if(content.at(i+1)==' '||content.at(i+1)=='\t')
			isclass = false;
	}

	if(isclass)
	{
		int j = pos-1;
		while(content.at(j)!=' '&&content.at(j)!='\t'&&content.at(j)!='\n')
		{
			j--;
		}
		oneclassname = content.substr(j+1,pos-1-j);


		int bodystart = content.find("{",pos);
		if(bodystart!=string::npos)
		{
			ileft++;
		}
		int k;
		for(k=bodystart+1;k<content.length();k++)
		{
			if(content.at(k)=='{')
				ileft++;
			else if(content.at(k)=='}')
				ileft--;
			if(ileft == 0)
				break;
		}
		
		int start = pos;
		while(content.at(start)!='\n')
			start--;

		oneclassbody = content.substr(start+1,k-start);
		map<string ,CMethodBody*>::iterator iter;
		iter = cppclass.find(oneclassname);
		if(iter!=cppclass.end())
		{
			CMethodBody *q = iter->second;
			CMethodBody *p = new CMethodBody(oneclassbody);
			while(q->next!=NULL)
				q=q->next;
			p->next = NULL;
			q->next = p;
		}
		else
		{
			CMethodBody *p = new CMethodBody(oneclassbody);
			p->next = NULL;
			cppclass.insert(pair<string,CMethodBody*>(oneclassname,p));
		}
		return findclasses(k,content)+1;
	}

	return findclasses(pos+2,content);
}

void CReadCpp::getheadfile(string content)    //ʱ�临�ӶȺܸߣ�Ҫ�޸�
{
	int pos = content.find("#include \"");
	while(pos!=string::npos)
	{
		string filename="";
		pos += strlen("#include \"");
		int i = pos;
		while(content.at(i)!='\"')
		{
			filename += content.at(i);
			i++;
		}
		headfile.push_back(filename);
		pos = content.find("#include \"",pos);
	}
}

string CReadCpp::readallfile(string name)
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
