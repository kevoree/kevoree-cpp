package org.kevoree.library.cpp.mavenplugin;

import org.apache.maven.model.DeploymentRepository;
import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.MojoFailureException;
import org.apache.maven.project.MavenProject;
import org.kevoree.library.cpp.mavenplugin.utils.MavenDeployer;
import org.kevoree.library.cpp.mavenplugin.utils.PluginHelper;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * @author jedartois
 * @author <a href="mailto:jedartois@gmail.com">Jean-Emile DARTOIS</a>
 * @goal deploy
 */
public class DeployMojo extends AbstractMojo {
    /**
     * The directory root under which processor-generated source files will be placed; files are placed in
     * subdirectories based on package namespace. This is equivalent to the <code>-s</code> argument for apt.
     *
     * @parameter default-value="${project.build.directory}/generated-sources/kevoree"
     */
    private File sourceOutputDirectory;

    /**
     * @parameter default-value="${basedir}"
     */
    private File inputCFile;


    /**
     * POM
     *
     * @parameter expression="${project}"
     * @readonly
     * @required
     */

    protected MavenProject project;

    private MavenDeployer deployer;

    @Override
    public void execute() throws MojoExecutionException, MojoFailureException {

        // looking for so
        List<File> types_lib = new ArrayList<File>();
        List<String> filter_lib = new ArrayList<String>();
        filter_lib.add(".so");
        filter_lib.add(".dylib");
        PluginHelper.scanForHeader(inputCFile, types_lib, filter_lib);

        if(filter_lib.size() > 0){
            //    PluginHelper.copyFileUsingStream( types_so.get(0),new File(path+types_so.get(0).getName()));

            DeploymentRepository repo=null;
            if(  project.getDistributionManagement()!=null && project.getVersion().contains("SNAPSHOT")){
                repo =   project.getDistributionManagement().getSnapshotRepository();

            }else if(project.getDistributionManagement()!=null)
            {
                repo = project.getDistributionManagement().getRepository();
            }
            if(repo != null ){
                deployer = new MavenDeployer(repo.getId(),repo.getUrl());

                try {
                    getLog().info("Deploy Typedefintion  "+repo.getUrl());
                    String path =inputCFile.getPath()+File.separator+"src"+File.separator+"main"+File.separator+"resources"+File.separator+"KEV-INF"+File.separator;
                    File json = new File (path+"lib.json");
                    if(json.exists())
                    {
                        deployer.deploy(project.getGroupId(),project.getArtifactId(),project.getVersion(),json.getAbsolutePath(),"json");

                    }else
                    {
                        getLog().error("lib.json not found");

                    }

                    getLog().info("Deploy dynamic library "+types_lib.get(0).getName()+" "+repo.getUrl());
                    deployer.deploy(project.getGroupId(),project.getArtifactId(),project.getVersion(),types_lib.get(0).getAbsolutePath(),"so");


                } catch (IOException e) {
                    e.printStackTrace();
                }
                //      deployer.deploy(project.getGroupId(),project.getArtifactId(),project.getVersion(),path+"lib.json","json");
            }else{
                getLog().error("There is not distributionManagement specify for deploy artifact");
            }


        }
    }
}
