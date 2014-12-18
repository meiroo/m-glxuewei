package meiroo.xuewei;

import android.content.res.AssetManager;
import android.util.Log;


import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;


/** Utils functions. */
public class Utils {
	public static boolean  glCorrectTimeFinished  = false ;

public static void CopyAssets(AssetManager assetManager,String sdcardPath,String folderName) {
	    
		String[] files = null; 
	    try {
	        files = assetManager.list("");
	    } catch (IOException e) {
	        Log.e("tag", e.getMessage());
	    }
	    File f = new File(sdcardPath+"/"+folderName);
	    if (f.isFile()) {
	    	throw new RuntimeException("Folder "+sdcardPath+"/"+folderName+" is a file");
	    } else if (!f.isDirectory()){
	    	f.mkdir();
	    }
	    
	    for(String filename : files) {
	        InputStream in = null;
	        OutputStream out = null;
	        try {
	          in = assetManager.open(filename);
	          
	          f = new File(sdcardPath+"/"+folderName+"/" + filename);
	          if (f.exists()){
	        	  Log.i("gamekit", "fileexists!");
	        	  continue;
	          }
	          
	          out = new FileOutputStream( sdcardPath+"/"+folderName+"/" + filename);
	          copyFile(in, out);
	          in.close();
	          in = null;
	          out.flush();
	          out.close();
	          out = null;
	        } catch(Exception e) {
	            Log.e("tag", e.getMessage());
	        }       
	    }
	}
	public static void copyFile(InputStream in, OutputStream out) throws IOException {
	    byte[] buffer = new byte[1024];
	    int read;
	    while((read = in.read(buffer)) != -1){
	      out.write(buffer, 0, read);
	    }
	}
}
