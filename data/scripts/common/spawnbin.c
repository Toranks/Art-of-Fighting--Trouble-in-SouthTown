void killAni(void bindAni)
{
	void parent=getentityproperty(getlocalvar("self"),"parent");
	if(parent){
		if (getentityproperty(parent,"animationid")!=openborconstant(bindAni))
		{
			killentity(getlocalvar("self"));
		}
	}
}
