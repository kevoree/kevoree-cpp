#include <iostream>
#include <exception>

#ifndef __KevoreeException_H
#define __KevoreeException_H
/**
 * Author: jean-emile.dartois@inria.fr
 * Date: 31/07/14
 * Time: 9:00
 */
class KevoreeException: public exception
{
public:
	KevoreeException(std::string const& msg="",int priority=0) throw()    :m_msg(msg),m_priority(priority)  {}
	virtual ~KevoreeException() throw() {}
	virtual const char* what() const throw()
    {
		return m_msg.c_str();
    }

	int getPriority() const throw()
    {
		return m_priority;
    }
private:
	int m_priority;
	string m_msg;
};

#endif
