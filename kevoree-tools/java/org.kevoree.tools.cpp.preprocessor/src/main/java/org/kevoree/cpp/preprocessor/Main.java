package org.kevoree.cpp.preprocessor;

import org.kevoree.cpp.preprocessor.ast.EOF;
import org.kevoree.cpp.preprocessor.ast.Statment;
import org.kevoree.cpp.preprocessor.ast.Unsupported;
import org.kevoree.cpp.preprocessor.lexer.Lexer;



import java.io.*;
import java.util.ArrayList;

import java.util.List;

/**
 * Created by jed on 30/06/14.
 */
public class Main {

    public static void listeRepertoire(File path, List<String> allFiles) {

        if (path.isDirectory()) {
            File[] list = path.listFiles();
            if (list != null) {
                for (int i = 0; i < list.length; i++) {
                    // Appel récursif sur les sous-répertoires
                    listeRepertoire(list[i], allFiles);
                }
            } else {
                System.err.println(path + " : Erreur de lecture.");
            }
        } else {
            String currentFilePath = path.getAbsolutePath();

            if(currentFilePath.contains(".h")){
                allFiles.add(currentFilePath);
            }

        }
    }




    public static void  main(String argv[]) throws Exception {

        List<String> files = new ArrayList<String>();

    listeRepertoire(new File("/home/jed/KEVOREE_PROJECT/kevoree-cpp/kevoree-library"),files);

        for(String file :files){
       //     System.out.println(file);
            Lexer te = new Lexer(new FileInputStream(new File(file)));
            Statment token =   te.nextToken();

            while(  !(token instanceof EOF )  ){

                if(!(token instanceof       Unsupported)){
                    System.out.println(token);

                }

                token =   te.nextToken();
            }
        }



    }
}
