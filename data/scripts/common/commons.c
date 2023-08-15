#include "data/scripts/common/makeInv.c"
void stayAir(int time)
{
	changeentityproperty(getlocalvar("self"),"tosstime",openborvariant("elapsed_time")+time);
}
void antiGrab(void swi)
{
	setentityvar(getlocalvar("self"),0,swi);
}
void breakGrab(void damage,void fall)
{
	void self=getlocalvar("self");
	void opponent=getentityproperty(self,"link");
	damageentity(opponent,self,damage,fall,openborconstant("ATK_NORMAL"));
}
void flip()
{
	void self=getlocalvar("self");
	changeentityproperty(self,"direction", !getentityproperty(self,"direction")); 
}
void turnJump()
{
	changeentityproperty(getlocalvar("self"), "aiflag", "jumpid",getentityproperty(getlocalvar("self"),"animationid"));
}
void enterAtt(char ani)
{
	void self=getlocalvar("self");
	if(getentityproperty(self,"health")>0){
		performattack(self,openborconstant(ani),0);
		//changeentityproperty(self,"animation", openborconstant(ani));
		//changeentityproperty(self,"aiflag","idling",0);
		//changeentityproperty(self,"aiflag", "attacking", 1);
		//changeentityproperty(self,"takeaction", "common_attack_proc");
	}
}
void changeAni(char ani)
{
	void self = getlocalvar("self");
	if(getentityproperty(self,"health")>0){
		//performattack(self,openborconstant(ani));
		changeentityproperty(self, "animation", openborconstant(ani));
	}
}

void dasher( float Vx, float Vy, float Vz )
{
	void self = getlocalvar("self");
	int dir = getentityproperty(self,"direction");
	if(!dir)Vx = -Vx ;
	changeentityproperty(self, "velocity", Vx, Vz, Vy);
}

void leaper( float Vx, float Vy, float Vz )
{
    void	self	=	getlocalvar("self");
    int		dir		=	getentityproperty(self,"direction");

    if(!dir)Vx=-Vx;
    tossentity(self, Vy, Vx, Vz);
}

void stop()
{
    void self = getlocalvar("self");
    changeentityproperty(self, "velocity", 0, 0, 0);
}
void backAni(char ani)
{
	void self=getlocalvar("self");
	void tar=getentityproperty(self,"link");
	if(!tar){tar=getentityproperty(self,"opponent");}else{}
	if (tar)
	{
		if (getentityproperty(self,"direction")==getentityproperty(tar,"direction"))
		{
			changeAni(ani);
		}
	}
}
