void airAni(void ani,void rangemin,void rangemax)
{
	void self=getlocalvar("self");
	void tar=findtarget(self);
	if(tar)
	{
		if(getentityproperty(tar,"a")>0)
		{
			void distx=getentityproperty(tar,"x") - getentityproperty(self,"x");
			void distz=getentityproperty(tar,"z") - getentityproperty(self,"z");
			void dir=getentityproperty(self,"direction");
			if(distz<0)distz=-distz;
			if(distz>15)return;
			if(dir)
			{
				if(distx>rangemax||distx<rangemin)return;
			}else{
				if(distx<rangemax||distx>rangemin)return;
			}
			stop();
			enterAtt(ani);
		}
	}
}
void speAni(void ani,void rangex,void rangez)
{
	void self=getlocalvar("self");
	void tar=findtarget(self);
	if(tar)
	{
		if(getentityproperty(tar,"animationid")==openborconstant("ANI_SPECIAL"))
		{
			void distx=getentityproperty(tar,"x") - getentityproperty(self,"x");
			void distz=getentityproperty(tar,"z") - getentityproperty(self,"z");
			if(distx<0)distx=-distx;
			if(distz<0)distz=-distz;
			if(distx<rangex&&distz<rangez)enterAtt(ani);
		}
	}
}
