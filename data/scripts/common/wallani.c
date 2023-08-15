void wallAni(void anim)
{
	void self=getlocalvar("self");
	void dir=getentityproperty(self,"direction");
	void x=getentityproperty(self,"x");
	void z=getentityproperty(self,"z");
	void a=getentityproperty(self,"base");
	void i;
	if(dir){
		for (i=x+1;i<x+40;i+=2)
		{
			if(checkwall(i,z)>a)
			{
				performattack(self,openborconstant(anim));
				return 1;
			}
		}
	}else{
		for (i=x-40;i<x-1;i+=2)
		{
			if(checkwall(i,z)>a)
			{
				performattack(self,openborconstant(anim));
				return 1;
			}
		}
	}
	return 0;
}

