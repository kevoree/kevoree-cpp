#ifndef __Primitives_H
#define __Primitives_H

enum  Primitives {
    StartInstance,
    UpdateInstance,
    UpdateDictionaryInstance,
    AddBinding,
    AddInstance,
    AddDeployUnit,
	UpdateDeployUnit,
    UpdateBinding,
    RemoveDeployUnit,
    RemoveInstance,
    RemoveBinding,
    StopInstance
};

// schedule

static const int Priority_Primitives(Primitives e)
{
	  switch(e)
	  {
	  case StartInstance: return 11;
	  case UpdateInstance: return 10;
	  case UpdateDictionaryInstance : return 9;
	  case AddBinding: return 8;
	  case AddInstance: return 7;
	  case AddDeployUnit : return 6;
	  case UpdateDeployUnit: return 5;
	  case UpdateBinding: return 4;
	  case RemoveDeployUnit: return 3;
	  case RemoveInstance: return 2;
	  case RemoveBinding : return 1;
	  case StopInstance: return 0;
	  }
}

/*m
static std::string TO_STRING_Primitives(Primitives e)
{
	  switch(e)
	  {
		  case UpdateDeployUnit: return "UpdateDeployUnit";
		  case AddDeployUnit: return "AddDeployUnit";
		  case RemoveDeployUnit: return "RemoveDeployUnit";
		  case UpdateInstance: return "UpdateInstance";
		  
		  case UpdateDictionaryInstance: return "UpdateDictionaryInstance";
		  case AddInstance: return "AddInstance";
		  case RemoveInstance: return "RemoveInstance";
		  case AddBinding: return "AddBinding";
		  
		  case RemoveBinding: return "RemoveBinding";
		  case StartInstance: return "StartInstance";
		  case StopInstance: return "StopInstance";
		  
		  default: return "ERROR";
	  }
}
*/

#endif
