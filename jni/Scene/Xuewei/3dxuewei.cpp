#include "ImageLoader.h"
#include <time.h>
#include "Camera.h"
#include "Node.h"
#include "Mesh3dsNode.h"
#include "PointNode.h"
#include "PanelNode.h"
#include "RectNode.h"
#include "xueweiLoader.h"
#include "3dxuewei.h"
#include "OpenGLTexture.h"
#include "OpenGLRender.h"
#include "OpenGLBuffer.h"
#include "Window.h"
#include "Scene.h"
#include "FreeTypeLoader.h"
#include "AnimeLinear.h"
#include "3dXueweiLogic.h"
#include "LineNode.h"
#include "CubeNode.h"

void C3DXueWei::Init()
{
	point4f color = point4f(0.125,0.1875,0.2734,1);
	Render->SetBackColor(color);


	//test for 3ds animation
	//ManNode = new CMesh3dsNode("man.3DS",false,false,true);	
	//ManNode->Position = point3f(0.75,0,0);
	//ManNode->RotationEular = point3f(0,180,0);

	//ManNode = new CMesh3dsNode("man.3DS");
	//ManNode->Mesh.SaveMGLMeshFile("man.mglmesh");
	ManNode = new CNode();
	ManNode->Mesh.LoadMGLMeshFile("man.mglmesh");
	ManNode->Mesh.MeshBuffers[0]->SetVBOType(EVT_STATIC,EVT_STATIC,EVT_NEVER,EVT_STATIC);
	
	ManNode->Scale = point3f(3,3,3);	
	//ManNode->SetDefaultColor(point4f(0,0,0,1));
	//ManNode->BlendOpen = true;
	//ManNode->SrcBlendType = EBF_ONE;
	//ManNode->DstBlendType = EBF_ONE_MINUS_SRC_ALPHA;

	
	//XueWeiPoints = new CPointNode(500);
	XueWeiRects = new CRectNode(XUEWEI_NUM);
	XueWeiRects->SetTexture(0,XueWeiLoader->GetJingluoColorTex());
	XueWeiRects->Mesh.MeshBuffers[0]->SetVBOType(EVT_STATIC,EVT_STATIC,EVT_NEVER,EVT_STATIC);
	XueWeiLines = new CLineNode(XUEWEI_NUM);
	//XueWeiRects->SetDrawScope(0,11);
	//XueWeiRects->SetTexture(new COpenGLTexture("trans.jpg"));
	XueweiNamePanel = NULL;
	XueweiNamePanel = new CPanelNode(1,1,0.4,0.2);
	XueweiNamePanel->DisableViewMatrix = true;
	XueweiNamePanel->SetVisible(false);
	XueweiNamePanel->BlendOpen = true;
	XueweiNamePanel->SrcBlendType = EBF_SRC_ALPHA;
	XueweiNamePanel->DstBlendType = EBF_ONE_MINUS_SRC_ALPHA;
	

	XueweiDescript = new CPanelNode(1,3,2,0.12,point3f(0,-0.5,0));
	XueweiDescript->DisableViewMatrix = true;
	XueweiDescript->BlendOpen = true;
	XueweiDescript->SrcBlendType = EBF_SRC_ALPHA;
	XueweiDescript->DstBlendType = EBF_ONE_MINUS_SRC_ALPHA;
	XueweiDescript->SetDefaultColor(point4f(1,1,1,1));
	XueweiDescript->SetVisible(false);

	ReadMe = new CPanelNode(1,1,1.8,0.9,point3f(0,0,0));
	ReadMe->DisableViewMatrix = true;
	ReadMe->BlendOpen = true;
	ReadMe->SrcBlendType = EBF_SRC_ALPHA;
	ReadMe->DstBlendType = EBF_ZERO;
	ReadMe->SetDefaultColor(point4f(0.8,0.8,0.8,1));
	ReadMe->SetVisible(false);



	XueWeiLoader = new CXueWeiLoader();
	XueWeiLoader->Load(XueWeiRects,XueWeiLines);
	XueWeiRects->Scale = point3f(3,3,3);
	XueWeiRects->BlendOpen = true;
	XueWeiRects->SrcBlendType = EBF_ONE;
	XueWeiRects->DstBlendType = EBF_ONE_MINUS_SRC_ALPHA;

	XueWeiLines->Scale = point3f(3,3,3);

	XueWeiMarker = new CNode();
	XueWeiMarker->Mesh.AddMeshBuffer(XueWeiRects->GetCopyMesh()->MeshBuffers[0]);
	XueWeiMarker->Scale = point3f(0.005,0.005,0.005);
	//XueWeiMarker->RotationEular = point3f(0,0,0);
	
	XueWeiMarker->BlendOpen = true;
	XueWeiMarker->SrcBlendType = EBF_SRC_ALPHA;
	XueWeiMarker->DstBlendType = EBF_ONE;
	XueWeiMarker->SetDefaultColor(point4f(1,1,1,1));
	XueWeiMarker->SetVisible(false);

	Logic = new XueweiLogic(this,ManNode,XueWeiLines);

	OperatePanel = new CPanelNode(2,1,0.25,0.125,point3f(-0.5,-0.8,0));
	Logic->OperatePanelInit((CPanelNode*)OperatePanel);

	JingLuoPanel = new CPanelNode(1,13,0.3,0.15,point3f(0.8,0,0));
	Logic->JingLuoPanelInit((CPanelNode*)JingLuoPanel,XueWeiLoader);

	JingLuoSwitch = new CPanelNode(1,1,0.3,0.15,point3f(0.8,0,0));
	Logic->JingLuoSwitchInit((CPanelNode*)JingLuoSwitch);

	Logic->ReadMePanelInit((CPanelNode*)ReadMe);


	Camera = new CCamera(5);
	Camera->Position = point3f(0,0,-50);
	Camera->FixProjection = true;
	Render->SetCamera(Camera);

	Anime = new CAnimeLinear(1000,1);
	Anime->AddPoint(new AnimePoint<point3f>(&RelativeRotate,point3f(0,0,0),point3f(0,180,0)));
	Anime->Start();

	XueWeiMarkerAnime = new CAnimeLinear(1000,100000000);
	//XueWeiMarkerAnime->AddPoint(new AnimePoint<point3f>(&XueWeiMarker->Scale,point3f(0.01,0.01,0.01),point3f(0.005,0.005,0.005)));
	XueWeiMarkerAnime->AddPoint(new AnimePoint<point3f>(&XueWeiMarker->RotationEular,point3f(0,0,0),point3f(0,0,360)));
	XueWeiMarkerAnime->Start();

	Draging = false;

	ManNode->DrawMode = EDM_TRIANGLES;
	XueWeiLines->SetVisible(false);
	MouseEventType = GESTURE;

}

