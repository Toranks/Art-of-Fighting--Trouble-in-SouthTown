#define	MODEL_NAME 2
#define	SELECTABLE 4
void setValid(void name,void isselectable)
{
	int i;
	int maxents=100;
	for(i=0;i<maxents;i++)
	{
		if(getmodelproperty(i,MODEL_NAME)==name)
		{
			changemodelproperty(i,SELECTABLE,isselectable);
			return;
		}
	}
}
