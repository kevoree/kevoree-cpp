package org.kevoree.library.cpp.mavenplugin;

import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.MojoFailureException;
import org.apache.maven.plugins.annotations.Parameter;
import org.apache.maven.project.MavenProject;
import org.kevoree.library.cpp.mavenplugin.utils.CMakeFileBuilder;
import org.kevoree.library.cpp.mavenplugin.utils.Mojos;


import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.Map;


/**
 * @author Aymeric Hervieu
 * @goal build-cmake
 */
public class CompileMojo extends AbstractMojo {
    /**
     * @parameter
     */
    private List<String> includeDir;


    /**
     * @parameter
     */
    private List<String> libs;


    /**
     * POM
     *
     * @parameter expression="${project}"
     * @readonly
     * @required
     */

    protected MavenProject project;

    /**
     * @parameter default-value="${basedir}"
     */
    private File inputCFile;

    @Override
    public void execute() throws MojoExecutionException, MojoFailureException {
        String kevpath = System.getenv("KEVOREE_PATH");
        Map<String, String> variables = System.getenv();
        String[] projectNameTab = project.getName().split("::") ;
        CMakeFileBuilder cmfb = new CMakeFileBuilder(projectNameTab[projectNameTab.length-1].trim(), inputCFile.getPath()) ;
        cmfb.add_set("KEVOREEROOT", kevpath);
        cmfb.add_set("CMAKE_CXX_FLAGS", "\"${CMAKE_CXX_FLAGS}   -std=c++11 -pedantic\"") ;
        cmfb.add_Include_Directories("${KEVOREEROOT}/include/kevoree-core/");
        cmfb.add_Include_Directories("${KEVOREEROOT}/include/kevoree-core/model/");
        cmfb.add_Include_Directories("${KEVOREEROOT}/include/");




        if(includeDir != null) {
            for (String s : includeDir) {
                cmfb.add_Include_Directories(s);
            }
        }
        cmfb.add_link_Directories("${KEVOREEROOT}/lib/");

        if(libs != null) {
            for (String lib : libs) {
                cmfb.add_target_link_lib(lib);
            }
        }

        try {
            cmfb.buildCmake();
        } catch (IOException e) {
            e.printStackTrace();
        }
        getLog().info("building make file");
        String path = System.getenv("PATH");
        ProcessBuilder pb = new ProcessBuilder("cmake",".");
        Map<String, String> env = pb.environment();
        env.put("PATH",path);
        try {
            Mojos.waitFor(pb,this);

        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();

         }
        getLog().info("Compiling");
        ProcessBuilder pb2 = new ProcessBuilder("make");
        try {

            Mojos.waitFor(pb2,this);
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

      //  cmfb.getCmakeFile().delete();

    }

}
