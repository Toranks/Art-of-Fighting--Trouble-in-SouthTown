#include "data/scripts/common/spawnsty.c"
void triggerStory(char ani,int wait)
{
	void self=getlocalvar("self");
	char name=getentityproperty(self,"name");
	if (wait)
		if(!inScreen())return;
	spawnStory(name);
	if(wait){changeentityproperty(self,"animation",openborconstant(ani));}
}

void waitForStory(char story)
{
	if (!inScreen()){
		updateframe(getlocalvar("self"), 0);
		return;
	}
	spawnStory(story);
}
void inScreen()
{
	void self	=	getlocalvar("self");
	void x		=	getentityproperty(self,"x");
	void xpos	=	openborvariant("xpos");
	if(x>100+xpos&&x<xpos+380)
	{
		return 1;
	}else{
		return 0;
	}
}

