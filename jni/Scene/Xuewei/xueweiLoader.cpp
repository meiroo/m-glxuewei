#include "xueweiLoader.h"
#include "RectNode.h"
#include "stdio.h"
#include "stdlib.h"
#include "LineNode.h"
#include "OpenGLTexture.h"
#include "OpenGL2Texture.h"
#include "RawImage.h"

CXueWeiLoader::~CXueWeiLoader()
{
	delete[] xuewei;
	delete[] jingluo;
}
point4f CXueWeiLoader::GetJingluoColor(int jingluo_id)
{
	switch(jingluo_id)
	{
	case 1:
		return point4f(0.8,0.8,0.8,1.0);
	case 2:
		return point4f(0.12549020,0.18823530,0.27450982,1);
	case 3:
		return point4f(1.0,1.0,0.0,1.0);
	case 4:
		return point4f(0.7,0.7,0.3,1.0);
	case 5:
		return point4f(1.0,0.5,0.5,1.0);
	case 6:
		return point4f(1.0,0.0,0.0,1.0);
	case 7:
		return point4f(0.1,0.1,0.1,1.0);
	case 8:
		return point4f(0.3,0.0,0.3,1.0);
	case 9:
		return point4f(0.4,0.8,0.4,1.0);
	case 10:
		return point4f(0.0,1.0,0.0,1.0);
	case 11:
		return point4f(0.0,1.0,1.0,1.0);
	case 12:
		return point4f(0.4,0.4,0.8,1.0);
	case 13:
		return point4f(1.0,1.0,1.0,1.0);
	case 14:
		return point4f(1.0,1.0,1.0,1.0);
	}
}

void CXueWeiLoader::SetJingluo(XUEWEI& xuewei)
{
	int jingluo_id = xuewei.jingluo_id;

	if(jingluo[jingluo_id-1].jingluo_id == -1)
	{
		jingluo[jingluo_id-1].jingluo_id = jingluo_id;
		jingluo[jingluo_id-1].jingluo_cname = xuewei.jingluo_cname;
		jingluo[jingluo_id-1].jingluo_start = xuewei.xuewei_id-1;
		jingluo[jingluo_id-1].jingluo_color = GetJingluoColor(jingluo_id);
	}
	jingluo[jingluo_id-1].jingluo_count ++;	
}

bool CXueWeiLoader::Load(CRectNode* Rects, CLineNode* Lines)
{
	xuewei = new XUEWEI[400];
	jingluo = new JINGLUO[20];

	FILE *fp;	

	MString ms;
#if 1
	fp = fopen(ms.str_join(g_Engine->MediaPath,XUEWEI_FILE_NAME),"r");

	for (int n=0;n<XUEWEI_NUM;n++)
	{	
		fscanf(fp,"%f %f %f %f %f %f %f %f %d %s %s %d %s %s %s %s"
			,&xuewei[n].world_x,&xuewei[n].world_y,&xuewei[n].world_z
			,&xuewei[n].mx,&xuewei[n].my,&xuewei[n].dx
			,&xuewei[n].jiaodu_x,&xuewei[n].jiaodu_y,&xuewei[n].xuewei_id
			,&xuewei[n].xuewei_ename,&xuewei[n].xuewei_cname,&xuewei[n].jingluo_id
			,&xuewei[n].jingluo_cname,&xuewei[n].shiyi,&xuewei[n].gongneng,&xuewei[n].weizhi);	
		
		//special process for 13 14
		if(xuewei[n].xuewei_id >= 310)
		{
			xuewei[n].world_x/=3.0;xuewei[n].world_y/=3.0;xuewei[n].world_z/=3.0;
		}

		SetJingluo(xuewei[n]);
		point4f color = GetJingluoColor(xuewei[n].jingluo_id);

		Rects->addTransformedElement(point3f(xuewei[n].world_x,xuewei[n].world_y,xuewei[n].world_z),
			point3f(xuewei[n].jiaodu_x,xuewei[n].jiaodu_y/*+180*/,0),point3f(0.02,0.02,0.02),color,xuewei[n].jingluo_id);

		if(Lines && n>0 && xuewei[n].jingluo_id == xuewei[n-1].jingluo_id)
		{
			Lines->AddElement(0,point3f(xuewei[n-1].world_x,xuewei[n-1].world_y,xuewei[n-1].world_z),point3f(xuewei[n].world_x,xuewei[n].world_y,xuewei[n].world_z),0,color);
		}

		//Rects->AddElement(0,point3f(xuewei[n].world_x,xuewei[n].world_y,xuewei[n].world_z),
		//	point3f(0,0,0),point3f(0.2,0.2,0.2),0);
	}
	fclose(fp);
#else
	fp = _wfopen(L"./xwsj.lj",L"r,ccs=UTF-8");
	for (int n=0;n<XUEWEI_NUM;n++)
	{	
		fwscanf(fp,L"%f %f %f %f %f %f %f %f %d %s %s %d %s %s %s %s"
			,&xuewei[n].world_x,&xuewei[n].world_y,&xuewei[n].world_z
			,&xuewei[n].mx,&xuewei[n].my,&xuewei[n].dx
			,&xuewei[n].jiaodu_x,&xuewei[n].jiaodu_y,&xuewei[n].xuewei_id
			,&xuewei[n].xuewei_ename,&xuewei[n].xuewei_cname,&xuewei[n].jingluo_id
			,&xuewei[n].jingluo_cname,&xuewei[n].shiyi,&xuewei[n].gongneng,&xuewei[n].weizhi);	
		//Rects->AddElement(0,point3f(xuewei[n].world_x,xuewei[n].world_y,xuewei[n].world_z),0);
		SetJingluo(xuewei[n]);
		point4f color = GetJingluoColor(xuewei[n].jingluo_id);

		Rects->addTransformedElement(point3f(xuewei[n].world_x,xuewei[n].world_y,xuewei[n].world_z),
			point3f(xuewei[n].jiaodu_x,xuewei[n].jiaodu_y/*+180*/,0),point3f(0.02,0.02,0.02),color,0);

		//Rects->AddElement(0,point3f(xuewei[n].world_x,xuewei[n].world_y,xuewei[n].world_z),
		//	point3f(0,0,0),point3f(0.2,0.2,0.2),0);
	}
	fclose(fp);

#endif
	return true;
}

CTexture* CXueWeiLoader::GetJingluoColorTex()
{
	unsigned char* buffer = new unsigned char[4*12];
	memset(buffer,0,4*12);
	for(int i = 0; i < 12; i++)
	{
		buffer[0 + i*4] = GetJingluoColor(i+1).X*255;
		buffer[1 + i*4] = GetJingluoColor(i+1).Y*255;
		buffer[2 + i*4] = GetJingluoColor(i+1).Z*255;
		buffer[3 + i*4] = GetJingluoColor(i+1).M*255;
	}
	CTexture* tex = new COpenGLTexture(IMAGE_RGBA,12,1,buffer);
	delete[] buffer;
	return tex;

}