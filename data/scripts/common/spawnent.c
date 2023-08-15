void spawnEnt(void vName,void x,void z)
{
	clearspawnentry();
	setspawnentry("name", vName);
	setspawnentry("coords",x,z);
	return spawn();
}
