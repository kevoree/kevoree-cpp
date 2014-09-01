#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $symbol_escape = '"' )
#set( $symbol_escape = '<')
#set( $symbol_escape = '>')

#if( $typeDef == 'component' )
#set ($typeVal = 'AbstractComponent')
#set ($type = 'ComponentType')
#elseif( $typeDef == 'channel')
#set ($typeVal = 'AbstractChannel')
#set ($type = 'ChannelType')
#elseif ( $typeDef == 'group')
#set ($typeVal = 'AbstractGroup')
#set ($type = 'GroupType')
#end


${hashSymbol}include ${quotes}${typeDefName}.h${quotes}


//Generated code, do not remove
extern "C"{  
${typeVal}* create(){
	return new ${typeDefName}();
}
}
extern "C" {
void destroy_object( ${typeDefName} * object )
{
	delete object;
}
}




${typeDefName}::${typeDefName}()
{

}
${typeDefName}::~${typeDefName}()
{


}

void ${typeDefName}::start()
{

	cout <<"The ${typeDefName} ${typeDef} is starting"  << endl;
}

void ${typeDefName}::stop(){
	cout <<"The ${typeDefName} ${typeDef} is stopping" << endl;
}


void ${typeDefName}::update()
{	
	cout <<"The ${typeDefName} ${typeDef} is updating" << endl;
}

#if( $typeDef == 'channel')
void  ${typeDefName}::dispatch(std::string data)
{
// FIX ME POC
	Channel *element =	(Channel*)getModelElement();
	for ( std::map<string,MBinding*>::iterator it = element->bindings.begin();  it !=  element->bindings.end(); ++it)
	{
		MBinding *binding = it->second;
		Port *p = binding->port;
		ComponentInstance *component = (ComponentInstance*)binding->port->eContainer();
		Port *provided = component->findprovidedByID(p->internalGetKey());
		if(provided != NULL)
		{
			//std::cout << component->name+"/"+provided->name << std::endl;
			std::string path =component->name+"/"+provided->name;
			if(local.find(path) != local.end())
			{
				local[path]->receive(data);

			}else {
				std::cout << "not found "<<path << std::endl;
			}


		}


	}

}
#end


