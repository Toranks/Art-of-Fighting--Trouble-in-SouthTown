
void main()
{
	void self = getlocalvar("self");
	void vName = getentityproperty(self,"name");
	void target = findtarget(self);

	float Tx = getentityproperty(self, "x");
	float Tz = getentityproperty(self, "z");
	float Tz1 = Tz+5;




	void vSpawn;
	clearspawnentry();
	setspawnentry("name", vName);

	vSpawn = spawn();

	changeentityproperty(vSpawn, "position", Tx, Tz, 0);
	performattack(vSpawn, openborconstant("ANI_FOLLOW1"));
	performattack(target, openborconstant("ANI_FOLLOW17"));
	changeentityproperty(target, "position", Tx, Tz1, 0);
}