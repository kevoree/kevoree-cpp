package org.kevoree.library.cpp.pusher;


import org.java_websocket.client.WebSocketClient;
import org.java_websocket.handshake.ServerHandshake;
import org.kevoree.ContainerRoot;
import org.kevoree.compare.DefaultModelCompare;
import org.kevoree.impl.DefaultKevoreeFactory;
import org.kevoree.library.ws.Protocol;
import org.kevoree.library.ws.WSGroup;
import org.kevoree.loader.JSONModelLoader;
import org.kevoree.log.Log;
import org.kevoree.modeling.api.compare.ModelCompare;
import org.kevoree.modeling.api.json.JSONModelSerializer;

import java.io.File;
import java.io.FileInputStream;
import java.net.URI;
import java.util.concurrent.atomic.AtomicBoolean;


/**
 * Created by jed on 30/06/14.
 */
public class Main {



    public static WebSocketClient createWSClient(String ip, String port) {
        final WebSocketClient[] client = new WebSocketClient[1];
        URI uri = null;
        if (ip.contains(":")) {
            uri = URI.create("ws://[" + ip + "]:" + port);
        } else {
            uri = URI.create("ws://" + ip + ":" + port);
        }
        client[0] = new WebSocketClient(uri) {
            @Override
            public void onOpen(ServerHandshake handshakedata) {
                System.out.println("connected");
            }

            @Override
            public void onMessage(String message) {


            }

            @Override
            public void onClose(int code, String reason, boolean remote) {
            }

            @Override
            public void onError(Exception ex) {
            }
        };

        return client[0];
    }

    public static void  main(String argv[]) throws Exception {


        DefaultKevoreeFactory factory= new DefaultKevoreeFactory();
        JSONModelLoader loader  = new JSONModelLoader();
        JSONModelSerializer jsonModelSaver = new JSONModelSerializer();

       ContainerRoot model = (ContainerRoot)loader.loadModelFromStream(new FileInputStream("/home/jed/KEVOREE_PROJECT/kevoree-cpp/tests/dataTest/kmf/bindings.json")).get(0);

        ContainerRoot model2 = (ContainerRoot)  loader.loadModelFromStream(new FileInputStream("/home/jed/KEVOREE_PROJECT/kevoree-cpp/tests/dataTest/kmf/bindings2.json")).get(0);
        ModelCompare compare = new DefaultModelCompare();


        ContainerRoot model3 = (ContainerRoot)  loader.loadModelFromStream(new FileInputStream("/home/jed/KEVOREE_PROJECT/kevoree-cpp/tests/dataTest/kmf/model_node_empty.json")).get(0);

        ContainerRoot model4 = (ContainerRoot)  loader.loadModelFromStream(new FileInputStream("/home/jed/KEVOREE_PROJECT/kevoree-cpp/tests/dataTest/kmf/onNODE_helloworld_component.json")).get(0);



//                System.out.println(    compare.diff(model,model2).exportToString());

        Protocol.PushMessage pushMessage = new Protocol.PushMessage(jsonModelSaver.serialize(model));
        Protocol.PushMessage pushMessage2 = new Protocol.PushMessage(jsonModelSaver.serialize(model2));
        Protocol.PushMessage pushMessage3 = new Protocol.PushMessage(jsonModelSaver.serialize(model3));
        Protocol.PushMessage pushMessage4 = new Protocol.PushMessage(jsonModelSaver.serialize(model4));


        while(true){
            WebSocketClient client =createWSClient("stratus.irisa.fr","9000");
            client.connectBlocking();

            client.send(pushMessage4.toRaw());
        //    Thread.sleep(200);
           // client.send(pushMessage2.toRaw());
           // System.out.println("UPDATE");

            client.send(pushMessage3.toRaw());
          //  Thread.sleep(200);
            client.close();

        }



    }
}
