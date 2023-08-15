void canGrab(void vEnt,void isEnemy)
{
	void type;
	void vulnerable=1;
	if(isEnemy)
		type=openborconstant("TYPE_ENEMY");
	else
	{
		type=openborconstant("TYPE_PLAYER");
		vulnerable=getentityproperty(vEnt, "vulnerable");
	}

	if (vEnt
	&& getentityproperty(vEnt,"type")==type
	&& getentityproperty(vEnt,"antigrab")<1
	&& !getentityproperty(vEnt,"dead")
	&& !getentityvar(vEnt,0)
	&& !getentityproperty(vEnt,"aiflag","invincible")
	&& getentityproperty(vEnt,"animationid")!=openborconstant("ANI_RISE")
	&& vulnerable
	)
		return 1;
	else
		return 0;
}
