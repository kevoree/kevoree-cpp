// todo
/**
 * Author: jedartois@gmail.com
 * Date: 24/10/13
 * Time: 18:36
 */
/*

 #ifndef __XMIPARSER_H
 #define __XMIPARSER_H

 #include <string>
 #include <sstream>
 #include <iostream>

using namespace std;

class XMIParser

{

public :

   XMIParser();
   ~XMIParser(istream &inputStream);
   bool hasNext();
   string getLocalName();
   int getAttributeCount();
   string getAttributeLocalName(int i) ;
   string getAttributePrefix(int i) ;
   string getAttributeValue(int i) ;
   char readChar() ;
   int next();


private :
   int index ;
   char currentChar ;
   string xmlVersion ;
   string xmlCharset ;

   string tagName ;
   string tagPrefix;

   std::list<string> attributesNames ;
   std::list<string> attributesPrefixes ;
   std::list<string> attributesValues;

   string attributeName;
   string attributeName;
   string attributeValue;

   bool readSingleton;

   void read_lessThan();
   void read_upperThan();
   void read_xmlHeader();
   void read_closingTag() ;
   void read_openTag() ;
   void read_tagName() ;
   void read_attributes() ;

};

*/
