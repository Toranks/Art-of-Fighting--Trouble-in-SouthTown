void hurt(int Damage,int pain,int hitdelay,int knockdown,int is_live)
{
	void self = getlocalvar("self");
	void target = getentityproperty(self, "opponent");
	if (target)
	{
		if (is_live){
			int THealth = getentityproperty(target,"health");
			if(THealth <= Damage){Damage = THealth - 1;}
		}
		damageentity(target, self, Damage, knockdown, openborconstant("ATK_NORMAL")+pain);
		int enextanim = getentityproperty(target, "nextanim");
		int enextthink = getentityproperty(target, "nextthink");
		changeentityproperty(target, "nextanim", enextanim + hitdelay);
		changeentityproperty(target, "nextthink", enextthink + hitdelay);
		enextanim = getentityproperty(self, "nextanim");
		enextthink = getentityproperty(self, "nextthink");
		changeentityproperty(self, "nextanim", enextanim + hitdelay);
		changeentityproperty(self, "nextthink", enextthink + hitdelay);
	}
}

