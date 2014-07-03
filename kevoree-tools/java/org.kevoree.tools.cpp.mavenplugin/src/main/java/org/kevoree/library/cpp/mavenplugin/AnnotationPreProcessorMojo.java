package org.kevoree.library.cpp.mavenplugin;

import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.MojoFailureException;

import org.apache.maven.project.MavenProject;

import org.kevoree.ContainerRoot;
import org.kevoree.DeployUnit;
import org.kevoree.NodeType;
import org.kevoree.cpp.preprocessor.lexer.Lexer;
import org.kevoree.cpp.preprocessor.lexer.Token;
import org.kevoree.impl.DefaultKevoreeFactory;
import org.kevoree.library.cpp.mavenplugin.utils.PluginHelper;
import org.kevoree.modeling.api.json.JSONModelSerializer;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
/**
 * @author jedartois
 * @author <a href="mailto:jedartois@gmail.com">Jean-Emile DARTOIS</a>
 * @version $Id$
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
    @Override
    public void execute() throws MojoExecutionException, MojoFailureException {

        if (inputCFile == null || !(inputCFile.exists())) {
            getLog().warn("InputDir null => ");
        } else {
            DefaultKevoreeFactory factory = new DefaultKevoreeFactory();
            JSONModelSerializer serializer = new JSONModelSerializer();

            ContainerRoot root=factory.createContainerRoot();
            List<File> types = new ArrayList<File>();
            PluginHelper.scanForHeader(inputCFile,types);
            for (File f : types) {

                try {
                    Lexer te = new Lexer(new FileInputStream(f));
                    Token token =   te.nextToken();

                    while(  token.getType() != Token.TokenType.END_OF_FILE  ){

                        if(token.getType() == Token.TokenType.NodeType)
                        {
                            getLog().info("NodeType found =>" +token);

                            DeployUnit du =factory.createDeployUnit();

                            du.setName(token.getValue());
                            du.setGroupName(project.getGroupId());
                            du.setVersion(project.getVersion());
                            du.setType("so");


                            NodeType nodeType =factory.createNodeType();
                            nodeType.setName(token.getValue());
                            nodeType.setDeployUnit(du);
                            nodeType.setAbstract(false);
                            root.addDeployUnits(du);

                            root.addTypeDefinitions(nodeType);


                        }else    if(token.getType() == Token.TokenType.ComponentType){


                        }

                        token =   te.nextToken();
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }

            try
            {
                String model = serializer.serialize(root);
                getLog().warn("Model Json => "+model);
                PluginHelper.writeFile(inputCFile.getPath()+File.separator+"lib.json",model);
            } catch (IOException e) {
                e.printStackTrace();
            }

            PluginHelper.run("cmake",".");
            PluginHelper.run("make");
       //     PluginHelper.run("make");

        }
    }
}
