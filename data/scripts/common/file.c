void saveSetting(void value)
{
	void pakname=openborvariant("pakname");
	void file=createfilestream();
	filestreamappend(file,value,1);
	savefilestream(file,"save.s");
	closefilestream(file);
}
void loadSetting(void fn)
{
	void pakname=openborvariant("pakname");
	//void file=openfilestream("saves/"+pakname+"/"+fn);
	void file=openfilestream(fn,1);
	void ret;
	if(file==-1)
	{
		return 0;
	}else{
		ret=getfilestreamargument(file, 0, "int");
		closefilestream(file);
		return ret;
	}
}
