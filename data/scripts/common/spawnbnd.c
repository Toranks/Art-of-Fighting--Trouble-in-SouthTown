void spawnBind(void vName, void ani,float fX, float fY)
{
	void spawn=spawnEntity(vName,fX,fY,1,0,1,0);
	setlocalvar("bindf",spawn);
	if(ani!="")changeentityproperty(spawn,"animation",openborconstant(ani));
}
void adjust(void x,void y,void frame)
{
	void target=getlocalvar("bindf");
	if(target)
	{
		updateframe(target,frame);
		bindentity(target, getlocalvar("self"), x, 1, y, 1, 0);
	}
}
void unBind()
{
	void target=getlocalvar("bindf");
	if(target)
	{
		bindentity(target,NULL());
		killentity(target);
	}
}
