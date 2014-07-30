package org.kevoree.library.cpp.mavenplugin;


import org.kevoree.ContainerRoot;
import org.kevoree.compare.DefaultModelCompare;
import org.kevoree.impl.DefaultKevoreeFactory;
import org.kevoree.loader.JSONModelLoader;
import org.kevoree.modeling.api.compare.ModelCompare;

import java.io.File;
import java.io.FileInputStream;


/**
 * Created by jed on 30/06/14.
 */
public class Main {




    public static void  main(String argv[]) throws Exception {


        DefaultKevoreeFactory factory= new DefaultKevoreeFactory();
        JSONModelLoader loader  = new JSONModelLoader();

       ContainerRoot model = (ContainerRoot)loader.loadModelFromStream(new FileInputStream("/home/jed/KEVOREE_PROJECT/kevoree-cpp/tests/dataTest/kmf/bindings.json")).get(0);

        ContainerRoot model2 = (ContainerRoot)  loader.loadModelFromStream(new FileInputStream("/home/jed/KEVOREE_PROJECT/kevoree-cpp/tests/dataTest/kmf/bindings2.json")).get(0);
        ModelCompare compare = new DefaultModelCompare();



                System.out.println(    compare.diff(model,model2).exportToString());

    }
}
