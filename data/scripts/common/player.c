#include "data/scripts/common/setvalid.c"
#include "data/scripts/msg/sendMsg.c"
void recover()
{
	void self = getlocalvar("self");
	int	iPIndex = getentityproperty(self,"playerindex");
	void Health = getentityproperty(self,"health");
	void ijump = playerkeys(iPIndex, 0, "moveup","attack");
	if	(Health >= 1 && ijump){
		sendMessage("RECOVER!");
		void mp=getentityproperty(self,"mp")+10;
		changeentityproperty(self,"mp",mp);
		changeentityproperty(self, "animation", openborconstant("ANI_FOLLOW5"));
	}
}
void stealth(void value)
{
	changeentityproperty(getlocalvar("self"),"stealth",value);
}
void noRun(){
	void self = getlocalvar("self");
	changeentityproperty(self, "aiflag", "running", 0);
}
void overHeat(void time)
{
	void self=getlocalvar("self");
	void index=getentityproperty(self,"playerindex");
	void t=openborvariant("ent_max");
	void i,ent;
	for(i=0;i<t;i++){
		ent=getentity(i);
		if(
			getentityproperty(ent,"Model")=="Meter"
			&&getentityproperty(ent,"parent")==self
			)
		{
			sendMessage("LIMITED!");
			if(getentityproperty(self,"a")>getentityproperty(self,"base"))
			{
				enterAtt("ANI_PAIN");//damageentity(self,self,0,1,openborconstant("ATK_NORMAL"));
			}else{
				enterAtt("ANI_PAIN");
			}
			return;
		}
	}
	
	clearspawnentry();
	setspawnentry("name","meter");
	//setspawnentry("coords",40+index*160,openborvariant("ypos")+268);
	void lh=openborvariant("levelheight");
	if(lh<272)lh=272;
	setspawnentry("coords",30+index*160,lh-20);
	void vSpawn=spawn();

	changeentityproperty(vSpawn,"parent",self);
	//bindentity(vSpawn, self, 0, 1, y, 2, 0);
	changeentityproperty(vSpawn,"edelay",1,time,1,999,1,999);
}
void noDropDamage()
{
	void self=getlocalvar("self");
	changeentityproperty(self,"damage_on_landing",0);
	changeentityproperty(self,"nograb",0);
	changeentityproperty(self,"aiflag","falling",0);
	changeentityproperty(self,"aiflag","drop",0);
	changeentityproperty(self,"aiflag","projectile",0);
	changeentityproperty(self,"takeaction", "common_attack_proc");
}
void aiFlag(int flag, int on, int action)
{
	void vSelf = getlocalvar("self");
	changeentityproperty(vSelf, "aiflag", flag, on);
	changeentityproperty(vSelf, "takeaction", action);
}

void sendMessage(char msg)
{
	sendMsg(getlocalvar("self"),msg);
}

void block(int Flag)
{
	void self = getlocalvar("self");
	//changeentityproperty(self, "aiflag", "idling", !Flag);
	changeentityproperty(self, "aiflag", "blocking", Flag);
	//changeentityproperty(self, "takeaction", "common_block");
}
void select()
{
	if(openborvariant("in_level")){return;}else{}
	void self=getlocalvar("self");
	void st=openborvariant("current_stage");
	void x=getentityproperty(self,"x");
	x%=++x;
	setValid("Sarah",st>2);
	setValid("Ingrid",getglobalvar("clearCount")>0);
	setglobalvar("select."+x+".name",getentityproperty(self,"model"));
}

void costSelf(int Damage)
{
	void self = getlocalvar("self");
	void mp = getentityproperty(self,"mp");
	int health;
	int v=mp - Damage;

	if(v>=0){
		changeentityproperty(self,"mp",v);
	}else{
		v=-v;
		health=getentityproperty(self,"health");
		if (health>(v/2)){
			changeentityproperty(self,"health",health-(v/2));
			changeentityproperty(self,"mp",0);
			sendMsg(self,"OVER GAUGE!");
		}else{
			sendMsg(self,"EMPTY!");
			changeAni("ANI_PAIN");
		}
	}
}

void stall()
{
	void tar=getentityproperty(getlocalvar("self"),"grabbing");
	if(tar){changeentityproperty(tar,"stalltime",openborvariant("elapsed_time")+1000);}
}
