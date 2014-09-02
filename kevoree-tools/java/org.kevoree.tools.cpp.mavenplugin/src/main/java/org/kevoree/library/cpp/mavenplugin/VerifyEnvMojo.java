package org.kevoree.library.cpp.mavenplugin;

import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.MojoFailureException;

import java.io.IOException;

/**
 * Created by Aymeric on 02/09/2014.
 */


/**
 * @author Aymeric Hervieu
 * @goal environment-checker
 */

 public class  VerifyEnvMojo  extends AbstractMojo {


    @Override
    public void execute() throws MojoExecutionException, MojoFailureException {

        String missing_element  ="" ;
        if(!verifyKevoreePath()){

            getLog().error("Please set up your KEVOREE_PATH environment variable (export KEVOREE_PATH=/Kev/Path)..");
        }
     /*   if(!verifiyGit())
        {
            getLog().error("git is missing, please install it or update your path ");
        }*/
        if(!verifiyGcc())
        {
            getLog().error("gcc is missing, please install it or update your path ");
        }
        if(!verifiyGpp())
        {
            getLog().error("g++ is missing, please install it or update your path ");
        }
        if(!verifiyCmake())
        {
            getLog().error("CMake is missing, please install it or update your path ");
        }
        if(System.getProperty("os.name").toLowerCase().startsWith("mac")){
            if(!verifyClang())
            {
                getLog().error("clang is missing, please install it or update your path ");
            }

            if(!verifyClangpp())
            {
                getLog().error("clang++ is missing, please install it or update your path ");
            }
        }

    }

    private boolean verifyKevoreePath() {

        String kevPath = System.getenv("KEVOREE_PATH");
        if (kevPath == null){
            return false;
        }else
        {
            return true;
        }
    }

    private boolean verifiyCmake(){
        return runtimeVerfier("cmake") ;
    }

    private boolean verifiyGit(){
        return runtimeVerfier("git") ;
    }

    private boolean verifiyGcc(){
        return runtimeVerfier("gcc") ;
    }

    private boolean verifiyGpp(){
        return runtimeVerfier("g++") ;
    }

    private boolean verifyClang(){

        return runtimeVerfier("clang") ;
    }

    private boolean verifyClangpp(){

        return runtimeVerfier("clang++") ;
    }

    private boolean runtimeVerfier(String runtime){
        Runtime rt = Runtime.getRuntime();
        Process proc = null;
        try {
            proc = rt.exec(runtime);
        } catch (IOException e) {

           return false ;
        }
        int exitVal = proc.exitValue();
        getLog().info("Exit value " + exitVal + " for " + runtime);
        return exitVal == 0 ;

    }
}
