#include <string>
#include <vector>
#include <map>
using namespace std;
class CMethodBody
{
public:
	CMethodBody *next;
	string body;
	CMethodBody(string method);
};
class CReadCpp
{
public:
	CReadCpp *next;
	string CppName;
	int imatch;
	int classposition;
	string globalStr;
	vector<string> headfile;
	map<string,CMethodBody*> cppclass;
public:
	CReadCpp(string name);
	~CReadCpp();
	string readallfile(string name);
	void getrelation();
	void getheadfile(int classstart,string content);
	int findclasses(int s,string content);
	CReadCpp* getnext();
	void setnext(CReadCpp *p);
	string findGlobal(string content);

};