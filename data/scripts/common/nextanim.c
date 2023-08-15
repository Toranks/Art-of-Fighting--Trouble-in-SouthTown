void nextAnim(void ent,void time)
{
	int enextanim = getentityproperty(ent, "nextanim");
	int enextthink = getentityproperty(ent, "nextthink");
	changeentityproperty(ent, "nextanim", enextanim + 80);
	changeentityproperty(ent, "nextthink", enextthink + 80);
}