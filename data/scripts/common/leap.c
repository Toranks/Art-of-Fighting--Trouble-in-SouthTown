#include "data/scripts/common/spawnEnt.c"
void leap(float vy, float dx, float dz,void tossy)
{
	void self	=	getlocalvar("self");
	void target	=	findtarget(self);
	void tossx,tossz;
	if(target){
		void dir	=	getentityproperty(self,"direction");
		void x		=	getentityproperty(self, "x");
		void z		=	getentityproperty(self, "z");
		void Tx		=	getentityproperty(target, "x");
		void Tz		=	getentityproperty(target, "z");

		if (!dir)dx = -dx;
		spawnEnt("ring",Tx - openborvariant("xpos"),Tz);

		if(Tx < x)
			changeentityproperty(self, "direction", 0);
		else 
			changeentityproperty(self, "direction", 1);

		x = x+dx;
		z = z+dz;
		tossx=(Tx-x)/(22*vy);
		tossz=(Tz-z)/(22*vy);
		tossentity(self, tossy, tossx, tossz);
	}else{
		tossentity(self, 3, 0, 0);
	}
}
void leapToTarget(float vy,void tossy)
{
	leap(vy,0,0,tossy);
}

