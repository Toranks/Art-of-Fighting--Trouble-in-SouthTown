void addScore(void ent,void score)
{
	if(getentityproperty(ent,"TYPE")==openborconstant("TYPE_PLAYER")){
		int  PIndex = getentityproperty(ent,"playerindex");
		int  PScore = getplayerproperty(PIndex, "score");
		changeplayerproperty(PIndex, "score", PScore+score);
	}
}
