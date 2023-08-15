void tyrantBody(int enabled,float fac)
{
		int count,down;
		void self = getlocalvar("self");
		if(enabled)
		{
			count=17;down=0;
		}else{
			count=1;down=1;
		}
		changeentityproperty(self,"defense",openborconstant("ATK_NORMAL"),fac,count,down);
		changeentityproperty(self,"defense",openborconstant("ATK_NORMAL2"),fac,count,down);
		changeentityproperty(self,"defense",openborconstant("ATK_BLAST"),fac,count,down);
}
