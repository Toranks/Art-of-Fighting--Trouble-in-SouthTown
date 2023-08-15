void lockR(int Rx, int Rz,int Ra,char ani1,char ani2)
{
	void self=getlocalvar("self");
	void target=findTarget01(Rx,Rz,Ra,"TYPE_ENEMY");
	if (target!=NULL()){
		if (ani1!=""){
			changeAni(ani1);
		}
	}else{
		if (ani2!=""){
			changeAni(ani2);
		}
	}
}

void findTarget01(int Rx, int Rz,int Ra,char find_type)
{
	int iECnt = openborvariant("ent_max");
	int iEnt;
	void vEnt,ani;
	void self = getlocalvar("self");
	float x = getentityproperty(self, "x");
	float z = getentityproperty(self, "z");
	float a = getentityproperty(self, "a");
	int dir=getentityproperty(self,"direction");

	for(iEnt=0; iEnt<iECnt; iEnt++)
	{
		vEnt=getentity(iEnt);
		if (
		getentityproperty(vEnt,"type")==openborconstant(find_type)
		&& getentityproperty(vEnt,"exists")
		&& !getentityproperty(vEnt,"dead")
		&& vEnt){	
			if (isInRange(self,dir,vEnt,Rx,Rz,Ra,x,z,a)){return vEnt;}
		}
	}
	return NULL();
}
int isInRange(void self,int dir,void target,int Rx, int Rz,int Ra,float x,float z,float a)
{
	float Tx = getentityproperty(target, "x");
	float Tz = getentityproperty(target, "z");
	float Ta = getentityproperty(target, "a");
	float Disx;
	float Disz = Tz - z;
	float Disa = Ta - a;

	if (dir==0){
		Disx = x - Tx;
	}else{
		Disx = Tx - x;
	}

	if(Disz < 0){
		Disz = -Disz;
	}
	if(Disa < 0){
		Disa = -Disa;
	}
	
	if( Disx <= Rx && Disx>0 && Disz <= Rz && Disa<=Ra)
	{
		return 1;
	}else{
		return 0;
	}
}
