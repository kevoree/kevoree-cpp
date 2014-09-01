#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $symbol_escape = '"' )


#ifndef __${componentName}_H
#define __${componentName}_H

${hashSymbol}include ${lt}kevoree-core/api/AbstractComponent.h${gt}


#pragma ComponentType "${componentName}"
class ${componentName} :public AbstractComponent
{
	public:
	${componentName}();
	~${componentName}();

	 void start();
	 void stop();
	 void update();

};

#endif /*__${componentName}_H*/
