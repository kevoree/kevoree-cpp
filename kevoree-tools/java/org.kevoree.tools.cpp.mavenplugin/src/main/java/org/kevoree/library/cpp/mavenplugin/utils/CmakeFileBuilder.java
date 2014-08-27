package org.kevoree.library.cpp.mavenplugin.utils;

import java.io.*;
import java.util.LinkedList;

/**
 * Created by Aymeric on 18/08/2014.
 */
public class CMakeFileBuilder {

    private LinkedList<String> link_directories_list ;

    private LinkedList<String> include_directories_list ;

    private LinkedList<String> set_var_list ;

    private LinkedList<String> target_link_lib ;

    private LinkedList<String> library_Lst ;

    private String version ="2.8" ;

    private String projectName ;

    private String internalprojectName ;

    private String path ;

    private File cmakeFile ;


    public static String compilationCmd = "IF(${CMAKE_SYSTEM_NAME} MATCHES \"Linux\")\n" +
            "\n" +
            "   SET(ENABLE_CXX11 \"-std=c++11\")\n" +
            "   EXECUTE_PROCESS(COMMAND \"${CMAKE_CXX_COMPILER} -dumpversion\" OUTPUT_VARIABLE GCC_VERSION)\n" +
            "   if (GCC_VERSION VERSION_LESS 4.7)\n" +
            "      SET(ENABLE_CXX11 \"-std=c++0x\")\n" +
            "   endif()\n" +
            "   SET(CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS} ${ENABLE_CXX11}\")\n" +
            "endif()\n" ;

    public CMakeFileBuilder(String ProjecName, String basePath) {
        link_directories_list = new LinkedList<String>() ;
        include_directories_list = new LinkedList<String>() ;
        set_var_list = new LinkedList<String>() ;
        target_link_lib = new LinkedList<String>();
        library_Lst = new LinkedList<String>();
        this.projectName = ProjecName ;
        internalprojectName = this.projectName +"_intern";
        path = basePath ;
    }


    public void add_Include_Directories(String file){
        include_directories_list.add("include_directories("+file+")\n") ;
    }

    public void set_Cmake_Version(String version){
       this.version = version ;
    }

    public void add_link_Directories(String file){
        link_directories_list.add("link_directories("+file+")\n") ;
    }

    public void add_set(String varName,String varVal){
        set_var_list.add("set("+varName+" "+varVal+")\n");
    }

    public void add_target_link_lib( String varVal){
        target_link_lib.add("TARGET_LINK_LIBRARIES("+projectName+" "+varVal+")\n") ;
    }


    public File getCmakeFile() {
        return cmakeFile;
    }

    public void buildCmake() throws IOException {

         cmakeFile = new File(path +File.separator +"CMakeLists.txt") ;

        if (!cmakeFile.exists()) {
            cmakeFile.createNewFile();
        }else
        {
            cmakeFile.delete();
            cmakeFile.createNewFile();
        }

        FileWriter fw = new FileWriter(cmakeFile);
        fw.write("cmake_minimum_required(VERSION " + version+")\n" );
        fw.write("project("+projectName +")\n" );

        for (String s : set_var_list) {
            fw.write(s);
        }
        fw.write("\n" );
       fw.write(compilationCmd);
        fw.write("\n" );
        for (String s : include_directories_list) {
            fw.write(s);
        }
        fw.write("\n" );
        for (String s : link_directories_list) {
            fw.write(s);
        }

        fw.write("\n" );
        fw.write("file(GLOB_RECURSE "+internalprojectName+"_files src/*.cpp)\n") ;
        fw.write("ADD_LIBRARY("+projectName+" SHARED ${"+internalprojectName+"_files} )\n") ;
        fw.write("\n" );
        for (String s : target_link_lib) {
            fw.write(s);
        }
        fw.write("\n" );
        for (String s : library_Lst) {
            fw.write(s);
        }
        fw.close();
    }

}
