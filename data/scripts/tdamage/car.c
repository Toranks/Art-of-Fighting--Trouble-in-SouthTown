void main()
{
	int dmg= getlocalvar("damage");
	void target=getlocalvar("attacker");
	void vSpawn;
	clearspawnentry();
	setspawnentry("name","turn");
	vSpawn = spawn();
	changeentityproperty(vSpawn, "parent",getlocalvar("self"));
	changeentityproperty(vSpawn, "speed",getentityproperty(target,"direction"));

	if (dmg>7){
		changeentityproperty(vSpawn,"animation",openborconstant("ANI_FOLLOW1"));
	}
}


