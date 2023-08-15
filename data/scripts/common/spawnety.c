void spawnEntry(void vName,void hp,void map,void item,void dir)
{
	clearspawnentry();
	loadmodel(vName);
	setspawnentry("name", vName);
	setspawnentry("map",map);
	setspawnentry("health",hp);
	if(item&&item!="")
		setspawnentry("item",item);
	if(dir)
		setspawnentry("coords",-60,rand()%20+240);
	else
		setspawnentry("coords",530,rand()%20+240);
	void vSpawn=spawn();
	return vSpawn;
}
