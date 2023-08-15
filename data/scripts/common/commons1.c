void slow(int swi)
{
	changeopenborvariant("slowmotion", swi);
}

void gravity(int Ratio)
{
    changeentityproperty(getlocalvar("self"),"antigravity", Ratio);
}
void looper(int Frame, int Limit)
{
    void self = getlocalvar("self");
    void loop = getlocalvar("Loop" + self);

    if(loop==NULL()){
      setlocalvar("Loop" + self, 0);
      loop = 0;
    } 
   
    if(loop < Limit){
		updateframe(self, Frame);
		setlocalvar("Loop" + self, loop+1);
	}else{
		setlocalvar("Loop"+self,NULL());
	}
}
