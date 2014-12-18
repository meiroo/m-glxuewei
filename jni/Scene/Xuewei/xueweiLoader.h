#pragma once
#include "mglTypes.h"

#define XUEWEI_FILE_NAME "xwsj.lj"  //穴位内容文件
#define XUEWEI_NUM 361

//#define  EDIT_XUEWEI_MODE

class CTexture;

struct JINGLUO
{
	int jingluo_id; //所属经络编号
	char* jingluo_cname;  //所属经络(中文)
	int jingluo_start;
	int jingluo_count;
	point4f jingluo_color;
	JINGLUO():jingluo_id(-1),jingluo_count(0){}

};

struct XUEWEI  // 穴位整体内容结构
{
	float world_x,world_y,world_z;  //穴位坐标world_x,world_y,world_z,
	float mx,my;  //人体移动坐标mx,my,
	float dx;  //人体大小dx,
	float jiaodu_x,jiaodu_y;  //人体旋转角度jiaodu_x,jiaodu_y
	int xuewei_id; //穴位编号
	char xuewei_ename[100];  //穴位名(英文)
	char xuewei_cname[100];  //穴位名(中文)
	int jingluo_id; //所属经络编号
	char jingluo_cname[100];  //所属经络(中文)
	char shiyi[500];  //穴位释义
	char gongneng[500]; //穴位功能
	char weizhi[500];//穴位位置
};

class CRectNode;
class CLineNode;
class CXueWeiLoader
{
public:
	XUEWEI* xuewei;  //穴位总数不超过500
	JINGLUO* jingluo;

	void SetJingluo(XUEWEI& xuewei);
	point4f GetJingluoColor(int jingluo_id);
	CTexture* GetJingluoColorTex();
	bool Load(CRectNode* Rects, CLineNode* Lines);
	virtual ~CXueWeiLoader();
};