void C3DXueWei::Display()
{
	Anime->OnAnime();
	Render->SetCamera(Camera);

	Render->LightOn(true);	
	Render->DrawNode(ManNode);
	Render->DrawNode(XueWeiRects);



	Render->LightOn(false);
	Render->DrawNode(XueWeiLines);

	Render->SetZWrite(true,false);
	Render->DrawNode(XueWeiMarker);	
	Render->SetZWrite(false,false);

	Render->DrawNode(OperatePanel);
	Render->DrawNode(JingLuoPanel);
	Render->DrawNode(JingLuoSwitch);
	Render->DrawNode(XueweiNamePanel);
	Render->DrawNode(XueweiDescript);
	Render->DrawNode(ReadMe);

	Render->SetZWrite(true,true);
}

void C3DXueWei::KeyboardEvent(unsigned char key , int x , int y)
{
	XueweiNamePanel->SetVisible(false);
	XueweiDescript->SetVisible(false);

	unsigned char* checkImage;
	switch (key) {
		case KEY_SPACE:
			//Anime->ReStart();
			ReadMe->SetVisible(!ReadMe->Visible);
			break;
		default:
			break;
	}
	//Camera->KeyboardEvent(key,x,y);
	Window->update();
}

void C3DXueWei::Show3DXueWeiName(int id, int x, int y)
{
	float widthHalf = Render->Width/2.0;
	float heightHalf = Render->Height/2.0;
	//XueweiNamePanel = new CPanelNode(1,1,0.25);
	XueweiNamePanel->Position = point3f((x-widthHalf)/widthHalf,(heightHalf-y)/heightHalf-0.1,0);
	XueweiNamePanel->Scale = point3f(1,0.5,1);
	

	delete XueweiNamePanel->GetTexture(0);
	delete XueweiDescript->GetTexture(0);
	delete XueweiDescript->GetTexture(1);
	delete XueweiDescript->GetTexture(2);
	CFreeTypeLoader loader;
	wchar_t str[10] = {0};
	MString::Utf8ToUnicode(str,10,XueWeiLoader->xuewei[id].xuewei_cname,strlen(XueWeiLoader->xuewei[id].xuewei_cname));
	XueweiNamePanel->SetTexture(0,loader.LoadStrImageFromFont("lanting.ttf",(unsigned short*)str,32));
	XueweiNamePanel->SetVisible(true);

	unsigned short str2[60] = {0};
	loader.StrMinRect.X = 640;
	int length = MString::Utf8ToUnicode(str2,60,XueWeiLoader->xuewei[id].shiyi,strlen(XueWeiLoader->xuewei[id].shiyi));
	XueweiDescript->SetTexture(0,loader.LoadStrImageFromFont("lanting.ttf",(unsigned short*)str2,32,640));
	memset(str2,0,sizeof(unsigned short)*60);
	MString::Utf8ToUnicode(str2,60,XueWeiLoader->xuewei[id].gongneng,strlen(XueWeiLoader->xuewei[id].gongneng));
	XueweiDescript->SetTexture(1,loader.LoadStrImageFromFont("lanting.ttf",(unsigned short*)str2,32,640));
	memset(str2,0,sizeof(unsigned short)*60);
	MString::Utf8ToUnicode(str2,60,XueWeiLoader->xuewei[id].weizhi,strlen(XueWeiLoader->xuewei[id].weizhi));
	XueweiDescript->SetTexture(2,loader.LoadStrImageFromFont("lanting.ttf",(unsigned short*)str2,32,640));
	XueweiDescript->SetVisible(true);

	point3f collPos = point3f(XueWeiLoader->xuewei[id].world_x,XueWeiLoader->xuewei[id].world_y,XueWeiLoader->xuewei[id].world_z);
	XueWeiMarker->Position = collPos*3;
	XueWeiMarker->RotationEular = point3f(XueWeiLoader->xuewei[id].jiaodu_x,XueWeiLoader->xuewei[id].jiaodu_y,0);
	XueWeiMarker->SetDefaultColor(point4f(1,1,1,0.2));
	XueWeiMarker->SetVisible(true);
	XueWeiMarkerAnime->ReSet();
	XueWeiMarkerAnime->ReStart();
}
int C3DXueWei::CheckXueweiSelected(int x,int y)
{
	point3f pos;
	bool collied = Logic->GetCollisionManPos(x,y,pos);
	if(!collied)
		return -1;	
	mat4f nodeMatrix;
	CRender::MakeModelMatrix(ManNode, nodeMatrix);

	point3f nodepos = nodeMatrix.multiplyWith1x4Matrix(pos);
	int index = XueWeiRects->GetCollisionIndex(nodepos);
	return index;
}

