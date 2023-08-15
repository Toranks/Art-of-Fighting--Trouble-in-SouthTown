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

	if (getentityproperty(self,"type")==openborconstant("type_player"))
	{
		changeentityproperty(vSpawn,"candamage","type_enemy","type_obstacle");
	}else if(getentityproperty(self,"type")==openborconstant("type_enemy"))
	{
		changeentityproperty(vSpawn,"candamage","type_player","type_npc");
	}
}
void tosser(void Bomb, float dx, float dy, float dz, float Vx, float Vy, float Vz)
{
	void self = getlocalvar("self");
	int Direction = getentityproperty(self, "direction");
	int x = getentityproperty(self, "x");
	int y = getentityproperty(self, "a");
	int z = getentityproperty(self, "z");
	if (!Direction){
		dx=-dx;
	}else{}
	void Shot = projectile(Bomb, x+dx, z+dz, y+dy, Direction, 0, 1, 0);
	changeentityproperty(Shot, "parent", self);
	tossentity(Shot, Vy, Vx, Vz);
	changeentityproperty(Shot, "speed", Vx); 
	changeentityproperty(Shot, "hostile", getentityproperty(self, "hostile")+openborconstant("TYPE_RESERVED"));
	changeentityproperty(Shot, "candamage", getentityproperty(self, "candamage")+openborconstant("TYPE_RESERVED"));
}
void shoot2(void Shot, float dx, float dy, float dz,float vx, float vy, float vz)
{
	void self = getlocalvar("self");
	int Direction = getentityproperty(self, "direction");
	int x = getentityproperty(self, "x");
	int y = getentityproperty(self, "a");
	int z = getentityproperty(self, "z");
	if (!Direction){
	  dx = -dx;
	}else{}
	void vSpawn=projectile(Shot, x+dx, z+dz, y+dy, Direction, 0, 1, 0);
	changeentityproperty(vSpawn,"speed",vx);
	changeentityproperty(vSpawn,"velocity",vx,vz,vy);
	changeentityproperty(vSpawn, "hostile", getentityproperty(self, "hostile")+openborconstant("TYPE_RESERVED"));
	changeentityproperty(vSpawn, "candamage", getentityproperty(self, "candamage")+openborconstant("TYPE_RESERVED"));
}
