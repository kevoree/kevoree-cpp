package org.kevoree.cpp.preprocessor.lexer;

import org.kevoree.cpp.preprocessor.ast.*;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by jed on 30/06/14.
 */

/* TODO
DICO
optional
datatype
fragmentDependant
defaultValue
 */

public class Lexer {
    byte[]  buffer;
    int index;

    public static byte[] readFully(InputStream input) throws IOException
    {

        byte[] buffer = new byte[8192];
        int bytesRead;
        ByteArrayOutputStream output = new ByteArrayOutputStream();
        while ((bytesRead = input.read(buffer)) != -1)
        {
            output.write(buffer, 0, bytesRead);

        }

        return output.toByteArray();
    }


    public Lexer(InputStream inputStream) throws IOException {
        index=0;
        buffer=  readFully(inputStream);
    }


    boolean isSpace(byte next_char){

        if (next_char == ' ' || next_char == '\t' || next_char == '\n')
        {
            return true;
        }

        return false;
    }
    boolean isPragma() {

        if (buffer[index ] == 'p' && buffer[index + 1] == 'r' && buffer[index + 2] == 'a' && buffer[index + 3] == 'g' && buffer[index + 4] == 'm' && buffer[index + 5] == 'a') {

            index = index + 5;
            return true;
        } else {
            return false;
        }
    }
    public String parseToken(){
        // name
        byte   c;
        String value="";
        do
        {
            c = nextChar();
            value +=(char)c;
        }while (isDone() != true && isSpace(c) != true );
        return value.trim().replace("\"","").toLowerCase();
    }


    public   String  parsedefaultValue(){
        int indice=index;
        byte   c= ' ';
        do {
            String value="";
            do
            {
                c = nextChar();
                value +=(char)c;
            }while (isDone() != true && isSpace(c) != true );

            if(value.toLowerCase().startsWith("defaultvalue")){

                index = indice;
                return value.substring(value.indexOf("=")+1,value.length()).trim().replace("\"","").toLowerCase();
            }

            return "";

        }
        while (isDone() != true &&  c != '#');




    }

    public   List<String>  parseOptions(){
        int indice =index;
        List<String> tokens = new ArrayList<String>();
        byte   c= ' ';
        do {
            String value="";
            do
            {
                c = nextChar();
                value +=(char)c;
            }while (isDone() != true && isSpace(c) != true );
            value = value.trim().replace("\"","").toLowerCase();

                tokens.add(value);


        }
        while (isDone() != true &&  c != '#');



        return tokens;
    }


    public  Statment nextToken(){
        byte   c;

        Statment statment=null;
        if (isDone()) {
            EOF token= new EOF();

            return token;
        }
        c=nextChar();

        while (isDone() != true && isSpace(c)==true && c != '#') {
            c = nextChar();
        }


        if(c == '#'){

            if(isPragma())
            {

                // id
                while (isDone() != true && isSpace(c)!=true ) {
                    c = nextChar();
                }

                String type = parseToken();
                if(type.equals(NodeType.class.getSimpleName().toLowerCase()))
                {
                    statment = new NodeType();
                    statment.setName(parseToken());

                }else  if(type.equals(ComponentType.class.getSimpleName().toLowerCase())){

                    statment = new ComponentType();
                    statment.setName(parseToken());
                }else  if(type.equals(ChannelType.class.getSimpleName().toLowerCase())){
                    statment  = new ChannelType();
                    statment.setName(parseToken());

                }else  if(type.equals(GroupType.class.getSimpleName().toLowerCase())){
                    statment  = new GroupType();
                    statment.setName(parseToken());
                } else if(type.equals(Param.class.getSimpleName().toLowerCase())){
                    statment  = new Param();
                    statment.setName(parseToken());

                    String defaultvalue = parsedefaultValue();
                    List<String> options =parseOptions();
                    if(defaultvalue.length() > 0){
                        ((Param)statment).setDefaultValue(defaultvalue);
                    }
                    if(options.contains("fragdep")){
                        statment.setFragdep(true);
                    }
                    if(options.contains("optional")){
                        statment.setOptional(true);
                    }
                }
                else if(type.equals(Input.class.getSimpleName().toLowerCase())){
                    statment  = new Input();
                    statment.setName(parseToken());





                }else if(type.equals(Provide.class.getSimpleName().toLowerCase())) {
                    statment = new Provide();
                    statment.setName(parseToken());
                }
                else {
                    // no managed
                    System.out.println(type+" ");
                    statment = new Unsupported();
                }

/*
                if(token.getId().toLowerCase().trim().equals(Token.type_strings[0]))
                {
                    token.setType(Token.TokenType.NodeType);
                    parseName(token);
                }else  if(token.getId().toLowerCase().trim().equals(Token.type_strings[1]))
                {
                    token.setType(Token.TokenType.GroupType);
                    parseName(token);
                }else  if(token.getId().toLowerCase().trim().equals(Token.type_strings[2])){
                    token.setType(Token.TokenType.ComponentType);
                    parseName(token);
                }else  if(token.getId().toLowerCase().trim().equals(Token.type_strings[3]))
                {
                    token.setType(Token.TokenType.Param);
                    parseName(token);

                    parsedefaultValue(token);


                }else

                {
                    token.setType(Token.TokenType.PRAGMA);
                }*/


            }
            else
            {
                // next
                statment = new Unsupported();
            }


        }else {
            statment = new Unsupported();
        }



        return statment;
    }

    private byte nextChar() {
        return buffer[index++];
    }

    public boolean isDone() {

        return 	  index >= buffer.length;
    }
}
