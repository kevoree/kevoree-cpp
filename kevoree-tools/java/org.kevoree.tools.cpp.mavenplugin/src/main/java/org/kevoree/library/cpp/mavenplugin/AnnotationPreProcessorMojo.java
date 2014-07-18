package org.kevoree.library.cpp.mavenplugin;

import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.MojoFailureException;

import org.apache.maven.project.MavenProject;

import org.kevoree.*;
import org.kevoree.ComponentType;
import org.kevoree.NodeType;
import org.kevoree.Repository;
import org.kevoree.cpp.preprocessor.ast.*;
import org.kevoree.cpp.preprocessor.ast.ChannelType;
import org.kevoree.cpp.preprocessor.ast.GroupType;
import org.kevoree.cpp.preprocessor.lexer.Lexer;
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
 * @goal generate
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
                TypeDefinition type=null;
                try {
                    Lexer te = new Lexer(new FileInputStream(f));
                    List<Statment> options = new ArrayList<Statment>();
                    Statment token =   te.nextToken();

                    while(  !(token instanceof EOF)  ){

                        if(!(token instanceof org.kevoree.cpp.preprocessor.ast.Unsupported)){


                            DeployUnit du =factory.createDeployUnit();
                            du.setName(project.getArtifactId());
                            du.setGroupName(project.getGroupId());
                            du.setVersion(project.getVersion());
                            du.setType("so");

                            getLog().info("Type found =>" +token);

                            if(token instanceof org.kevoree.cpp.preprocessor.ast.NodeType){

                                type =factory.createNodeType();
                                type.setName(token.getName());
                                type.setDeployUnit(du);
                                type.setVersion(project.getVersion());
                                type.setAbstract(false);
                                root.addTypeDefinitions(type);
                                root.addDeployUnits(du);


                            }else if(token instanceof org.kevoree.cpp.preprocessor.ast.ComponentType){

                                type= factory.createComponentType();
                                type.setName(token.getName());
                                type.setDeployUnit(du);
                                type.setVersion(project.getVersion());
                                type.setAbstract(false);
                                root.addTypeDefinitions(type);
                                root.addDeployUnits(du);

                            }else if(token instanceof org.kevoree.cpp.preprocessor.ast.Param){
                                options.add( token);

                            }else if(token instanceof org.kevoree.cpp.preprocessor.ast.GroupType) {
                                type = factory.createGroupType();
                                type.setName(token.getName());
                                type.setDeployUnit(du);
                                type.setVersion(project.getVersion());
                                type.setAbstract(false);
                                root.addTypeDefinitions(type);
                                root.addDeployUnits(du);
                            }      else if(token instanceof ChannelType){
                                    type= factory.createChannelType();
                                    type.setName(token.getName());
                                    type.setDeployUnit(du);
                                    type.setVersion(project.getVersion());
                                    type.setAbstract(false);
                                    root.addTypeDefinitions(type);
                                    root.addDeployUnits(du);

                            }else if(token instanceof org.kevoree.cpp.preprocessor.ast.Input){
                                options.add( token);

                            }else if(token instanceof org.kevoree.cpp.preprocessor.ast.Provide){
                                options.add( token);
                            }

                        }

                        token =   te.nextToken();
                    }
                    if(type != null) {
                        DictionaryType paramtype = factory.createDictionaryType();

                        type.setDictionaryType(paramtype);
                        for (Statment option : options) {

                            if (option instanceof Param) {
                                Param param = (Param) option;

                                DictionaryAttribute attport = factory.createDictionaryAttribute();

                                attport.setOptional(param.isOptional());
                                attport.setDatatype("string");
                                attport.setFragmentDependant(param.isFragdep());
                                attport.setName(param.getName());
                                attport.setDefaultValue(param.getDefaultValue());

                                paramtype.addAttributes(attport);


                            }else if (option instanceof Input) {

                                PortTypeRef port=     factory.createPortTypeRef();
                                port.setName(option.getName());

                                ((ComponentType)type).addRequired(port);

                            }else if (option instanceof Provide) {
                                PortTypeRef port=     factory.createPortTypeRef();
                                port.setName(option.getName());

                                ((ComponentType)type).addProvided(port);
                            }
                        }
                    }else {

                        getLog().error("no typedefintion "+type);
                    }



                } catch (Exception e) {
                    e.printStackTrace();
                }
            }

            try
            {
                String model = serializer.serialize(root);
                getLog().info("Generate Model Json => " + model);
                String path =inputCFile.getPath()+File.separator+"src"+File.separator+"main"+File.separator+"resources"+File.separator+"KEV-INF"+File.separator;
                PluginHelper.writeFile(path+"lib.json",model);
            } catch (IOException e) {
                e.printStackTrace();
            }


        }
    }
}

