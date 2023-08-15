
void main()
{
	void self = getlocalvar("self");
	void vName = "runetb1";

	int XPos = openborvariant("xpos");
	int YPos = openborvariant("ypos");
	int sh = openborvariant("hResolution");
	int sv = openborvariant("vresolution");

	int Tx = XPos+10;
	int Ty = 5;
	int Tz = YPos+260;

	void go1 = getentityproperty(self,"name");
	void vSpawn;

	clearspawnentry();
	setspawnentry("name", vName);

	vSpawn = spawn();

	changeentityproperty(vSpawn, "position", Tx, Tz, Ty);
	performattack(vSpawn, openborconstant(go1));
	return vSpawn;
}