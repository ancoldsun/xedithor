/*
 * Copyright 2012 Edi Ermawan  < edi.ermawan@gmail.com >
 * 
 */

package com.xdr.lib;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.files.FileHandle;

/*
 *  reader class for binary sprite data
 *  supply png & int[] sprite description
 */
public class XDRPackReader {

	private File m_fileToRead;
	private byte [] m_pngByteArray;
	private int [] m_sprIntArray;
	String m_strFileName;
	private static boolean ANDROID=false;
	
	public XDRPackReader(int idFile) {
		String strFileName;
		if(ANDROID)
			strFileName ="sprites/"+idFile+".bin";
		else
			strFileName ="assets/sprites/"+idFile+".bin";
		m_strFileName = strFileName;
		//File fileToRead = new File(strFileName);
		//m_fileToRead = fileToRead;
		
		
	}
	
	public byte [] getPNGByteArray(){
		return m_pngByteArray;
	}
	
	public int [] getSprIntDesc(){
		return m_sprIntArray;
	}
	/*
	 *  read sprite file, split it in png byte array AND sprite description data
	 *  @param  : -
	 *  @output : png byte array, int array 
	 */
	public void ReadSprite() throws IOException {
		/*
		//InputStream is = new FileInputStream(m_fileToRead);

		InputStream is = Gdx.files.internal(m_strFileName).read();
		
		//long length = m_fileToRead.length();//length();
		byte[] bytes = null;//new byte[(int)length];
		is.read(bytes);

		long length = bytes.length;
		
		
		if (length > Integer.MAX_VALUE) {
	        // File is too large
	    }
		int offset = 0;
	    int numRead = 0;
	    while (offset < bytes.length
	           && (numRead=is.read(bytes, offset, bytes.length-offset)) >= 0) {
	        offset += numRead;
	    }
	    
	    if (offset < bytes.length) {
	        throw new IOException("Could not completely read file "+m_fileToRead.getName());
	    }
	    is.close();	
	    */
		FileHandle handle = Gdx.files.internal(m_strFileName);
		byte[] bytes = handle.readBytes();
		// PNG size is in 4 first byte.
		int positionRead=0;
		int sizePNG = read32(bytes,0);
		m_pngByteArray = new byte[sizePNG];
		
		// copy PNG
		for(int i=0;i<sizePNG;i++){
			m_pngByteArray[i] = bytes[i+4];
		}
		
		// begin read byte in this position
		positionRead = sizePNG;	
		int lengthInt = (bytes.length-sizePNG)/4;
		m_sprIntArray =new int[lengthInt];

		for(int i=0;i<lengthInt;i++)
		{
			m_sprIntArray[i]     = read32(bytes,positionRead); 
			positionRead +=4;   								
		}
	}
	/*
	 *  convert byte array to integer
	 *  @param : byte[] array
	 *  @param : offset
	 *  output : integer
	 */
	private int read32(byte[] bytes,int offset)
	{	
		int value = 0;
		value     += (bytes[offset] & 0x000000FF)   << 24;
		value     += (bytes[offset+1] & 0x000000FF) << 16;
		value     += (bytes[offset+2] & 0x000000FF) << 8;
		value     += (bytes[offset+3] & 0x000000FF) << 0;
		
		return value;
	}
	
}

