#include "data/scripts/common/spawn.c"
void shoot(void Shot, float dx, float dy, float dz)
{ // Shooting projectile
	void self = getlocalvar("self");
	int Direction = getentityproperty(self, "direction");
	int x = getentityproperty(self, "x");
	int y = getentityproperty(self, "a");
	int z = getentityproperty(self, "z");

	if (!Direction)
	{
		dx = -dx;
	}else{}

	void vSpawn=projectile(Shot, x+dx, z+dz, y+dy, Direction, 0, 0, 0);
}
void tosser(void Bomb, float dx, float dy, float dz, float Vx, float Vy, float Vz)
{
	void self = getlocalvar("self");
	int Direction = getentityproperty(self, "direction");
	int x = getentityproperty(self, "x");
	int y = getentityproperty(self, "a");
	int z = getentityproperty(self, "z");
	if (!Direction){
		Vx=-Vx;
	}else{}
	void Shot = spawnEntity03(Bomb,dx,dy,dz,0,0,0,0,"",0,1);
	changeentityproperty(Shot, "parent", self);
	tossentity(Shot, Vy, Vx, Vz);
}
void shoot2(void Shot, float dx, float dy, float dz,float vx, float vy, float vz)
{ // Shooting projectile
	void self = getlocalvar("self");
	int Direction = getentityproperty(self, "direction");
	int x = getentityproperty(self, "x");
	int y = getentityproperty(self, "a");
	int z = getentityproperty(self, "z");

	if (Direction == 0){ //Is entity facing left?                  
	  dx = -dx; //Reverse X direction to match facing
	}else{}
	void vSpawn=projectile(Shot, x+dx, z+dz, y+dy, Direction, 0, 1, 0);
	changeentityproperty(vSpawn,"speed",vx);
	changeentityproperty(vSpawn,"velocity",vx,vz,vy);
}
