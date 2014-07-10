package org.kevoree.library.cpp.mavenplugin;

import org.apache.maven.model.*;
import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.MojoFailureException;

import org.apache.maven.project.MavenProject;

import org.kevoree.*;
import org.kevoree.Repository;
import org.kevoree.cpp.preprocessor.lexer.Lexer;
import org.kevoree.cpp.preprocessor.lexer.Token;
import org.kevoree.impl.DefaultKevoreeFactory;
import org.kevoree.library.cpp.mavenplugin.utils.MavenDeployer;
import org.kevoree.library.cpp.mavenplugin.utils.PluginHelper;
import org.kevoree.modeling.api.json.JSONModelSerializer;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
/**
 * @author jedartois
 * @author <a href="mailto:jedartois@gmail.com">Jean-Emile DARTOIS</a>
 * @version $Id$
 * @execute phase="compile"
 * @goal generate
 * @phase generate-sources
 * @requiresDependencyResolution compile
 */
public class AnnotationPreProcessorMojo extends AbstractMojo {

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

    private  MavenDeployer deployer;
    @Override
    public void execute() throws MojoExecutionException, MojoFailureException {

        if (inputCFile == null || !(inputCFile.exists())) {
            getLog().warn("InputDir null => ");
        } else {
            DefaultKevoreeFactory factory = new DefaultKevoreeFactory();
            JSONModelSerializer serializer = new JSONModelSerializer();
            ContainerRoot root=factory.createContainerRoot();


            List<org.apache.maven.model.Repository>  repositories = project.getRepositories();

            // add repos
            for(org.apache.maven.model.Repository r : repositories){
                Repository repository =   factory.createRepository();
                repository.setUrl(r.getUrl());
                root.addRepositories(repository);
            }

            // searching for typedefintions
            List<File> types = new ArrayList<File>();
            PluginHelper.scanForHeader(inputCFile,types, Collections.singletonList(".h"));
            for (File f : types) {

                try {
                    Lexer te = new Lexer(new FileInputStream(f));
                    Token token =   te.nextToken();
                    DictionaryType dictionaryType =    factory.createDictionaryType();
                    while(  token.getType() != Token.TokenType.END_OF_FILE  )
                    {

                        DeployUnit du =factory.createDeployUnit();
                        du.setName(token.getValue());
                        du.setGroupName(project.getGroupId());
                        du.setVersion(project.getVersion());
                        du.setType("so");



                        if(token.getType() == Token.TokenType.NodeType)
                        {
                            getLog().info("NodeType found =>" +token);
                            NodeType   type =factory.createNodeType();

                            type.setName(token.getValue());
                            type.setDeployUnit(du);
                            type.setAbstract(false);
                            root.addTypeDefinitions(type);
                            root.addDeployUnits(du);

                        }else    if(token.getType() == Token.TokenType.ComponentType){
                            getLog().info("ComponentType found =>" +token);
                            ComponentType type= factory.createComponentType();
                            type.setName(token.getValue());
                            type.setDeployUnit(du);
                            type.setAbstract(false);
                            root.addTypeDefinitions(type);
                            root.addDeployUnits(du);
                        }else if(token.getType() == Token.TokenType.Dictionary){
                            getLog().info("Dictionarys found =>" +token);

                            DictionaryAttribute dictionaryAttribute = factory.createDictionaryAttribute();

                            dictionaryAttribute.setName(token.getValue());


                        }





                        token =   te.nextToken();
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }

            try
            {

                // looking for so
                List<File> types_so = new ArrayList<File>();

                String model = serializer.serialize(root);
                getLog().debug("Generate Model Json => " + model);
                String path =inputCFile.getPath()+File.separator+"src"+File.separator+"main"+File.separator+"resources"+File.separator+"KEV-INF"+File.separator;
                PluginHelper.writeFile(path+"lib.json",model);

                List<String> list = new ArrayList<String>();
                list.add(".so");
                list.add(".dylib");
                PluginHelper.scanForHeader(inputCFile,types_so,list);

                if(types_so.size() > 0){
                    //    PluginHelper.copyFileUsingStream( types_so.get(0),new File(path+types_so.get(0).getName()));

                    DeploymentRepository repo=null;
                    if(project.getVersion().contains("SNAPSHOT")){
                        repo =   project.getDistributionManagement().getSnapshotRepository();

                    }else
                    {
                        repo = project.getDistributionManagement().getRepository();
                    }
                    if(repo != null ){
                        deployer = new MavenDeployer(repo.getId(),repo.getUrl());

                        deployer.deploy(project.getGroupId(),project.getArtifactId(),project.getVersion(),types_so.get(0).getAbsolutePath(),"so");
                        deployer.deploy(project.getGroupId(),project.getArtifactId(),project.getVersion(),path+"lib.json","json");
                    }else{
                        getLog().error("there is not repository specify for deploy artifact");

                    }


                }
            } catch (IOException e) {
                e.printStackTrace();
            }


        }
    }
}
