package meiroo.xuewei;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.Typeface;

public class AndroidFontTool{
	public static int FontWidth = 300;
	public static int FontHeight = 50;
	public static Bitmap DrawNameOnBitmap(String name) 
	 {
	    Bitmap bmp = null;
	    
	    bmp = Bitmap.createBitmap(FontWidth, FontHeight, Bitmap.Config.ARGB_8888);
	    
	    Canvas canvasTemp = new Canvas(bmp);
	    canvasTemp.drawColor(Color.parseColor("#22222222")); // ��ɫ80%͸��
	    Paint p = new Paint(Paint.ANTI_ALIAS_FLAG);
	    Typeface font = Typeface.create("微软雅黑", Typeface.NORMAL);
	    p.setColor(Color.RED);
	    p.setTypeface(font);
	    p.setTextAlign(Paint.Align.CENTER);
	    p.setTextSize(FontWidth/(float)10);
	    
	    float[] widths = new float[name.length()];
	    int count = p.getTextWidths(name, 0, name.length(), widths);
	    float w = p.measureText(name, 0, name.length());



	    canvasTemp.drawText(name, FontWidth/(float)2.0, FontHeight/(float)5.0*4, p);
	     
	    return bmp;
	 }
	
	public static int ImageWidth = 512;
	public static int ImageHeight = 512;
	public static Bitmap DrawNineBitmaps() 
	 {
		Bitmap bmp = Bitmap.createBitmap(ImageWidth, ImageHeight, Bitmap.Config.ARGB_8888);
		Canvas canvas = new Canvas(bmp);
		canvas.drawColor(Color.parseColor("#ff222222"));
		Paint p = new Paint(Paint.ANTI_ALIAS_FLAG);
		p.setColor(Color.RED);
		
		Bitmap bmp1 = AndroidFontTool.DrawNameOnBitmap("11111");
		Bitmap bmp2 = AndroidFontTool.DrawNameOnBitmap("22222");
		Bitmap bmp3 = AndroidFontTool.DrawNameOnBitmap("33333");
		Bitmap bmp4 = AndroidFontTool.DrawNameOnBitmap("44444");
		Bitmap bmp5 = AndroidFontTool.DrawNameOnBitmap("55555");
		Bitmap bmp6 = AndroidFontTool.DrawNameOnBitmap("66666");
		Bitmap bmp7 = AndroidFontTool.DrawNameOnBitmap("77777");
		Bitmap bmp8 = AndroidFontTool.DrawNameOnBitmap("88888");
		Bitmap bmp9 = AndroidFontTool.DrawNameOnBitmap("99999");
		
		Rect dstRect = new Rect();
		dstRect.set(0, 0, ImageWidth/3, ImageHeight/3);
		canvas.drawBitmap(bmp1, null, dstRect, null);
		dstRect.set(ImageWidth/3, ImageHeight/3, ImageWidth/3*2, ImageHeight/3*2);
		canvas.drawBitmap(bmp2, null, dstRect, null);
		dstRect.set(ImageWidth/3*2, ImageHeight/3*2, ImageWidth, ImageHeight);
		canvas.drawBitmap(bmp3, null, dstRect, null);
		
		return bmp;
	 }
}