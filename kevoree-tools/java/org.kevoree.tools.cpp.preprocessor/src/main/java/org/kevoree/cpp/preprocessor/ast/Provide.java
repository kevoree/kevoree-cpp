package org.kevoree.cpp.preprocessor.ast;

/**
 * Created by jed on 17/07/14.
 */
public class Provide extends Statment {

    public String toString(){
        return  this.getClass().getSimpleName()+" "+super.toString();
    }
}
