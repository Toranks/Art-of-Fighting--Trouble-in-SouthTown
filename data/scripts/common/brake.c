void brakeIdle(void ani,void defaultspd)
{
	void self = getlocalvar("self");
	changeentityproperty(self, "running", defaultspd);
	if(getscriptvar(0))performattack(self,openborconstant(ani));
	setscriptvar(0,0);
}
void brakeWalk(void ani,void defaultspd)
{
	void self = getlocalvar("self");
	int d = getentityproperty(self, "direction");
	changeentityproperty(self, "running", defaultspd);
	if(getscriptvar(0)){
		performattack(self,openborconstant(ani));
		changeentityproperty(self, "direction",!d);
	}
	setscriptvar(0,0);
}
void brakeRun(void incspd,void brakespd,void maxspd)
{
	void self  = getlocalvar("self");
	float spd = getentityproperty(self, "running","speed");
	float vx =  getentityproperty(self, "xdir");
	float vz =  getentityproperty(self, "zdir");
	if(spd<maxspd)spd+=incspd;
	if(vx>0)
		vx=spd;
	else if(vx<0)
		vx = -spd;
	if(vz>0)
		vz = spd/2;
	else if(vz<0)
		vz = -spd/2;
	changeentityproperty(self, "velocity", vx, vz);
	changeentityproperty(self, "running", spd);
	if(spd>brakespd)
		setscriptvar(0,1);
	else
		setscriptvar(0,0);
}
