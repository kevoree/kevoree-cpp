package org.kevoree.library.cpp.mavenplugin.utils;

import java.io.*;
import java.util.List;
import java.util.Map;

/**
 * Created by jed on 01/07/14.
 */
public class PluginHelper {

    public static void scanForHeader(File path, List<File> allFiles,List<String> filters) {

        if (path.isDirectory()) {
            File[] list = path.listFiles();
            if (list != null) {
                for (int i = 0; i < list.length; i++) {
                    scanForHeader(list[i], allFiles,filters);
                }
            } else {
                System.err.println(path + " : Erreur de lecture.");
            }
        } else {
            String currentFilePath = path.getAbsolutePath();
            for(String filter :filters){
                if(currentFilePath.contains(filter)){
                    allFiles.add(new File(currentFilePath));
                }
            }


        }
    }
public static  void run(String... command){
    ProcessBuilder builder = new ProcessBuilder(command);
    builder.redirectErrorStream(true);
    Map<String, String> environ = builder.environment();

    final Process process;
    try {
        process = builder.start();

        InputStream is = process.getInputStream();
        InputStreamReader isr = new InputStreamReader(is);
        BufferedReader br = new BufferedReader(isr);
        String line;

        System.out.println("Program terminated!");
    } catch (IOException e) {
        e.printStackTrace();
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


    public static void copyFileUsingStream(File source, File dest) throws IOException {
        InputStream is = null;
        OutputStream os = null;
        try {
            is = new FileInputStream(source);
            os = new FileOutputStream(dest);
            byte[] buffer = new byte[1024];
            int length;
            while ((length = is.read(buffer)) > 0) {
                os.write(buffer, 0, length);
            }
        } finally {
            is.close();
            os.close();
        }
    }
}
