void keyMove(float V)
{
	void self = getlocalvar("self");
	int iPIndex = getentityproperty(self,"playerindex");
	float xdir = 0;
	float zdir = 0;

	if (playerkeys(iPIndex, 0, "moveleft")){
		xdir = -V;
	} else if(playerkeys(iPIndex, 0, "moveright")){
		xdir = V;
	}
	changeentityproperty(self, "velocity", xdir, zdir);
}
