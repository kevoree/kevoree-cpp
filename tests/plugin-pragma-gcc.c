/* Demonstrates how to add custom pragmas */

#include "gcc-plugin.h"
#include <stdlib.h>
#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "rtl.h"
#include "tree.h"
#include "function.h"

#include "cpplib.h"
#include "tree-pass.h"
#include "intl.h"

int plugin_is_GPL_compatible;



/* handler of #pragma GCCPLUGIN sayhello "message" is quite similar to
   handler of #pragma GCC message...*/

static void handle_pragma_ComponentType (cpp_reader *dummy)
{
  tree message = 0;
  if (pragma_lex (&message) != CPP_STRING)
    {
      warning (OPT_Wpragmas, "%<Component Name%>  is not a string");
      return;
    }
  if (TREE_STRING_LENGTH (message) > 1)
    if (cfun){
		      warning (OPT_Wpragmas, "%< ComponentType%> from function %qE: %s",cfun->decl, TREE_STRING_POINTER (message));
	}else{
	        warning (OPT_Wpragmas, "%<ComponentType%>  name: %s",TREE_STRING_POINTER (message));	
	}

}


static void handle_pragma_Dictionary (cpp_reader *dummy)
{
  tree message = 0;
   enum cpp_ttype token;
  if (pragma_lex (&message) != CPP_STRING)
    {
		  token = pragma_lex (&message);
		  if (token != CPP_NAME){
			  
		  }
			     warning (OPT_Wpragmas, "%< Dictionary> %s ",token);
	
   

      return;
    }
  if (TREE_STRING_LENGTH (message) > 1){
    if (cfun)
    {
		warning (OPT_Wpragmas,"%<Dictionary%> from function %qE: %s", cfun->decl, TREE_STRING_POINTER (message));	
	} 
	else 
	{
        warning (OPT_Wpragmas, "%<Dictionary%> %s",TREE_STRING_POINTER (message));
            
	}
}
}

/* Plugin callback called during pragma registration */

static void register_my_pragma (void *event_data, void *data) 
{
 // warning (0, G_("Callback to register pragmas"));
  c_register_pragma (NULL, "ComponentType", handle_pragma_ComponentType);
  c_register_pragma (NULL, "Dictionary", handle_pragma_Dictionary);
  
}

int plugin_init (struct plugin_name_args *plugin_info,struct plugin_gcc_version *version)
{
  const char *plugin_name = plugin_info->base_name;

  register_callback (plugin_name, PLUGIN_PRAGMAS, register_my_pragma, NULL);
  return 0;
}
