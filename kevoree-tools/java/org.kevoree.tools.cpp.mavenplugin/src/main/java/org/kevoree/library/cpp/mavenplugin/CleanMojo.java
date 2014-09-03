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
        System.out.print(f.toString());
        if (f.exists()) {
            System.out.print("exe");
            f.delete();
        }
        File f2 = new File(working_dir.toString() + "/CMakeFiles");
        if (f2.exists()) {
            Deleters.removeDirectory(f2);
        }
        File f3 = new File(working_dir.toString() + "/cmake_install.cmake");
        if (f3.exists()) {
            f3.delete();
        }
        File f4 = new File(working_dir.toString() + "/target");
        if (f4.exists()) {
            Deleters.removeDirectory(f4);
        }
        File f5 = new File(working_dir.toString() + "/Makefile");
        if (f5.exists()) {
           f5.delete();
        }
        File f6 = new File(working_dir.toString() + "/CMakeLists.txt");
        if (f6.exists()) {
            f6.delete();
        }
        File[] res =  working_dir.listFiles(new FileFilter() {
            @Override
            public boolean accept(File pathname) {

                System.out.print(pathname.getName());
                return pathname.toString().trim().contains("dylib") || pathname.toString().trim().contains("so") ;
            }
        });
        if(res.length > 0)
        {
            res[0].delete();
        }

    }





}


