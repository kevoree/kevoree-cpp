package org.kevoree.library.cpp.mavenplugin.utils;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by jed on 01/07/14.
 */
public class PluginHelper {

    public static void scanForHeader(File path, List<File> allFiles) {

        if (path.isDirectory()) {
            File[] list = path.listFiles();
            if (list != null) {
                for (int i = 0; i < list.length; i++) {
                    scanForHeader(list[i], allFiles);
                }
            } else {
                System.err.println(path + " : Erreur de lecture.");
            }
        } else {
            String currentFilePath = path.getAbsolutePath();

            if(currentFilePath.contains(".h")){
                allFiles.add(new File(currentFilePath));
            }

        }
    }

    public static void writeFile(String path,String data) throws IOException
    {
        File file = new File(path.substring(0,path.lastIndexOf("/")));
        file.mkdirs();

        FileWriter fileWriter = new FileWriter(path);
        BufferedWriter out_j = new BufferedWriter(fileWriter);
        out_j.write(data);
        out_j.close();


    }
}
