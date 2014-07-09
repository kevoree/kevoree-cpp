package org.kevoree.library.cpp.mavenplugin.utils;

import org.codehaus.plexus.util.Base64;

import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;

/**
 * Created by jed on 09/07/14.
 */
public class MavenDeployerTest {

//curl -v -u admin:admin123 --upload-file pom.xml http://localhost:8081/nexus/content/repositories/releases/org/foo/1.0/foo-1.0.pom

    public static void main(String argv[]) throws IOException {

        String webPage = "http://maven.reacloud.com/repository/reacloud/snapsho";
        String name = "deploy2015";
        String password = "deploy2015";
        File file = new File("/home/jed/KEVOREE_PROJECT/kevoree-cpp/kevoree-library/HelloWorldComponent/src/main/resources/libhelloworld_component.so");

        String authString = name + ":" + password;
        byte[] authEncBytes = Base64.encodeBase64(authString.getBytes());
        String authStringEnc = new String(authEncBytes);
        URL url = new URL(webPage);
        HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();
        urlConnection = (HttpURLConnection) url.openConnection();
        urlConnection.setRequestProperty("Authorization", "Basic "   + authStringEnc);
        urlConnection.setConnectTimeout(500000);
        urlConnection.setReadTimeout(500000);
        urlConnection.setRequestProperty("Content-Type", "application/octet-stream");
        urlConnection.setRequestProperty("Content-Length", "" + file.length());


        urlConnection.setDoOutput(true);
        urlConnection.setRequestMethod("PUT");
        urlConnection.connect();

        OutputStreamWriter out = new OutputStreamWriter(urlConnection.getOutputStream());

System.out.println("File size "+file.length()+" octets");
        try {
            FileInputStream fis = new FileInputStream(file);
            char current;
            while (fis.available() > 0) {
                current = (char) fis.read();
             //   System.out.println("writing");
                out.write(current);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        out.close();
        InputStream is = urlConnection.getInputStream();
        InputStreamReader isr = new InputStreamReader(is);
        int numCharsRead = 0;
        char[] charArray = new char[1024];
        StringBuffer sb = new StringBuffer();
        while ((numCharsRead = isr.read(charArray)) > 0) {
            sb.append(charArray, 0, numCharsRead);
        }
        String result = sb.toString();
        System.out.println(result);
    }
}
