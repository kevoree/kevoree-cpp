package org.kevoree.cpp.preprocessor.lexer;

/**
 * Created by jed on 30/06/14.
 */


public class Token {

    public enum  TokenType {
        PRAGMA,
        SOURCE,
        NodeType,
        ComponentType,
        Dictionary,
        GroupType,
        END_OF_FILE
    };

    TokenType type;
    String id;
    String value;


    public TokenType getType() {
        return type;
    }

    public void setType(TokenType type) {
        this.type = type;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }
    public String toString(){
        return type+" "+ id+" "+value;
    }
}
