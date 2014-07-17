package org.kevoree.cpp.preprocessor.ast;

import java.util.List;

/**
 * Created by jed on 17/07/14.
 */
public class NodeType extends Statment {

    public String toString(){
        return  this.getClass().getSimpleName()+" "+super.toString();
    }
}
