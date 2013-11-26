#ifndef __Primitives_H
#define __Primitives_H

enum  Primitives {
	UpdateDeployUnit,
    AddDeployUnit,
    RemoveDeployUnit,
    UpdateInstance,
    UpdateBinding,
    UpdateDictionaryInstance,
    AddInstance,
    RemoveInstance,
    AddBinding,
    RemoveBinding,
    StartInstance,
    StopInstance
};


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


#endif
