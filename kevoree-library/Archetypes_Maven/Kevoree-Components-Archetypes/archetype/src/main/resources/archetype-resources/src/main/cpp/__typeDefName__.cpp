#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $symbol_escape = '"' )
#set( $symbol_escape = '<')
#set( $symbol_escape = '>')


${hashSymbol}include ${quotes}${componentName}.h${quotes}


//Generated code, do not remove
extern "C"{  
AbstractComponent* create(){
	return new ${componentName}();
}
}
extern "C" {
void destroy_object( ${componentName} * object )
{
	delete object;
}
}




${componentName}::${componentName}()
{

}
${componentName}::~${componentName}()
{


}

void ${componentName}::start()
{

	cout <<"The ${componentName} component is starting"  << endl;
}

void ${componentName}::stop(){
	cout <<"The ${componentName} component is stopping" << endl;
}


void ${componentName}::update()
{	
	cout <<"The ${componentName} component is updating" << endl;
}


