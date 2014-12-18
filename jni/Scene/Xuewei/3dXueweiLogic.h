#pragma once
#include "mglTypes.h"
#include "FreeTypeLoader.h"
class CNode;
class CScene;
class CPanelNode;
class CXueWeiLoader;
class CTexture;
class CFreeTypeLoader;

class XueweiLogic
{
public:
	XueweiLogic(CScene* scene,CNode* manNode,CNode* lines);
	int CheckOperatePanelSelected(CPanelNode* panel,int &index,int& lastIndex, int x, int y);
	int CheckPanelSelected(CPanelNode* panel,int x, int y);
	void OperatePanelInit(CPanelNode* panel);
	void JingLuoPanelInit(CPanelNode* panel,CXueWeiLoader* loader);
	void JingLuoSwitchInit(CPanelNode* panel);
	void AddNewXuewei(CNode* marker,int x, int y);
	void ReadMePanelInit(CPanelNode* panel);
	bool GetCollisionManPos(int x, int y, point3f& pos);

	CScene* Scene;
	CRender* Render;
	CNode* ManNode;
	CNode* XueWeiLines;

	CPanelNode* OperatePanel;
	int OperatePanelIndex;
	CTexture* OperatePanelTextures[5];

	CFreeTypeLoader FreeTypeloader;
	CTexture* OpenJingluoButtonTexture;
};
