void isCN()
{
	return openborvariant("current_set")>0;
}
void getPath()
{
	if(isCN())
		return "CN";
	else
		return "EN";
}
