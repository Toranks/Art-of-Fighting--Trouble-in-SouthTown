#include "data/scripts/common/score.c"
void lock()
{
	lockEntity(1);
}
void lockEntity(void noair)
{
	void self = getlocalvar("self");
	void target = getentityproperty(self, "grabbing");
	if (!target){
		target = getentityproperty(self, "opponent");
		if(!target){
			setentityvar(self,0,0);
			setidle(self,openborconstant("ANI_IDLE"));
			return;
		}
	}
	if(getentityproperty(target,"type")==openborconstant("TYPE_OBSTACLE")
		||getentityproperty(target,"dead")
		||getentityproperty(target,"antigrab")
		){
		setidle(self,openborconstant("ANI_IDLE"));
	}else{
		if(noair)
		{
			if(getentityproperty(target,"a")!=getentityproperty(target,"base"))
			{
				setidle(self,openborconstant("ANI_IDLE"));
				return;
			}
		}
		setentityvar(self,0,target);
		setentityvar(target,0,1);
	}
}
void slamStart()
{
	void self = getlocalvar("self");
	if(!self){return;}else{}
	void target = getentityvar(self,0);
	if(target)
	{
		changeentityproperty(target,"noaicontrol",1);
		performattack(target,openborconstant("ANI_FALL7"));
	}else{
		setidle(self,openborconstant("ANI_IDLE"));
	}
}
void position(int Frame, float dx, float dy, float dz, int face)
{
	void self = getlocalvar("self");
	if(!self){return;}else{}
	void target = getentityvar(self,0);
	if(target)
	{
		updateframe(target, Frame);
		bindentity(target, self, dx, dz, dy, face, 0);
		//changeentityproperty(target,"nextthink",openborvariant("elapsed_time")+250);
		//changeentityproperty(target,"nextanim",openborvariant("elapsed_time")+250);
	}
}
void depost()
{
	depost01(0);
}
void depost01(void bounce)
{
	void self = getlocalvar("self");
	void target = getentityvar(self,0);
	if(target)
	{
		bindentity(target, NULL());
		if(bounce)
		{
			changeentityproperty(target,"velocity",0,0,0);

		}
	}
}
void slamHurt()
{
	//void self = getlocalvar("self");
	//void target = getentityvar(self,0);
	//void model;
	//if(target){
	//	model=getentityproperty(target,"model");
	//	if	(model=="Hugo"
	//		||model=="Andore"
	//		||model=="Raiden"
	//		||model=="Chang"
	//		||model=="Alex"
	//		||model=="Zankuro"
	//		)
	//	{
	//		depost();
	//		clearSlam();
	//		damageentity(self,target,15,1,openborconstant("ATK_NORMAL"));
	//		damageentity(target,self,0,1,openborconstant("ATK_NORMAL"));
	//		tossentity(target,-1,0.01, 0);
	//	}
	//}
}
void clearSlam()
{
	void self = getlocalvar("self");
	void target = getentityvar(self,0);
	void x,zself,xself,offset,wall,i;
	void base=getentityproperty(self,"base");
	if(target)
	{
		setentityvar(self,0,NULL());
		setentityvar(target,0,NULL());
		x=getentityproperty(target,"x");
		xself=getentityproperty(self,"x");
		zself=getentityproperty(self,"z");
		changeentityproperty(target,"noaicontrol",0);
		if (xself>x){
			offset=2;
		}else{
			offset=-2;
		}
		for (i=0;i<200;i++)
		{
			wall=checkwall(x,zself);
			if (wall<=base){
				changeentityproperty(target,"position",x,zself);
				return;
			}
			x+=offset;
		}
	}
}
void finish(int Damage, int x, int y, int z, int faceOpposite)
{
	void self = getlocalvar("self");
	void target = getentityvar(self,0);
	int SDir = getentityproperty(target,"direction");
	int MDir;

	if(faceOpposite){
		MDir=!SDir;
	}else{
		MDir=SDir;
	}
	if(target)
	{
		int dir = getentityproperty(target,"direction");
		if(!dir)x = -x;
		damageentity(target, self, Damage, 1, openborconstant("ATK_NORMAL")); 
		tossentity(target, y, x, z);
		changeentityproperty(target, "direction", MDir);
	}
}

void antiWall2()
{//Checks distance from the walls
 //If inside of the walls, entity will be moved away with defined movement
	void self 		= getlocalvar("self");
	void target 	= getentityvar(self, "grabbed");
	int direction 	= getentityproperty(self, "direction");
	int x 			= getentityproperty(self, "x");
	int Tx 			= getentityproperty(target, "x");
	int z 			= getentityproperty(self, "z");
	int Tz 			= getentityproperty(target, "z");
	int subWall		= getentityproperty(self, "subject_to_wall");
	float wall 		= checkwall(Tx, Tz);

	if(target != NULL()){
		if(wall){
			if(subWall == 1){
				changeentityproperty(target, "position", x);
				changeentityproperty(target, "velocity", 0, 0, NULL());
			}
		}
	}
}

void throw(int Damage, int x, int y, int z, int faceOpposite)
{
	void self = getlocalvar("self");
	void target = getentityvar(self,0);
	int SDir = getentityproperty(target,"direction");
	int MDir;

	if(faceOpposite){
		MDir=!SDir;
	}else{
		MDir=SDir;
	}

	if(target)
	{
		int dir = getentityproperty(target,"direction");
		if(!dir){
			x = -x;
		}
		bindentity(target, NULL());
		damageentity(target, self, 0, 1, openborconstant("ATK_NORMAL4"));
		changeentityproperty(target, "attacking", 1);
		changeentityproperty(target, "damage_on_landing", Damage);
		changeentityproperty(target, "projectile", 1);
		changeentityproperty(target, "direction", MDir);
		tossentity(target, y, x, z);
		clearSlam();
		
   }
}

void hurt(int aamage)
{ 
	hurt2(aamage,0);
}
void hurt2(int damage,int is_live)
{
	hurt3(damage,is_live,7,1);
}
void hurt3(int Damage,int is_live,int type,int keepframe)
{
	void self = getlocalvar("self");
	void target = getentityvar(self,0);
	if(!target){return;}else{}
	int TAniPos = getentityproperty(target,"animpos");
	
	if (is_live){
		void hp=getentityproperty(target,"health");
		void thp = hp;
		thp -=Damage;
		if(thp<1)thp=1;
		changeentityproperty(target,"health",thp);
		addScore(self,Damage*5);
	}else{
		if(!type)
			damageentity(target, self, Damage, 1, openborconstant("ATK_NORMAL"));
		else
			damageentity(target, self, Damage, 1, openborconstant("ATK_NORMAL"+type));
	}
	if (keepframe)updateframe(target, TAniPos);
}
