package org.kevoree.library.cpp.mavenplugin.utils;

/**
 * Created by jed on 09/07/14.
 */
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import org.apache.commons.exec.CommandLine;
import org.apache.commons.exec.DefaultExecutor;
import org.apache.commons.exec.PumpStreamHandler;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.MojoFailureException;


public class MavenDeployer {
    private static final String MVN_DEPLOY = "mvn deploy:deploy-file "
            + "-DartifactId=${artifactId} -DgroupId=${groupId} -Dversion=${version} "
            + "-Dfile=${artifactPath} -Durl=${repositoryUrl} -Dpackaging=${packaging} -DrepositoryId=${repositoryId}";

    private String repositoryId;
    private String repositoryUrl;


    public MavenDeployer(final String repositoryId, final String repositoryUrl) {
        this.repositoryId = repositoryId;
        this.repositoryUrl = repositoryUrl;
    }

    public void deploy(final String groupId, final String artifactId, final String version, final String artifactPath,final String packaging) throws IOException, MojoFailureException, MojoExecutionException {


        final Map<String,String> params = new HashMap<String, String>();

        params.put("artifactId", artifactId);
        params.put("groupId", groupId);
        params.put("version", version);
        params.put("artifactPath", artifactPath);
        params.put("repositoryUrl", repositoryUrl);
        params.put("repositoryId", repositoryId);
        params.put("packaging", packaging);

        final CommandLine deployCmd = CommandLine.parse(MVN_DEPLOY);
        deployCmd.setSubstitutionMap(params);
        final DefaultExecutor executor = new DefaultExecutor();
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        PumpStreamHandler streamHandler = new PumpStreamHandler(outputStream);
        executor.setStreamHandler(streamHandler);
        executor.execute(deployCmd);
        if(!outputStream.toString().contains("SUCCESS")){
            System.err.println(outputStream.toString());
        }


    }
}