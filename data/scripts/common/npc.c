void edgeAni(char ani,int x1,int x2)
{
	void self=getlocalvar("self");
	int x=getentityproperty(self,"x") - openborvariant("xpos");
	if(getentityproperty(self,"direction"))
	{
		if (x>x2){enterPain(ani);}
	}else{
		if (x<x1){enterPain(ani);}
	}
}
void enterPain(char num)
{
	void self=getlocalvar("self");
	damageentity(self,self,0,0,openborconstant("ATK_NORMAL"+num));
}
