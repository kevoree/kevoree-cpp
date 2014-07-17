package org.kevoree.cpp.preprocessor.ast;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by jed on 17/07/14.
 */
public class Statment {

    boolean optional=false;
    boolean fragdep=false;

    private  String name;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
    private List<Param> paramList = new ArrayList<Param>();

    public List<Param> getParamList() {
        return paramList;
    }

    public void AddParamTypeList(Param paramList) {
        this.paramList.add(paramList);
    }

    public String toString(){
        return "" +name+" fragdep="+fragdep+" optional="+optional;
    }

    public boolean isFragdep() {
        return fragdep;
    }

    public void setFragdep(boolean fragdep) {
        this.fragdep = fragdep;
    }

    public boolean isOptional() {
        return optional;
    }

    public void setOptional(boolean optional) {
        this.optional = optional;
    }
}
