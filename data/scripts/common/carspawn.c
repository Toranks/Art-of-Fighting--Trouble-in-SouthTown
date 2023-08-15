void spawn01(void vName, float fX, float fY, float fZ)
{
	return spawnEntity(vName, fX, fY, fZ,0,0,0);
}
void spawnEntity(void vName, float fX, float fY, float fZ,int map,int bind,int pos)
{
	return spawnEntity01(vName, fX, fY, fZ,map,bind,pos,1);
}
void spawnEntity01(void vName, float fX, float fY, float fZ,int map,int bind,int pos,int owner)
{
	return spawnEntity02(vName,fX,fY,fZ,map,bind,pos,owner,NULL());
}
void spawnEntity02(void vName, float fX, float fY, float fZ,int map,int bind,int pos,int owner,void ani)
{
	return spawnEntity03(vName, fX,fY,fZ,map,bind,pos,owner,ani,1,1);
}
void spawnEntity03(void vName, float fX, float fY, float fZ,int map,int bind,int pos,int owner,void ani,int damage,int binddir)
{
	void self = getlocalvar("self");
	if(!self)return;else{}
	void vSpawn=spawnEn(vName);
	void reserved=openborconstant("TYPE_RESERVED");
	if(owner)
	{
		changeentityproperty(vSpawn, "owner", self);
		changeentityproperty(vSpawn, "hostile", getentityproperty(self, "hostile")+reserved);
		changeentityproperty(vSpawn, "candamage", getentityproperty(self, "candamage")+reserved);
	}
	changeentityproperty(vSpawn, "parent", self);
	if(bind){
		bindentity(vSpawn,self,fX,fZ,fY,binddir,0);
	}else{
		int iDirection = getentityproperty(self, "direction");
		if (!pos){
			if (!iDirection)fX=-fX;
			fX = fX + getentityproperty(self, "x");
			fY = fY + getentityproperty(self, "a");
			fZ = fZ + getentityproperty(self, "z");
		}else if(pos==1){
			iDirection=1;
			fX=fX+openborvariant("xpos");
			fY=fY+openborvariant("ypos");
		}else if(pos==2){
			if (iDirection){
				fX=fX+openborvariant("xpos");
			}else{
				fX=fX+openborvariant("xpos")+480;
			}
		}
	
		changeentityproperty(vSpawn, "direction", iDirection);
		if(pos==1)
			changeentityproperty(vSpawn, "position", fX, fY, fZ);
		else
			changeentityproperty(vSpawn, "position", fX, fZ, fY);
	}
	if (map>0){
		changeentityproperty(vSpawn, "map", map);
	}else if(map=-1){
		int cm=getentityproperty(self,"map");
		changeentityproperty(vSpawn,"map",cm);
	}
	if(ani)performattack(vSpawn,openborconstant(ani),0);
	return vSpawn;
}

void spawn02(void vName)
{
	return spawnEntity(vName,0,0,0,0,0,1);
}
void spawn03(void vName)
{
	return spawnEntity(vName,0,0,0,0,0,2);
}
void spawn_z(void vName,void offsetx,void offseta)
{
	void self = getlocalvar("self");
	void target=findtarget(self);
	void vSpawn;
	if(target!=NULL())
	{
		void dir=getentityproperty(self,"direction");
		void Tx = getentityproperty(target, "x");
		void Tz = getentityproperty(target, "z");
		if(!dir)offsetx=-offsetx;
		clearspawnentry();
		setspawnentry("name", vName);
		vSpawn=spawn();
		changeentityproperty(vSpawn, "candamage", getentityproperty(self, "candamage")+openborconstant("TYPE_RESERVED"));
		changeentityproperty(vSpawn, "position", Tx+offsetx, Tz, offseta);
		changeentityproperty(vSpawn, "direction",dir);
	}
	return vSpawn;
}

void spawnEn(void vName)
{
	clearspawnentry();
	setspawnentry("name", vName);
	void vSpawn=spawn();
	return vSpawn;
}
