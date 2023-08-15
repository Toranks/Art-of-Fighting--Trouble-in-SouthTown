
void main()
{
	void self = getlocalvar("self");
	void name = getentityproperty(self,"defaultname");
	int dx = getentityproperty(self, "x");
	int dy = getentityproperty(self, "a");
	int dz = getentityproperty(self, "z");
	void vShot;
	if (name == "lulcardx")
	{
	setindexedvar( "cardlul1", 0);
	float ccard = getindexedvar("cardlul1");
	ccard = ccard +1;
	setindexedvar( "cardlul1", ccard);
	vShot = projectile("lulcardx", dx, dz, dy, 1, 0, 50, 0);
	}
}