void C3DXueWei::MouseEvent(int button, int state, int x, int y)
{
	point3f p3 = Render->get3DPositionFromScreenXY(point2f(x,y),RelativePos.Z);

	//LOGI("Mouse Status: %d",state);

	// 按下并拖拽
	if((LastEventButton ==MOUSE_LBUTTON_DOWN && button == MOUSE_MOVE) || 
		(LastEventButton ==TOUCH_DOWN &&( button == TOUCH_MOVE || button == TOUCH_SCALEDOWN || button == TOUCH_SCALEUP))){
		Draging = true;
	}

	// 拖拽结束
	if((button == MOUSE_LBUTTON_UP || button == TOUCH_UP) && Draging == true){
		CurrentVect = CurrentVect+MovePoint-StartPoint;
		Draging = false;
	}

	// 按下
	int index = -1;
	static int lastIndex = 0;
	if(button == MOUSE_LBUTTON_DOWN )
	{
		XueweiNamePanel->SetVisible(false);
		XueweiDescript->SetVisible(false);
		ReadMe->SetVisible(false);
		StartPoint = p3;


	}else if(button == MOUSE_LBUTTON_UP)
	{
		while(true)
		{
			int ret = Logic->CheckOperatePanelSelected((CPanelNode*)OperatePanel,index,lastIndex,x,y);
			if(ret != -1)
			{
				MouseEventType = Logic->OperatePanelIndex;
				break;
			}

			ret  = CheckXueweiSelected(x,y);
			if(ret!=-1)
			{
				XueWeiMarker->SetVisible(true);
				Show3DXueWeiName(ret,x,y);
				break;
			}

			ret = Logic->CheckPanelSelected((CPanelNode*)JingLuoSwitch,x,y);
			if(ret != -1)
			{
				JingLuoPanel->SetVisible(true);
				JingLuoSwitch->SetVisible(false);
				break;
			}

			ret = Logic->CheckPanelSelected((CPanelNode*)JingLuoPanel,x,y);
			if(ret != -1)
			{
				JingLuoPanel->SetVisible(false);
				JingLuoSwitch->SetVisible(true);
				if(ret == 0)
				{
					XueWeiRects->SetDrawScope(0,0);
					XueWeiLines->SetDrawScope(0,0);
				}
				else
				{
					int jstart = XueWeiLoader->jingluo[ret-1].jingluo_start;
					int jcount = XueWeiLoader->jingluo[ret-1].jingluo_count;
					int jid = ret-1;
					XueWeiRects->SetDrawScope(jstart,jcount);
					XueWeiLines->SetDrawScope(jstart-jid,jcount-1);
				}
				XueWeiMarker->SetVisible(false);
				break;
			}

			break;


		}
		
			

	}else if(button == TOUCH_DOWN)
	{
		StartPoint = p3;
	}


	if(Draging){
		MovePoint = p3;
		point3f destVect = MovePoint-StartPoint;
		StartPoint = MovePoint;
		switch(MouseEventType)
		{
		case TRANSLATION:
			RelativePos = RelativePos + destVect;
			break;
		case ROTATE:
			RelativeRotate.Y += destVect.X*-4;
			RelativeRotate.X += destVect.Y*4;
			break;
		case SCALE:
			RelativeScale = RelativeScale*(1+destVect.Y*0.1);
			Render->SetLineWidth(1+RelativeScale.X/2);
			Render->SetPointSize(1+RelativeScale.X/2);
			break;
		case GESTURE:
			if(button == TOUCH_MOVE)
			{
				RelativePos = RelativePos + destVect;
			}else if(button == TOUCH_SCALEDOWN)
			{
				RelativeScale = RelativeScale-RelativeScale*0.1;
			}else if(button == TOUCH_SCALEUP)
			{
				RelativeScale = RelativeScale+RelativeScale*0.1;
			}else if(button == MOUSE_MOVE)
			{
				RelativeRotate.Y += destVect.X*-4;
				RelativeRotate.X += destVect.Y*4;
			}
			break;

		}

		//Lines->AddElement(0,LastPoint,MovePoint,0);
		//LastPoint = MovePoint;
	}

	//////////////////////////////////////////////////////////////////////////
	if(MOUSE_WHEEL == button){
		XueweiNamePanel->SetVisible(false);
		XueweiDescript->SetVisible(false);
		RelativeScale = RelativeScale+RelativeScale*state/1200.0;
		Render->SetLineWidth(1+RelativeScale.X/2);
		Render->SetPointSize(1+RelativeScale.X/2);
	}
	LastEventButton = button;
}

void C3DXueWei::Unload()
{
	delete ManNode;ManNode = NULL;
	delete XueWeiLoader; XueWeiLoader = NULL;
	delete XueWeiRects; XueWeiRects = NULL;
	delete XueWeiLines; XueWeiLines = NULL;
	delete XueweiNamePanel; XueweiNamePanel = NULL;
	delete XueweiDescript; XueweiDescript = NULL;
	//delete XueWeiMarker; XueWeiMarker = NULL;
	delete XueWeiMarkerAnime; XueWeiMarkerAnime = NULL;
	delete Anime; Anime = NULL;
	delete Logic; Logic = NULL;
	delete OperatePanel; OperatePanel = NULL;
	delete JingLuoPanel; JingLuoPanel = NULL;

}