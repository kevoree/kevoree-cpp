package org.kevoree.library.cpp.mavenplugin.utils;

import java.io.*;
import java.util.LinkedList;

/**
 * Created by Aymeric on 18/08/2014.
 */
public class CmakeFileBuilder {

    private LinkedList<String> link_directories_list ;

    private LinkedList<String> include_directories_list ;

    private LinkedList<String> set_var_list ;

    private LinkedList<String> target_link_lib ;

    private LinkedList<String> library_Lst ;

    private String version ="2.8" ;

    private String projectName ;

    private String internalprojectName ;

    public CmakeFileBuilder(String ProjecName) {
        link_directories_list = new LinkedList<String>() ;
        include_directories_list = new LinkedList<String>() ;
        set_var_list = new LinkedList<String>() ;
        target_link_lib = new LinkedList<String>();
        library_Lst = new LinkedList<String>();
        this.projectName = ProjecName ;
        internalprojectName = this.projectName +"_intern";
    }


    public void add_Include_Directories(String file){
        include_directories_list.add("include_directories("+file+")\n") ;
    }

    public void set_Cmake_Version(String version){
       this.version = version ;
    }

    public void add_link_Directories(String file){
        link_directories_list.add("LINK_directories("+file+")\n") ;
    }

    public void add_set(String varName,String varVal){
        set_var_list.add("set("+varName+" "+varVal+")\n");
    }

    public void add_target_link_lib( String varVal){
        target_link_lib.add("TARGET_LINK_LIBRARIES("+internalprojectName+" "+varVal+")\n") ;
    }



    public void buildCmake() throws IOException {
        File file = new File("./CMakeLists.txt") ;

        if (!file.exists()) {
            file.createNewFile();
        }else
        {
            file.delete();
            file.createNewFile();
        }

        FileWriter fw = new FileWriter(file);
        fw.write("cmake_minimum_required(VERSION" + version+")\n" );
        fw.write("project("+projectName +")\n" );
        for (String s : include_directories_list) {
            fw.write(s);
        }

        for (String s : link_directories_list) {
            fw.write(s);
        }

        for (String s : set_var_list) {
            fw.write(s);
        }

        fw.write("file(GLOB_RECURSE "+internalprojectName+"_files src/*.cpp)\n") ;
        fw.write("ADD_LIBRARY("+projectName+" SHARED    ${"+internalprojectName+"_files} )\n") ;

        for (String s : target_link_lib) {
            fw.write(s);
        }

        for (String s : library_Lst) {
            fw.write(s);
        }
    }

}
