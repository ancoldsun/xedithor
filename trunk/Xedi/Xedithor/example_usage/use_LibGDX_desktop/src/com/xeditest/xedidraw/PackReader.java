package com.xeditest.xedidraw;

import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

import javax.imageio.ImageIO;

public class PackReader {

	private static File m_fileToRead;
	private static BufferedImage m_image;
	private static InputStream m_inpuStreamImg;
	private static byte [] m_pngByteArray;
	private static int [] m_sprIntArray;
	
	public static int[][] m_modules;
	public static FrameDesc[] m_frames;
	public static AnimDesc[] m_anims;
	
	
	public PackReader(String string) {
		File fileToRead = new File(string);
		m_fileToRead = fileToRead;
	}
	
	public static BufferedImage getSpriteImage(){
		return m_image;
	}
	
	public static byte [] getSpriteBytes(){
		return m_pngByteArray;
	}
	
	public static int [] getSprIntDesc(){
		return m_sprIntArray;
	}
	
	public static InputStream getInputStreamPNG(){
		return m_inpuStreamImg;
	}

	public static void ReadSprite() throws IOException {
		
		InputStream is = new FileInputStream(m_fileToRead);
		
		long length = m_fileToRead.length();
		byte[] bytes = new byte[(int)length];
		
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
		
		System.out.println("enter.. getBytesFromFile");
	
		//PNG size is in 4 first byte.
		int positionRead=0;
		int sizePNG = read32(bytes,0);
		m_pngByteArray = new byte[sizePNG];
		
		//copy PNG
		for(int i=0;i<sizePNG;i++){
			m_pngByteArray[i] = bytes[i+4];
		}
		
		//begin read byte in this pos
		positionRead = sizePNG;	
		int lengthInt = (bytes.length-sizePNG)/4;
		m_sprIntArray =new int[lengthInt];

		for(int i=0;i<lengthInt;i++)
		{
			m_sprIntArray[i]     = read32(bytes,positionRead);         //
			positionRead +=4;   								//int is 4 byte
		}
		// parse other data
		//parseToSprite(m_sprIntArray);

	}
	
	private static int read32(byte[] bytes,int offset){
		
		int value = 0;
		value     += (bytes[offset] & 0x000000FF)   << 24;
		value     += (bytes[offset+1] & 0x000000FF) << 16;
		value     += (bytes[offset+2] & 0x000000FF) << 8;
		value     += (bytes[offset+3] & 0x000000FF) << 0;
		
		return value;
	}
	
	private static void parseToSprite(int[] a32Sprite){
		
		int i=0;
		while(i<a32Sprite.length){
			if(a32Sprite[i] == 0xEFFE0EEF){  // MODULE
				//System.out.println(" module part");
				int nModule = a32Sprite[++i];
				m_modules = new int [nModule][5];
				//System.out.println("-- n Module: "+ nModule);
				
				for(int j=0;j<nModule;j++){
					for(int k=0;k<5;k++){   // 5 = n column table modules in xedithor
						//System.out.print("  "+a32Sprite[++i]);
						m_modules[j][k] = a32Sprite[++i];
					}
					//System.out.println("");
				}
				i++;
			}
			if(a32Sprite[i] == 0xFFFA0EFF){ // FRAME
				//System.out.println(" frame part");
				int nFrame = a32Sprite[++i];
				//System.out.println("-- n Frame: "+ nFrame);
				
				m_frames= new FrameDesc[nFrame];
				
				for(int j=0;j<nFrame;j++){
					int nModid =a32Sprite[++i];
					int nModInFrame = a32Sprite[++i];
					
					m_frames[j] = new FrameDesc(nModInFrame,nModid);

					for(int k=0;k<nModInFrame;k++){
						System.out.print("module N: "+k);
						for(int l=0;l<5;l++){   // 5 = n column table frame desc in xedithor
							m_frames[j].m_modules[k][l] = a32Sprite[++i];
						}
					}
				}
				i++;
			}
			if(a32Sprite[i] == 0xEEEA0EFF){  // ANIMATION
				//System.out.println(" anim part");
				int nAnim = a32Sprite[++i];
				//System.out.println("-- n Anim: "+ nAnim);
				
				m_anims = new AnimDesc[nAnim];
				for(int j=0;j<nAnim;j++){
					System.out.print("--  AnimID       :"+a32Sprite[++i]);
					int nFrameAnim  = a32Sprite[++i];
					//System.out.print("--  nFrameInAnim :"+nFrameAnim);
					
					m_anims[j] = new AnimDesc(nFrameAnim);

					for(int k=0;k<nFrameAnim;k++){
						//System.out.print("frame N: "+k);
						for(int l=0;l<5;l++){   // 5 = n column table anim desc in xedithor
							//System.out.print("  "+a32Sprite[++i]);
							m_anims[j].m_frames[k][l] = a32Sprite[++i];
						}
						//System.out.println("");
					}
					//System.out.println("");
				}
				i++;				
			}
			i++;
		}
	}	
}

