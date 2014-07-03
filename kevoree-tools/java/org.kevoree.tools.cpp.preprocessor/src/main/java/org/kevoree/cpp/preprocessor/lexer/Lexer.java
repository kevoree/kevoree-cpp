package org.kevoree.cpp.preprocessor.lexer;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

/**
 * Created by jed on 30/06/14.
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

    public  Token nextToken(){
        byte   c;
        Token token= new Token();
        if (isDone()) {
            token.type = Token.TokenType.END_OF_FILE;
            return token;
        }
        c=nextChar();

        while (isDone() != true && isSpace(c)==true && c != '#') {
            c = nextChar();
        }

        if(c == '#'){

            if(isPragma())
            {

                while (isDone() != true && isSpace(c)!=true ) {
                    c = nextChar();
                }
                String id="";
                do
                {
                    c = nextChar();
                    id +=(char)c;
                }while (isDone() != true && isSpace(c) != true);
                token.setId(id);

                if(id.toLowerCase().trim().equals("nodetype"))
                {
                    token.setType(Token.TokenType.NodeType);
                }else  if(id.toLowerCase().trim().equals("grouptype"))
                {
                    token.setType(Token.TokenType.GroupType);
                }else  if(id.toLowerCase().trim().equals("componenttype")){
                    token.setType(Token.TokenType.ComponentType);
                }else  if(id.toLowerCase().trim().equals("dictionary"))
                {
                    token.setType(Token.TokenType.Dictionary);
                }else

                {
                    token.setType(Token.TokenType.PRAGMA);
                }
                String value="";
                do
                {
                    c = nextChar();
                    value +=(char)c;
                }while (isDone() != true && isSpace(c) != true);
                token.setValue(value.trim());

            }
            else
            {
                // next
                token.setType(Token.TokenType.SOURCE);
            }


        }else {
            token.setType(Token.TokenType.SOURCE);
        }



        return token;
    }

    private byte nextChar() {
        return buffer[index++];
    }

    public boolean isDone() {

        return 	  index >= buffer.length;
    }
}
