package org.kevoree.library.cpp.mavenplugin;

import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.MojoFailureException;
import org.apache.maven.project.MavenProject;

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
            removeDirectory(f2);
        }
        File f3 = new File(working_dir.toString() + "/cmake_install.cmake");
        if (f3.exists()) {
            f3.delete();
        }
        File f4 = new File(working_dir.toString() + "/target");
        if (f4.exists()) {
            removeDirectory(f4);
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




    private static boolean removeDirectory(File directory) {

        // System.out.println("removeDirectory " + directory);

        if (directory == null)
            return false;
        if (!directory.exists())
            return true;
        if (!directory.isDirectory())
            return false;

        String[] list = directory.list();

        // Some JVMs return null for File.list() when the
        // directory is empty.
        if (list != null) {
            for (int i = 0; i < list.length; i++) {
                File entry = new File(directory, list[i]);

                //        System.out.println("\tremoving entry " + entry);

                if (entry.isDirectory())
                {
                    if (!removeDirectory(entry))
                        return false;
                }
                else
                {
                    if (!entry.delete())
                        return false;
                }
            }
        }

        return directory.delete();
    }



}


