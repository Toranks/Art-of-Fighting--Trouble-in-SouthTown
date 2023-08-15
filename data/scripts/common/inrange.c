int isInRange(void self,void target,int Rx, int Rz,int Ra)
{
	float Tx	=	getentityproperty(target, "x");
	float Tz	=	getentityproperty(target, "z");
	float Ta	=	getentityproperty(target, "a");
	int	dir		=	getentityproperty(self,"direction");
	float x		=	getentityproperty(self,"x");
	float z		=	getentityproperty(self,"z");
	float a		=	getentityproperty(self,"a");
	float Disx;
	float Disz = Tz - z;
	float Disa = Ta - a;

	if (!dir){
		Disx = x - Tx;
	}else{
		Disx = Tx - x;
	}

	if(Disz < 0){
		Disz = -Disz;
	}
	if(Disa < 0){
		Disa = -Disa;
	}
	
	if( Disx <= Rx && Disx>0 && Disz <= Rz && Disa<=Ra)
	{
		return 1;
	}else{
		return 0;
	}
}
