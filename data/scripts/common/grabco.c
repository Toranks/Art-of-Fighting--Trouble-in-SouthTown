void grabAttack()
{
	void self=getlocalvar("self");
	if(self){
		void target=getentityproperty(self,"opponent");
		//damageentity(t,getlocalvar("self"),1,0,openborconstant("ATK_NORMAL"));
		performattack(target,openborconstant("ANI_PAIN"));
	/*	changeentityproperty(target,"aiflag","attacking",1);
		changeentityproperty(target,"aiflag","idling",0);*/
	}
}

void grabCounter(void time)
{
	changeentityproperty(getlocalvar("self"),"stalltime",openborvariant("elapsed_time")+time);
}
