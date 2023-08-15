void damage(int hp,char ani)
{
		void self=getlocalvar("self");
		if (getentityproperty(self,"health")<=(getentityproperty(self,"maxhealth")*hp/100))
		{
			changeentityproperty(self,"animation",openborconstant(ani));
		}
}

void beidle()
{// Go to IDLE animation!
    void self = getlocalvar("self");

    setidle(self, openborconstant("ANI_IDLE"));
}


void clearL()
{ // Clears all local variables
     clearlocalvar();
}





