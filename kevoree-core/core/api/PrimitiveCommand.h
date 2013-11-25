#ifndef __PrimitiveCommand_H
#define __PrimitiveCommand_H


class PrimitiveCommand
{
public:
	virtual bool execute(){};
	virtual void undo(){};
};


#endif
