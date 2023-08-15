void rangeAtt(float x,float z,char ani)
{
	void self = getlocalvar("self");
	void target = findtarget(self);
	float x1 = getentityproperty(target,"x");
	float x2 = getentityproperty(self,"x");
	float z1 = getentityproperty(target,"z");
	float z2 = getentityproperty(self,"z");
	float zz=z1-z2;
	float xx=x1-x2;
	if (zz<0){zz=-zz;}
	if (xx<0){xx=-xx;}
	if(z1-z2<=z && x1-x2<=x){
		changeentityproperty(self, "animation", openborconstant(ani));
	}
}
