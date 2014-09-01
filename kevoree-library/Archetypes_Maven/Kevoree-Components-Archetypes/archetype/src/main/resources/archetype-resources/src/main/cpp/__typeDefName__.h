#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $symbol_escape = '"' )

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


#ifndef __${typeDefName}_H
#define __${typeDefName}_H

${hashSymbol}include ${lt}kevoree-core/api/${typeVal}.h${gt}


#pragma ${type} "${typeDefName}"
#if( $typeDef == 'group')
#pragma Param "port" defaultValue="9000" fragdep
#end
class ${typeDefName} :public ${typeVal}
{
	public:
	${typeDefName}();
	~${typeDefName}();

	 void start();
	 void stop();
	 void update();
#if( $typeDef == 'channel')
     void dispatch(std::string data);
#end
};

#endif /*__${typeDefName}_H*/
