#include "3dXueweiLogic.h"
#include "Scene.h"
#include "Render.h"
#include "PanelNode.h"
#include "LineNode.h"
#include "xueweiLoader.h"

XueweiLogic::XueweiLogic(CScene* scene,CNode* manNode,CNode* lines):Scene(scene),ManNode(manNode),XueWeiLines(lines)
{
	Render = Scene->Render;
	Scene->CollisionNodes.push_back(ManNode);

	OpenJingluoButtonTexture = FreeTypeloader.LoadStrImageFromFont("lanting.ttf",L"open",32);
}

int XueweiLogic::CheckOperatePanelSelected(CPanelNode* panel,int &index,int& lastIndex, int x, int y)
{
	index = panel->GetSelected(x,y,Render->Width,Render->Height);
	if(index ==0)
	{
		OperatePanelIndex = (OperatePanelIndex + 1)%4;
		OperatePanel->SetTexture(0,OperatePanelTextures[OperatePanelIndex]);
	}else if(index == 1)
	{
		static bool on = false;
		on = !on;
		static_cast<CPanelNode*>(panel)->SetSelected(index,on);
		if(on)
		{
			ManNode->DrawMode = EDM_POINTS;
			XueWeiLines->SetVisible(true);
		}else
		{
			ManNode->DrawMode = EDM_TRIANGLES;
			XueWeiLines->SetVisible(false);
		}

	}
	return index;
}


void XueweiLogic::OperatePanelInit(CPanelNode* panel)
{
	OperatePanel = panel;
	OperatePanelIndex = 3;
	OperatePanel->DisableViewMatrix = true;
	OperatePanelTextures[0] = FreeTypeloader.LoadStrImageFromFont("lanting.ttf",L"位移",32);
	OperatePanelTextures[1] = FreeTypeloader.LoadStrImageFromFont("lanting.ttf",L"旋转",32);
	OperatePanelTextures[2] = FreeTypeloader.LoadStrImageFromFont("lanting.ttf",L"缩放",32);
	OperatePanelTextures[3] = FreeTypeloader.LoadStrImageFromFont("lanting.ttf",L"手势",32);
	OperatePanelTextures[4] = FreeTypeloader.LoadStrImageFromFont("lanting.ttf",L"皮肤",32);
	OperatePanel->SetTexture(0,OperatePanelTextures[OperatePanelIndex]);
	OperatePanel->SetTexture(1,OperatePanelTextures[4]);
	static_cast<CPanelNode*>(OperatePanel)->SetSelected(0);
	OperatePanel->BlendOpen = true;
	OperatePanel->SrcBlendType = EBF_SRC_ALPHA;
	OperatePanel->DstBlendType = EBF_ONE_MINUS_SRC_ALPHA;
}

void XueweiLogic::JingLuoPanelInit(CPanelNode* panel,CXueWeiLoader* loader)
{
	panel->DisableViewMatrix = true;
	for(int i =1;i<=12;i++)
	{
		point4f jcolor = loader->GetJingluoColor(i);
		jcolor.M = 0.75;
		panel->Mesh.MeshBuffers[i]->DefaultColor = jcolor;
	}
	//panel->SetSelected(1);
	panel->BlendOpen = true;
	panel->SetTexture(0,FreeTypeloader.LoadStrImageFromFont("lanting.ttf",L"全部",32));
	point4f color(1,1,1,0.0);
	panel->Mesh.MeshBuffers[0]->DefaultColor = color;
	panel->SetVisible(false);

}

void XueweiLogic::ReadMePanelInit(CPanelNode* panel)
{
	panel->SetVisible(false);
	wchar_t* str = L"手势操作：                                                       "\
		L"单指拖动触发人物旋转                    "\
		L"双指距离拉缩触发人物放大缩小       "\
		L"双指等距离平移触发人物平移          "\
		L"皮肤选项可以显示人体/显示经络连线"\
		L"Open选项可以显示单条经络显示      "\
		L"点击穴位则显示该穴位信息              "\
		L"---------------------------"\
		L"联系作者： meiroo@outlook.com"\
		;
	CTexture* tex = FreeTypeloader.LoadStrImageFromFont("lanting.ttf",str,32,512);
	panel->SetTexture(tex);
}

void XueweiLogic::JingLuoSwitchInit(CPanelNode* panel)
{
	panel->DisableViewMatrix = true;


	panel->BlendOpen = true;
	panel->SrcBlendType = EBF_SRC_ALPHA;
	panel->DstBlendType = EBF_ONE_MINUS_SRC_ALPHA;

	panel->SetTexture(0,OpenJingluoButtonTexture);
	point4f color(1,1,1,0);
	panel->Mesh.MeshBuffers[0]->DefaultColor = color;

	//panel->SetVisible(false);

}

int XueweiLogic::CheckPanelSelected(CPanelNode* panel,int x, int y)
{
	if(!panel->Visible)
		return -1;
	int index = panel->GetSelected(x,y,Render->Width,Render->Height);
	return index;
}

bool XueweiLogic::GetCollisionManPos(int x, int y,point3f& pos)
{
	line2f ray = Scene->Render->getRayLineFromScreenXY(point2f(x,y),false);
	point2f uvCollision;
	int pong = Scene->GetCollisionStatus(ray, pos,uvCollision);
	if(pong==-1)
		return  false;
	return true;
}
void XueweiLogic::AddNewXuewei(CNode* marker,int x, int y)
{
	line2f ray = Scene->Render->getRayLineFromScreenXY(point2f(x,y),false);
	point3f collpos;
	point2f uvCollision;
	int pong = Scene->GetCollisionStatus(ray, collpos,uvCollision);
	if(pong==-1)
		return;
	marker->Position = collpos*3;
	marker->Scale = point3f(0.003,0.003,0.003);
	marker->SetVisible(true);
}