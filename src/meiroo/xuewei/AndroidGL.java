package meiroo.xuewei;

import java.nio.IntBuffer;
import javax.microedition.khronos.opengles.GL10;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.opengl.GLUtils;
import android.util.Log;

public class AndroidGL
{
	public static int[] GenerateTexture(GL10 gl,int sum, Bitmap[] bitmaps)
	{
		int[] texture;
		int nCount = 0;
		IntBuffer textureBuffer = IntBuffer.allocate(sum);
		gl.glEnable(GL10.GL_TEXTURE_2D);
		gl.glGenTextures(sum, textureBuffer);
		texture = textureBuffer.array();
		for (int i = 0; i < sum; i++) {
			gl.glBindTexture(GL10.GL_TEXTURE_2D, texture[nCount]);
			gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MAG_FILTER,
					GL10.GL_LINEAR);
			gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER,
					GL10.GL_LINEAR);
			Bitmap bitmap = bitmaps[i];
			GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, bitmap, 0);

			Log.i("render1",
					"texutreID=" + texture[nCount] + "  width=" + bitmap.getWidth()
							+ "   height=" + bitmap.getHeight());
			nCount++;
			bitmap.recycle();
		}
		textureBuffer.clear();
		return texture;
	}
}