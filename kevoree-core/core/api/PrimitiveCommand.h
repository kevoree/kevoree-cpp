#ifndef __PrimitiveCommand_H
#define __PrimitiveCommand_H


class PrimitiveCommand
{
public:
PrimitiveCommand()
{
	result =false;
}
	virtual void execute(){};
	virtual void undo(){};
	virtual bool get_result()
	{		
		return result;
	};
bool result;
};


#endif
