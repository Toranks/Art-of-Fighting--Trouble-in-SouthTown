#include "data/scripts/common/cangrab.c"
int pushKey(void Key)
{
	void self = getlocalvar("self");
	int iPIndex = getentityproperty(self,"playerindex");
	void iRKey=0;
	if (Key=="U"){
		iRKey = playerkeys(iPIndex, 0, "moveup");
	}
	if (Key=="D"){
		iRKey = playerkeys(iPIndex, 0, "movedown");
	}
	if (Key=="F"){
		if (getentityproperty(self,"direction")==0){
			iRKey = playerkeys(iPIndex, 0, "moveleft");
		}else{
			iRKey = playerkeys(iPIndex, 0, "moveright");
		}
	}
	if (Key=="B"){
		if (getentityproperty(self,"direction")==1){
			iRKey = playerkeys(iPIndex, 0, "moveleft");
		}else{
			iRKey = playerkeys(iPIndex, 0, "moveright");
		}
	}
	if (Key=="J"){
		iRKey = playerkeys(iPIndex, 0, "jump");
	}
	if (Key=="A"){
		iRKey = playerkeys(iPIndex, 0, "attack");
	}
	if (Key=="S"){
		iRKey = playerkeys(iPIndex, 0, "special");
	}
	if (Key=="A2"){
		iRKey = playerkeys(iPIndex, 0, "attack2");
	}
	if (Key=="UA"){
		iRKey = playerkeys(iPIndex, 0, "moveup","attack");
	}
	if (Key=="DA"){
		iRKey = playerkeys(iPIndex, 0, "movedown","attack");
	}
	if (Key=="BJ"){
		if (getentityproperty(self,"direction")==1){
			iRKey = playerkeys(iPIndex, 0, "moveleft","jump");
		}else{
			iRKey = playerkeys(iPIndex, 0, "moveright","jump");
		}
	}
	if (Key=="BA"){
		if (getentityproperty(self,"direction")==1){
			iRKey = playerkeys(iPIndex, 0, "moveleft","attack");
		}else{
			iRKey = playerkeys(iPIndex, 0, "moveright","attack");
		}
	}
	if (Key=="FJ"){
		if (getentityproperty(self,"direction")==0){
			iRKey = playerkeys(iPIndex, 0, "moveleft","jump");
		}else{
			iRKey = playerkeys(iPIndex, 0, "moveright","jump");
		}
	}
	if (Key=="UJ"){
		iRKey = playerkeys(iPIndex, 0, "moveup", "jump");
	}
	return iRKey;
}

void key(void Key,void Ani,int Valid)
{
	void self = getlocalvar("self");
	if (Valid){
		void tar=getentityproperty(self,"opponent");
		if(canGrab(tar,1)
			&&getentityproperty(tar,"direction")!=getentityproperty(self,"direction")
			&&getentityproperty(tar,"a")==getentityproperty(tar,"base")
		){
			int dis_z=getentityproperty(tar,"z") - getentityproperty(self,"z");
			int dis_x=getentityproperty(tar,"x") - getentityproperty(self,"x");
			if (dis_z<0)dis_z=-dis_z;
			if (dis_x<0)dis_x=-dis_x;
			if (dis_z>10||dis_x>90)return;
		}else{
			return;
		}
	}
	if (pushKey(Key)){
		//performattack(self,openborconstant(Ani));
		changeentityproperty(self, "animation", openborconstant(Ani));
		//changeentityproperty(self, "animpos", 0);
	}
}
void key1(void Key)
{
	if (pushKey(Key)){
		setlocalvar("Key",0);
	}else{
		setlocalvar("Key",1);
	}
}
void key2(void Key,void Ani, int Frame)
{
	if (getlocalvar("Key"))
	{
		key(Key,Ani,Frame);
	}
}
