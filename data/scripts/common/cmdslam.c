#include "data/scripts/common/slam.c"
#include "data/scripts/common/cangrab.c"
#include "data/scripts/common/inRange.c"
void lockR(int Rx, int Rz,int Ra,char ani1,char ani2)
{
	cmdLock(Rx, Rz, Ra,ani1,ani2,0);
}
void lockRA(int Rx, int Rz,int Ra,char ani1,char ani2)
{
	cmdLock(Rx, Rz, Ra,ani1,ani2,1);
}
void lockRAll(int Rx, int Rz,int Ra,char ani1,char ani2)
{
	cmdLock(Rx, Rz, Ra,ani1,ani2,2);
}

void cmdLock(int Rx, int Rz,int Ra,char ani1,char ani2,int air)
{
	void self=getlocalvar("self");
	void target=findTarget01(Rx,Rz,Ra,1,air);
	if (target){
		setentityvar(self,0,target);
		if (ani1!=""){
			setentityvar(target,0,1);
			changeAni(ani1);	
		}
	}else{
		if (ani2!=""){
			changeAni(ani2);
		}
	}
}
void lockRE(int Rx, int Rz,int Ra,char ani1,char ani2)
{
	void self=getlocalvar("self");
	void target=findTarget01(Rx,Rz,Ra,0,0);
	if (target!=NULL()){
		setentityvar(self,0,target);
		setentityvar(target,0,1);
		if (ani1!=""){
			enterAtt(ani1);
		}
	}else{
		if (ani2!=""){
			enterAtt(ani2);
		}
	}
}

void findTarget01(int Rx, int Rz,int Ra,int isEnemy,int air)
{
	//air:Air limit is set
	int iECnt = openborvariant("ent_max");
	int iEnt;
	void vEnt,ani;
	void self = getlocalvar("self");
	for(iEnt=0; iEnt<iECnt; iEnt++)
	{
		vEnt=getentity(iEnt);
		if (canGrab(vEnt,isEnemy)){
			if (isInRange(self,vEnt,Rx,Rz,Ra)){
				if(air==1){
					//entity must in air and can hurt falling entity
					if(getentityproperty(vEnt,"a")>getentityproperty(vEnt,"base")){
						return vEnt;
					}
				}else if(air==0){
					if(!getentityproperty(vEnt,"nograb")){
						//can't hurt falling entity if no air
						return vEnt;
					}
				}else if(air==2){
					//Can hurt all status
					return vEnt;
				}
			}
		}
	}
	return NULL();
}
