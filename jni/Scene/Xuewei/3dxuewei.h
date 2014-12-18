#pragma once
#include "mgltypes.h"
#include "Scene.h"
#include "xueweiLoader.h"

class CAnimeLinear;
class CNode;
class CRectNode;
class CLineNode;
class CCamera;
class XueweiLogic;

class C3DXueWei:public CScene
{
public:
	CNode* ManNode;
	CNode* OperatePanel;
	CNode* XueweiNamePanel;
	CNode* XueweiDescript;
	CNode* JingLuoSwitch;
	CNode* JingLuoPanel;
	CRectNode* XueWeiRects;
	CLineNode* XueWeiLines;
	CNode* XueWeiMarker;
	CNode* ReadMe;
	CCamera* Camera;
	CAnimeLinear* Anime;
	CAnimeLinear* XueWeiMarkerAnime;
	f32 frame3ds;
	u32 FboId;

	point3f StartPoint;
	point3f MovePoint;
	point3f LastPoint;
	point3f CurrentVect;
	bool  Draging;
	int  LastEventButton;
	int MouseEventType;
	CXueWeiLoader* XueWeiLoader;
	XueweiLogic* Logic;


	enum EMOUSE_EVENT_PROCESS
	{
		TRANSLATION = 0,
		ROTATE,
		SCALE,
		GESTURE,
		END0
	};

	C3DXueWei(){}
	void Init();
	void Display();
	void KeyboardEvent(unsigned char key , int x , int y);
	void Show3DXueWeiName(int id, int x, int y);
	int CheckXueweiSelected(int x,int y);
	void MouseEvent(int button, int state, int x, int y);
	void Unload();
};