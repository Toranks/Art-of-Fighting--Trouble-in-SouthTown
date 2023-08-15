void moveToTarget(float spd,float rangex,float rangez)
{
    moveToPointedTarget(findtarget(getlocalvar("self")),spd,rangex,rangez,"");
}
void moveToTarget1(float spd,float rangex,float rangez,void ani)
{
    moveToPointedTarget(findtarget(getlocalvar("self")),spd,rangex,rangez,ani);
}
void moveToPointedTarget(void target,float spd,float rangex,float rangez,void ani)
{
    void self = getlocalvar("self");
	int dirZ=-1;
	int dir=0;
	int currentdir=getentityproperty(self,"direction");
    float x = getentityproperty(self, "x");
    float z = getentityproperty(self, "z");
	if (target){
		float Tx = getentityproperty(target, "x");
		float Tz = getentityproperty(target, "z");
		float Dx=x-Tx;
		float Dz=(z-Tz)*2;
		if(Dx<0){Dx=-Dx;dir=1;}
		if(Dz<0){Dz=-Dz;dirZ=1;}
		if(currentdir!=dir)changeentityproperty(self,"direction",dir);
		if(Dz<rangez*2 && Dx<rangex){
			if (ani=="ANI_IDLE")
			{
				setidle(self);
				
				return;
			}else if(ani!="")
			{
				performattack(self,openborconstant(ani),0);
				return;
			}
		}

		if(spd==-1){
			spd=getentityproperty(self,"speed");
		}else{}

		float Dis=Dx+Dz;
		float Vx,Vz;

		if (!Dis){Dis=1;}

		Vx=spd*Dx/Dis;
		Vz=spd*Dz/Dis*0.5;

		if(!currentdir)
			Vx=-Vx;
		changeentityproperty(self, "velocity", Vx, Vz*dirZ);
	}else{
		changeentityproperty(self, "velocity", 0,0,0);
		setidle(self);
	}
}
void inRangeAni(void Tx,void Tz,float rangex,float rangez,void ani)
{
    void self = getlocalvar("self");
    float x = getentityproperty(self, "x");
    float z = getentityproperty(self, "z");
	float Dx=x-Tx;
	float Dz=(z-Tz)*2;
	if(Dx<0){Dx=-Dx;}
	if(Dz<0){Dz=-Dz;}
	if(Dz<rangez*2 && Dx<rangex){
		if (ani=="ANI_IDLE")
		{
			stop();
			setidle(self);
		}else if(ani!="")
		{
			stop();
			performattack(self,openborconstant(ani),0);
		}
	}
}
void moveToPoint(void Tx,void Tz,float spd)
{
    void self = getlocalvar("self");
	int dirZ=-1;
	int dir=0;
	int currentdir=getentityproperty(self,"direction");
    float x = getentityproperty(self, "x");
    float z = getentityproperty(self, "z");
	float Dx=x-Tx;
	float Dz=(z-Tz)*2;
	if(Dx<0){Dx=-Dx;dir=1;}
	if(Dz<0){Dz=-Dz;dirZ=1;}
	if(currentdir!=dir)changeentityproperty(self,"direction",dir);
	if(spd==-1){
		spd=getentityproperty(self,"speed");
	}else{}
	float Dis=Dx+Dz;
	float Vx,Vz;
	if (!Dis){Dis=1;}
	Vx=spd*Dx/Dis;
	Vz=spd*Dz/Dis*0.5;
	if(!currentdir)
		Vx=-Vx;
	changeentityproperty(self, "velocity", Vx, Vz*dirZ);
}
