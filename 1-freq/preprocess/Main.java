package proc;

import java.io.IOException;


public class Main 
{
    public static void main(String[] args) throws IOException 
    {        
        if(args.length != 2)            
            System.err.println("Usage : java Main input_file_name output_file_name");
        else
            Preprocess.preprocessFile(args[0], args[1], true);
    }
    
}
