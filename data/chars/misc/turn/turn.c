void turn(int angle)
{
	void self=getlocalvar("self");
	void ent=getentityproperty(self,"parent");
	if (ent){
		if (!getentityproperty(self,"speed")){angle=-angle;}
		setdrawmethod(ent, 1, 256, 256, 0, 0, 0,0,0,0,angle);
	}
}
