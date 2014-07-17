package org.kevoree.cpp.preprocessor.ast;

/**
 * Created by jed on 17/07/14.
 */
public class Param extends Statment {

    private String defaultValue;
    public String toString(){
        return  this.getClass().getSimpleName()+" "+super.toString()+" defaultValue="+defaultValue;
    }

    public String getDefaultValue() {
        return defaultValue;
    }

    public void setDefaultValue(String defaultValue) {
        this.defaultValue = defaultValue;
    }
}
