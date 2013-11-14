

#include <trace/TraceSequence.h>
#include <json/JSONModelLoader.h>
#include <compare/ModelCompare.h>
#include <iostream>
#include <fstream>
#include <DefaultkevoreeFactory.h>

int main(int argc,char **argv)
{

	
 DefaultkevoreeFactory factory;

 JSONModelLoader loader;

 loader.setFactory(&factory);
ifstream myfile;
 myfile.open ("jedModel.json");
 if(!myfile){
     cout << "no file trace" << endl;
 }

ifstream myfile2;
 myfile2.open ("jedModel2.json");
 if(!myfile2){
     cout << "no file trace" << endl;
 }


ContainerRoot *model = (ContainerRoot*)loader.loadModelFromStream(myfile)->front();
ContainerRoot *model2 = (ContainerRoot*)loader.loadModelFromStream(myfile2)->front();


ModelCompare *kompare = new ModelCompare();
TraceSequence *seq = kompare->diff(model,model2);

cout << seq->exportToString() << endl;


}
