package org.kevoree.library.cpp.mavenplugin.utils;

import org.apache.maven.plugin.AbstractMojo;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * Mojo helper functions.
 * <p>
 * @author Gili Tzabari
 */
public class Mojos
{
	/**
	 * Launches and waits for a process to complete.
	 * <p>
	 * @param processBuilder the process builder
	 * @return the process exit code
	 * @throws java.io.IOException          if an I/O error occurs while running the process
	 * @throws InterruptedException if the thread was interrupted
	 */
	public static int waitFor(ProcessBuilder processBuilder, AbstractMojo am)
		throws IOException, InterruptedException
	{
		Process process = processBuilder.redirectErrorStream(true).start();
		BufferedReader in = null;
		try
		{
			in = new BufferedReader(new InputStreamReader(process.getInputStream()));
			while (true)
			{
				String line = in.readLine();
				if (line == null)
					break;
                am.getLog().info(line);
			}
		}
		finally
		{
			if (in != null)
				in.close();
		}
		return process.waitFor();
	}

	/**
	 * Prevent construction.
	 */
	private Mojos()
	{
	}
}
