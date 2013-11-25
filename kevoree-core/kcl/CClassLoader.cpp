#include <kevoree-core/kcl/CClassLoader.h>

CClassLibrary* CClassLibrary::s_pInstance = 0;


CClassLibrary* CClassLibrary::getInstance()
{
	if (s_pInstance) return s_pInstance;
	s_pInstance = new CClassLibrary();
	return s_pInstance;
}

CClassLibrary* CClassLibrary::registerClassLoader(const string& in_className, IClassLoader* in_pNodeLoader)
{
	map<string, IClassLoader*>::const_iterator it = m_classLoadersByName.find(in_className);
	if (it != m_classLoadersByName.end()) return 0;

	m_classLoadersByName[in_className] = in_pNodeLoader;
	return this;
}

void* CClassLibrary::createClassByName(const string& in_className)
{
	map<string, IClassLoader*>::const_iterator it = m_classLoadersByName.find(in_className);
	if (it == m_classLoadersByName.end())
	{
		return 0;
	}
	return it->second->createClass();
}
