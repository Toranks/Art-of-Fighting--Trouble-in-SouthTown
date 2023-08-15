void target(float Velx, float Velz, float dx, float dz, int Stop)
{
	// Velx = x Velocity
	// Velz = z Velocity
	// dx = x added distance
	// dz = z added distance
	// Stop = flag to stop moving if no target is found
    void self = getlocalvar("self");
    int dir = getentityproperty(self, "direction");
    float x = getentityproperty(self, "x");
    float z = getentityproperty(self, "z");
	if (!dir){dx=-dx;}else{}
	void target=findtarget(self);
	if (target){
		float Tx = getentityproperty(target, "x");
		float Tz = getentityproperty(target, "z");
		if(Tx < x){
			changeentityproperty(self, "direction", 0);
		} else {
			changeentityproperty(self, "direction", 1);
		}
		x += dx;
		z += dz;
		float Disx = Tx - x;
		float Disz = Tz - z;
		if(Disx<0){Disx = -Disx;}
		if(Disz<0){Disz = -Disz;}
		if(Disz<Disx)
		{
			if(Tx < x){
				setlocalvar("x"+self, -Velx);
			}else{
				setlocalvar("x"+self, Velx);
			}
			setlocalvar("z"+self, Velx*(Tz-z)/Disx);
		}else{
			if(Tz < z){
				setlocalvar("z"+self, -Velz);
			}else{
				setlocalvar("z"+self, Velz);
			}
			setlocalvar("x"+self, Velz*(Tx-x)/Disz);
		}
	}else{
		setlocalvar("z"+self, 0);
		setlocalvar("x"+self, 0);
	}
}

void dash()
{
    void self = getlocalvar("self");
    float Vx = getlocalvar("x"+self);
    float Vz = getlocalvar("z"+self);
    if(Vx!=NULL()&&Vz!=NULL()){
		changeentityproperty(self, "velocity", Vx, Vz);
	}
}
