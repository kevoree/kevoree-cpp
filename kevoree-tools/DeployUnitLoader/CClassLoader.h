#ifndef CCLASSLOADER_H_INCLUDED
#define CCLASSLOADER_H_INCLUDED


#include <map>
#include <string>

using namespace std;


class IClassLoader
{
public:
	virtual void*				createClass() = 0;
};


class CClassLibrary
{
public:

	static CClassLibrary*		getInstance();
	CClassLibrary*				registerClassLoader(const string& in_className, IClassLoader* in_pNodeLoader);
	void*						createClassByName(const string& in_className);

private:
	static CClassLibrary*		s_pInstance;
	CClassLibrary() {}
	virtual ~CClassLibrary() {}
	map<string, IClassLoader*>	deploysUnits;
};


#endif
