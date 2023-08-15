void prepareJump()
{
	setlocalvar("xdir",getentityproperty(getlocalvar("self"),"xdir"));
}
void secJump(void jumpHeight)
{
	void xdir=getlocalvar("xdir");
	if(!getentityproperty(getlocalvar("self"),"direction")) xdir=-xdir;
	leaper(xdir,jumpHeight,0);
}
