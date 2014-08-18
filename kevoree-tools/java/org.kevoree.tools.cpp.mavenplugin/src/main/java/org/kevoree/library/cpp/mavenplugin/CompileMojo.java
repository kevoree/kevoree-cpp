package org.kevoree.library.cpp.mavenplugin;

import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.MojoFailureException;
import org.apache.maven.project.MavenProject;
import org.sonatype.aether.util.artifact.ArtifacIdUtils;

/**
 * @author Aymeric Hervieu
 * @goal build-cmake
 */
public class CompileMojo extends AbstractMojo {

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
        getLog().info(project.getArtifactId());
    }

}
