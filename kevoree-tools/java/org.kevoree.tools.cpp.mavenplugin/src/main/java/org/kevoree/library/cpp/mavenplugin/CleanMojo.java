package org.kevoree.library.cpp.mavenplugin;

import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.MojoFailureException;
import org.apache.maven.project.MavenProject;
import org.kevoree.library.cpp.mavenplugin.utils.Deleters;

import java.io.File;
import java.io.FileFilter;


/**
 * @author Aymeric Hervieu
 * @goal clean-cmake
 */

public class CleanMojo extends AbstractMojo {

    /**
     * POM
     *
     * @parameter expression="${project}"
     * @readonly
     * @required
     */

    protected MavenProject project;

    @Override
    public void execute() throws MojoExecutionException, MojoFailureException {
//plugin to remove file

        File working_dir = project.getBasedir();
        File f = new File(working_dir.toString() + "/CMakeCache.txt");
       // System.out.print(f.toString());
        if (f.exists()) {
            //System.out.println("Deleting : " + f.getName());
            f.delete();
        }
        File f2 = new File(working_dir.toString() + "/CMakeFiles");
        if (f2.exists()) {
            //System.out.println("Deleting : " + f2.getName());
            Deleters.removeDirectory(f2);
        }
        File f3 = new File(working_dir.toString() + "/cmake_install.cmake");
        if (f3.exists()) {
            //System.out.println("Deleting : " + f3.getName());
            f3.delete();
        }
        File f4 = new File(working_dir.toString() + "/target");
        if (f4.exists()) {
          //  System.out.println("Deleting : " + f4.getName());
            Deleters.removeDirectory(f4);
        }
        File f5 = new File(working_dir.toString() + "/Makefile");
        if (f5.exists()) {
        //    System.out.println("Deleting : " + f5.getName());
           f5.delete();
        }
        File f6 = new File(working_dir.toString() + "/CMakeLists.txt");
        if (f6.exists()) {
          //  System.out.println("Deleting : " + f6.getName());
            f6.delete();
        }
        File[] res =  working_dir.listFiles(new FileFilter() {
            @Override
            public boolean accept(File pathname) {


                return pathname.getName().toString().trim().contains(".dylib") || pathname.getName().toString().trim().contains(".so") ;
            }
        });

        for (File re : res) {

        }
        if(res.length > 0)
        {
            res[0].delete();
        }

    }





}


