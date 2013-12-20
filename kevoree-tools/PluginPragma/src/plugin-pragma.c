#include "plugin-pragma-gcc.h"

int plugin_is_GPL_compatible;


/*
 *
 * http://gcc.gnu.org/wiki/GCC_PluginAPI
 * jedartois@gmail.com
 */



static void handle_pragma_ComponentType (cpp_reader *dummy)
{
	tree message = 0;
	if (pragma_lex (&message) != CPP_STRING)
	{
		warning (OPT_Wpragmas, "%<Component Name%>  is not a string");
		return;
	}
	if (TREE_STRING_LENGTH (message) > 1)
		if (cfun)
		{
			warning (OPT_Wpragmas, "%< ComponentType%> from function %qE: %s",cfun->decl, TREE_STRING_POINTER (message));
		}else
		{

			printf("Kevoree ComponentType => %s\n",TREE_STRING_POINTER (message));

			addComponentType(TREE_STRING_POINTER (message));
		}

}


static void handle_pragma_NodeType (cpp_reader *dummy)
{
	tree message = 0;

	if (pragma_lex (&message) != CPP_STRING)
	{
		warning (OPT_Wpragmas, "%<NodeType Name%>  is not a string");
		return;
	}
	if (TREE_STRING_LENGTH (message) > 1)
		if (cfun)
		{
			warning (OPT_Wpragmas, "%< NodeType%> from function %qE: %s",cfun->decl, TREE_STRING_POINTER (message));
		}else
		{
			printf("Kevoree NodeType => %s\n",TREE_STRING_POINTER (message));
			addNodeType(TREE_STRING_POINTER (message));
		}

}

static void handle_pragma_GroupType (cpp_reader *dummy)
{
	tree message = 0;
	if (pragma_lex (&message) != CPP_STRING)
	{
		warning (OPT_Wpragmas, "%<GroupType Name%>  is not a string");
		return;
	}
	if (TREE_STRING_LENGTH (message) > 1)
		if (cfun)
		{
			warning (OPT_Wpragmas, "%< GroupType%> from function %qE: %s",cfun->decl, TREE_STRING_POINTER (message));
		}else
		{

			printf("Kevoree GroupType => %s\n",TREE_STRING_POINTER (message));
			addGroupType(TREE_STRING_POINTER (message));
		}

}

static void handle_pragma_Dictionary (cpp_reader *dummy )
{
	tree message = 0;
	enum cpp_ttype token;
	token= pragma_lex (&message);

	if (token != CPP_STRING)
	{


		warning (OPT_Wpragmas, "%< Dictionary>");

		return;
	}
	if (TREE_STRING_LENGTH (message) > 1){
		if (cfun)
		{
			warning (OPT_Wpragmas,"%<Dictionary%> from function %qE: %s", cfun->decl, TREE_STRING_POINTER (message));
		}
		else
		{
			printf("Kevoree Dictionnary => %s\n",TREE_STRING_POINTER (message));
			addDictionnary(TREE_STRING_POINTER (message));
		}
	}
}

static void handle_pragma_Version (cpp_reader *dummy )
{
	tree message = 0;
	enum cpp_ttype token;
	token= pragma_lex (&message);

	if (token != CPP_STRING)
	{


		warning (OPT_Wpragmas, "%< Version>");

		return;
	}
	if (TREE_STRING_LENGTH (message) > 1){
		if (cfun)
		{
			warning (OPT_Wpragmas,"%<Version%> from function %qE: %s", cfun->decl, TREE_STRING_POINTER (message));
		}
		else
		{

			printf("Kevoree Version => %s\n",TREE_STRING_POINTER (message));
			setVersion(TREE_STRING_POINTER (message));
		}
	}
}

static void handle_pragma_groupName (cpp_reader *dummy )
{
	tree message = 0;
	enum cpp_ttype token;
	token= pragma_lex (&message);

	if (token != CPP_STRING)
	{


		warning (OPT_Wpragmas, "%< Version>");

		return;
	}
	if (TREE_STRING_LENGTH (message) > 1){
		if (cfun)
		{
			warning (OPT_Wpragmas,"%<Version%> from function %qE: %s", cfun->decl, TREE_STRING_POINTER (message));
		}
		else
		{

			printf("Kevoree GroupName  => %s\n",TREE_STRING_POINTER (message));
			setGroupName(TREE_STRING_POINTER (message));

		}
	}
}

/* Plugin callback called during pragma registration */

static void register_my_pragma (void *event_data, void *data) 
{
	// warning (0, G_("Callback to register pragmas"));
	c_register_pragma (NULL, "ComponentType", handle_pragma_ComponentType);
	c_register_pragma (NULL, "GroupType", handle_pragma_GroupType);
	c_register_pragma (NULL, "NodeType", handle_pragma_NodeType);
	c_register_pragma (NULL, "Dictionary", handle_pragma_Dictionary);


	c_register_pragma (NULL, "Version", handle_pragma_Version);
	c_register_pragma (NULL, "GroupName", handle_pragma_groupName);

}


static void event_finish(void *event_data, void *data) 
{
	printf("Writing lib.json...\n");

	closelib();
}
int plugin_init (struct plugin_name_args *plugin_info,struct plugin_gcc_version *version)
{

	printf("Kevoree Plugin initialized... \n");
	const char *plugin_name = plugin_info->full_name;

	register_callback (plugin_name, PLUGIN_PRAGMAS, register_my_pragma, NULL);
	register_callback (plugin_name, PLUGIN_FINISH, event_finish, NULL);

	return 0;
}

