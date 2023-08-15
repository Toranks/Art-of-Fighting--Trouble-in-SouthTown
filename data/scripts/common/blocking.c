void blockingStart()
{
	if (!getlocalvar("bReady")){return;}else{}
	void self=getlocalvar("self");
	int iPIndex = getentityproperty(self,"playerindex");
	int key;
	
	if (getentityproperty(self,"direction"))
	{
		key = playerkeys(iPIndex, 0, "moveright");
	}else{
		key = playerkeys(iPIndex, 0, "moveleft");
	}
	if (key)
	{
		block(1);
		setlocalvar("blocking",1);
	}
}
void blockingEnd()
{
	if (!getlocalvar("blocking")){return;}else{}
	block(0);
	setlocalvar("bReady",0);
}
void bReady()
{
	setlocalvar("bReady",1);
}
