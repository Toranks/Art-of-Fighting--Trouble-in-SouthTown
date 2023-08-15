void tele()
{
	void self = getlocalvar("self");
	int minz,maxz,center;
	minz=openborvariant("PLAYER_MIN_Z");
	maxz=openborvariant("PLAYER_MAX_Z");
	center=(maxz - minz)/2;
	int Tx = rand()%160+160 + openborvariant("xpos");
	int Tz = rand()%center+center+minz;
	changeentityproperty(self,"position",Tx,Tz,0);
}
