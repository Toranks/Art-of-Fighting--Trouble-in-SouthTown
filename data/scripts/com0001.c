

//void test(){
//     
//     int iRnd = rand()%2+1;
//     void vSelf = getlocalvar("self"); //Get calling entity. 
//        
//     //setglobalvar("test",iRnd); //Set flag.
//    
//}
//
//void test0002(void vAni){
//     
//     int iRnd = rand()%2+1;
//     void vSelf = getlocalvar("self"); //Get calling entity. 
//        
//     int iAni = openborconstant(vAni);
//
//     if (iAni){
//         performattack(vSelf, iAni);
//     }    
//}

void ai0001(void vAI1, int iAI1, void vAI2, int iAI2){
     
    /*
    ani001
    Damon Vaughn Caskey
    11/13/2007

    Switch caller to new AI mode.

    vAI#: AI Flag.
    iAI#: AI flag state.
    */
         
    void vSelf = getlocalvar("self"); //Get calling entity. 
        
    changeentityproperty(vSelf, "aiflag", vAI1, iAI1);   //Set flag.
    //changeentityproperty(vSelf, "aiflag", vAI2, iAI2); //Set flag.
      
}

void ani0001(void vModel, void vAni1, int iFrame1, void vAni2, int iFrame2, int iCmd, int iAIChance, int iHPCost, int iMPCost){

    /*
	ani001
	Damon Vaughn Caskey
	05/11/2007
	
	Switch calling entity to new animation and frame if command (or random chance if AI controlled) and status requirements are met.
	
	vAni1: Desired animation.
	iFrame: Desired frame.
	iCmd: Required key command when entity is under player control.
    iAIChance: Chance of animation change under AI control. 100 = always, 1 = almost never.
    iMPCost: Required MPCost.
    iHPCost: Required HPCost.
    */
	
    void vSelf     = getlocalvar("self");                //Calling entity. 
    int  iType     = getentityproperty(vSelf, "type");   //Caller type.
    int  iHP       = getentityproperty(vSelf, "health"); //Caller current HP.
    int  iMP       = getentityproperty(vSelf, "mp");     //Caller current MP.
    void vCurModel = getentityproperty(vSelf, "model");  //Current model name.
    int  iRMP;
    
    //Model requirement met?
    //if (vModel && vModel != vCurModel){ return; }
    
    //Player control?
    if(iType == openborconstant("TYPE_PLAYER"))
    {    
        if (iCmd && keyd001(getentityproperty(vSelf, "playerindex"), 0, vSelf) != iCmd) { return; } //Does command match? If not exit.		    		
    
    //AI control? Compare random 1-100 against iAIChance. If random is higher, exit.
    }else if(iAIChance)
    {     
        int iRand = (rand() % 100);            //Get a random number.
        if (iRand > 0) { iRand = -iRand; }     //Don't ask me why, but rand * 100 is not like C. Here it can still return negtaive after being modded. To fix this, we just insure the integer is ALWAYS negative, and adapt our routine accordingly.
        if (iRand < -iAIChance) { return; }    //If random number is less then AIChance, exit.          
    }
    
    //If Cost is a negative number, we are checking for resource BELOW Cost and not above. To save a paremeter we differentiate by passing a negative Cost and reversing evaluation.       
    if (iMPCost < 0)
    {   
        iRMP = -iMP;        
        
        //If iMP is less then iHPCost (same as if Resource < Cost if positive) runalternate and or exit.  
        if (iRMP < iMPCost)
        { 
           if (vAni2)
           {           
              changeentityproperty(vSelf, "animation", openborconstant(vAni2)); //Switch to alternate animation.
              //updateframe(vSelf, iFrame2);                                    //Switch to alternate frame.                                                                                  
           }
           return -1;        
        }        
        iMPCost = 0;  
    }
    else if(iMPCost > 0)
    {        
		if (iMPCost > iMP)
        {
           if (vAni2)
           {           
              changeentityproperty(vSelf, "animation", openborconstant(vAni2)); //Switch to alternate animation.
              //updateframe(vSelf, iFrame2);                                    //Switch to alternate frame.                                                                                                   
           }
           return -1;
        }
    }
	
    //If Cost is a negative number, we are checking for resource BELOW Cost and not above. To save a paremeter we differentiate by passing a negative Cost and reversing evaluation.                        
    if (iHPCost < 0)
    {      
       //If iHP is less then iHPCost (same as if Resource < Cost if positive) runalternate and or exit.  
       if (-iHP < iHPCost)
       {  
          if (vAni2){           
              changeentityproperty(vSelf, "animation", openborconstant(vAni2)); //Switch to alternate animation.
              //updateframe(vSelf, iFrame2);                                    //Switch to alternate frame.                                                                                  
          }
       return -1;        
       }        
       iHPCost = 0;  
    }
    else if(iHPCost > 0)
    {
		if (iHPCost > iHP)
        {
           if (vAni2)
           {           
              changeentityproperty(vSelf, "animation", openborconstant(vAni2)); //Switch to alternate animation.
              //updateframe(vSelf, iFrame2);                                    //Switch to alternate frame.                                                                                  
           }
           return -1;
        }
    }

    changeentityproperty(vSelf, "health", iHP - iHPCost); //Apply HP cost.
    changeentityproperty(vSelf, "mp", iMP - iMPCost);     //Apply MP cost.
	
	if (vAni1)
    { 
        changeentityproperty(vSelf, "animation", openborconstant(vAni1)); //Switch to alternate animation.
        //updateframe(vSelf, iFrame1);                                    //Switch to desired frame.
    }                                    
        
}

void ani0002(int iFrame1){

    /*
	ani001
	Damon Vaughn Caskey
	05/11/2007
	Loop calling entity back to desired frame if below max MP (for charge animation).
    	
	iFrame: Desired frame.
	*/
	
	void vSelf  = getlocalvar("self");                  //Calling entity. 
    int  iMP    = getentityproperty(vSelf, "mp");       //Caller current MP.
    int  iMaxMP = getentityproperty(vSelf, "maxmp");    //Caller current MP.
	
	if (iMP < iMaxMP){ updateframe(vSelf, iFrame1); }
	
}

void ani0003(void vModel, void vAni1, int iFrame1, float fXMin, float fXMax, float fYMin, float fYMax, float fZMin, float fZMax){

    /*
	ani001
	Damon Vaughn Caskey
	05/11/2007
	
	Switch calling entity to new animation and frame if range requirements are met.
	
	vAni1: Desired animation.
	iFrame: Desired frame.
	fXMin, fYMin, fZMin: Minimum X, Y, and Z ranges.
    fXMax, fYMax, fZMax: Maximum X, Y, and Z ranges.
    */
	
    void  vSelf     = getlocalvar("self");                  //Calling entity. 
    void  vTarget   = findtarget(vSelf);                    //Caller type.
    float fX        = getentityproperty(vSelf, "x");        //Caller X location.
    float fY        = getentityproperty(vSelf, "a");        //Caller Y location.
    float fZ        = getentityproperty(vSelf, "z");        //Caller Z location.
    float fTX       = getentityproperty(vTarget, "x");      //Target X location.
    float fTY       = getentityproperty(vTarget, "a");      //Target Y location.
    float fTZ       = getentityproperty(vTarget, "z");      //Target Z location.
	void  vCurModel = getentityproperty(vSelf, "model");    //Current model name.
	
	//Model requirement met?
    if (vModel && vModel != vCurModel){ return; }
    	
    //Outside any provided range? If so, exit.
	if (iRan001(fX, fTX, fXMin, fXMax) != 1) { return; }
	if (iRan001(fZ, fTZ, fZMin, fZMax) != 1) { return; }
	if (iRan001(fY, fTY, fYMin, fYMax) != 1) { return; }
	                
	performattack(vSelf, openborconstant(vAni1), 1);   //Switch to desired animation.
    if (iFrame1){ updateframe(vSelf, iFrame1); }       //Switch to desired frame.
        
}

void ani0004(void vAni, int iFrame){

    /*
	ani0004
	Damon Vaughn Caskey
	04/01/2008
	Force opponent entity to play animation.

    vTar: Target entity.
    vAni: Desired animation.    	
	iFrame: Desired frame.
	*/
	
	void vSelf   = getlocalvar("self");                     //Calling entity. 
    void vTarget = getentityproperty(vSelf, "opponent");    //Target entity.

	changeentityproperty(vTarget, "animation", openborconstant(vAni)); //Switch to desired animation.    	
    updateframe(vTarget, iFrame);

}

void ani0005(){

    /*
	ani0005
	Damon Vaughn Caskey
	05/10/2008
	Play animation in "animation" global var if it exists. 
	
	This function is more or less to get around an issue where changing animation on the same frame a hit 
    occurs instantly crashes the game.
    
	*/
	
	void vSelf = getlocalvar("self");       //Calling entity. 
    int  vAni  = getentityvar(vSelf, 3);    //Get animation varible.

    if (vAni)
    {
	   performattack(vSelf, openborconstant(vAni), 1);     //Switch to desired animation.    	
       setentityvar(vSelf, 3, NULL());                     //Clear variable.
    }
}

void ani0006(int iSkip, int iReps){
     
     /*
     ani0006
     Damon Vaughn Caskey
     05/11/2008
     Skip back or forward to specified frame.
     
     iSkip: Number of frames to fall back (or forward).
     iReps: How many times to skip or fall back. 0 = Infinity.
     */
     
     void vSelf = getlocalvar("self");                  //Calling entity.
     int iFrame = getentityproperty(vSelf, "animpos");  //Caller's frame.
     
     updateframe(vSelf, iFrame + iSkip);                     //Switch to desired frame.
     
}     

void autodraw(void vTarget){
            
    /*
    Autodraw()
    Damon Vaughn Caskey
    01/25/2008
    Applies requested draweffects and autozoom to all valid entities. The overall effect is to cause an entity to shirink as it
    moves "away" from the player's viewpoint and expand as it moves toward the player's vantage, similar to many Neo-Geo games.
    
    1. Iterates though all entities calculates a zoom ratio based on Z location (Entitys that are invalid (probably dead), have
    a "skip flag" (entityvar 15), or panel type are skipped.
    2. Zoom ratio is stored as entity variable for later use, and applied to ScaleX/ScaleY parameters of setdrawmthod for entity.
    3. Because this is a looping function, any other attempts at using setdrawmethod would be overidden. Therfore values
    are taken and applied from entity variables stored by other functions to control other setdrawmethod parameters including manual
    adjustment of scale values if desired.
    4. Autozoom variance is controlled by fMinZ * X. By changing the value of fMax, it is also possible to change the Z location in
    which entity is shown at its normal size.
    */
    
    void  vParent;                                                      //Parent of entity.
    int   iEntity;                                                      //Entity enumeration (for loop).
    int   iType      = getentityproperty(vTarget, "type");              //Entity type.
    float fScaleX;                                                      //X scale adjustment.
    float fScaleY;                                                      //Y scale adjustment.
    int   iFlipX;                                                       //Flip X.
    int   iFlipY;                                                       //Flip Y.
    int   iShiftX;                                                      //Shift X.
    int   iBlend;                                                       //Transparency.
    int   iRemap;                                                       //Remap palette.
    int   iFill;                                                        //Color fill.
    int   iRotate;                                                      //Rotation.
    int   iAni;                                                         //Animation bind.
    int   iFrameB;                                                      //Frame bind.
    int   iFrame;                                                       //Parent frame placeholder.
    int   iMax       = openborvariant("ent_max");                       //Number of entities present.    
    float fMinZ      = openborconstant("PLAYER_MIN_Z") * 1.08;          //Minimum Z location * Zoom factor.                                       
    float fDeltaZ    = (openborconstant("PLAYER_MAX_Z")-20) - fMinZ;    //Range betwen fMinZ and MaxZ                                            
    float fFactor;                                                      //Autozoom calculation placeholder.
                    
        
    //Is the entity valid, not set to be skipped (entityvar 15), and alive?
    if(vTarget && getentityproperty(vTarget, "exists") && !getentityvar(vTarget, 15)){
                                   
        fFactor  = getentityproperty(vTarget, "z") - fMinZ; //Distance of caller from fMinZ.
        fFactor /= fDeltaZ;                                 //Resolve float value.
        fFactor *= 0.1;                                     //Set scale to .9 thru 1
        fFactor += 0.9;                                     //Resolve %.
        setentityvar(vTarget, 14, fFactor);                 //Store scale ratio for use by sub entity (shooting, spawning, binding etc.) functions.
        fFactor *= 256;                                     //% of maximum size.
        
        //Only going to use none for flashes and sparks, which will never have live adjustments besides autozoom.
        if (iType == openborconstant("TYPE_NONE")){
            setdrawmethod(vTarget, 1, fFactor, fFactor, 0, 0, 0, 0, -1, 0, 0);  //Set final values to drawmethod.
        }else{
                            
            fScaleX = getentityvar(vTarget, 5);   //Y scale adjustment.                
            fScaleY = getentityvar(vTarget, 6);   //Y scale adjustment.
            iFlipX  = getentityvar(vTarget, 7);   //Flip X.
            iFlipY  = getentityvar(vTarget, 8);   //Flip Y.
            iShiftX = getentityvar(vTarget, 9);   //Shift X.
            iBlend  = getentityvar(vTarget, 10);  //Blend.
            iRemap  = getentityvar(vTarget, 11);  //Remap.
            iFill   = getentityvar(vTarget, 12);  //Fill.
            iRotate = getentityvar(vTarget, 13);  //Rotate.
            
            //If ScaleX Adjustment provided, apply it with autozoom factor.
            if (fScaleX){
                fScaleX = autodraw0002(fFactor, fScaleX); 
            }else{
                fScaleX = fFactor;
            }

            //If ScaleY Adjustment provided, apply it with autozoom factor.
            if (fScaleY){
                fScaleY = autodraw0002(fFactor, fScaleY);
            }else{
                fScaleY = fFactor; 
            }

            //If Values are not available, apply defaults.
            if (!iFlipX)  { iFlipX  = 0; }                        //FlipX.
            if (!iFlipY)  { iFlipY  = 0; }                        //FlipY.
            if (!iShiftX) { iShiftX = 0; }                        //ShiftX.
            if (!iBlend)  { iBlend  = 0; }                        //Alpha.
            if (!iRemap)  { iRemap  = -1; }                       //Remap.
            if (!iFill)   { iFill   = 0; }                        //Fill.
            if (!iRotate) { iRotate = 0; }                        //Fill.
        
            setdrawmethod(vTarget, 1, fScaleX, fScaleY, iFlipX, iFlipY, iShiftX, iBlend, iRemap, iFill, iRotate);  //Set final values to drawmethod.
        }
    }       
}

int autodraw0002(float fRatio, float fVector){    

    /*
    autodraw0002
    Damon Vaughn Caskey
    05/30/2008
    Returns whole integer from incoming location vector after applying fRatio. Primarly for integrating scaling (see Autodraw0001)
    with bind function (which must be given whole numbers for location offsets).

    fRatio: Ratio to apply. WIll almost always be the current scale ratio of a caller.
    fVector:   Vector to be scaled and rounded.
    */

    int iNeg = 0; //Negative flag.
    
    //Negative number? If so, the conversions below won't work. Temporarily convert to positive integer.
    if (fVector < 0){
        iNeg    = 1;            //Set negative flag.
        fVector = fVector * -1; //Convert to positive integer.
    }

    fVector += 0.0;                //Vector must be a float, convert here to make sure.
    fVector *= fRatio;             //Apply scale ratio.
    fVector %= (++fVector);        //Remove decimal (binds fail if not passed a whole integer).
    if (!fVector) { fVector = 1; } //If calculation produces 0, set to 1.
    
    //Vector was a temporary posative. Convert back to negative.
    if (iNeg){
        fVector = -fVector; //Convert to negative integer.
    }

    return fVector; //Return value.
}

void autodraw0003(float iScaleX, float iScaleY, int iFlipX, int iFlipY, int iShiftX, int iBlend, int iRemap, int iFill, int iRotate){

     /*
     draw0002
     Damon Vaughn Caskey
     01/25/2008
     Sets passed drawmethod parameters to caller.
     */
     
     void vSelf = getlocalvar("self"); //Caller.
     
            
     setentityvar(vSelf, 5, iScaleX);  //iScaleX adjustment.
     setentityvar(vSelf, 6, iScaleY);  //iScaleY adjustment.
     setentityvar(vSelf, 7, iFlipX);   //Flip X.
     setentityvar(vSelf, 8, iFlipY);   //Flip Y.
     setentityvar(vSelf, 9, iShiftX);  //Shift X.
     setentityvar(vSelf, 10, iBlend);  //Alpha.
     setentityvar(vSelf, 11, iRemap);  //Remap.
     setentityvar(vSelf, 12, iFill);   //Fill color.
     setentityvar(vSelf, 13, iRotate); //Rotate.
        
}   

void bind0001(int iX, int iY, int iZ, int iDir, int iAniFlag){
     
     /*
     bind0001
     Damon Vaughn Caskey
     02/11/2008
     Bind caller to parent.
     
     iX, iY, iZ: Location offsets.
     iDir:       Direction - 0 = no change, 1 = same target, -1 = opposite of target,  2 = right, -2 = left.
     iAniFlag:   See http://www.lavalit.com/index.php?topic=963.msg14445#msg14445
     */

     void  vSelf   = getlocalvar("self");                //Caller.
     void  vParent = getentityproperty(vSelf, "parent"); //Caller parent.
     float fRatio  = getentityvar(vParent, 14);
     
     if (!fRatio) { fRatio = 1; }
     
     iX *= fRatio;
     iY *= fRatio;
         
     bindentity(vSelf, vParent, iX, iZ, iY, iDir, iAniFlag);  //Execute bind.     

}

void bind0002(float fX, float fY, float fZ){
    
    /*
    bind0002
	Damon Vaughn Caskey
	06/20/2007
	Syncronizes target with caller's location.
	
	iSync:      Sync target setting (see vTar001 function).
	fX, fY, fZ: Distance adjustment (from caller).
	iDirection: Direction adjustment (see loc001 function).
    */

    void  vSelf   = getlocalvar("self");                     //Calling entity.
    void  vTarget = getentityproperty(vSelf, "opponent");    //Current opponent.
    int   iDir    = getentityproperty(vTarget, "direction"); //Current direction.
    float fRatio  = getentityvar(vSelf, 14);                 //Caller's current scale ratio.

    if (iDir == 1){ //Target facing left?             
         fX = -fX;  //Reverse horizontal adjustment.             
    }
    
    fX = (fX + getentityproperty(vSelf, "x")) * fRatio; //Apply requested X offset to X location and apply zoom scale.
    fY = (fY + getentityproperty(vSelf, "a")) * fRatio; //Apply requested Y offset to Y location and apply zoom scale.
    fZ = fZ + getentityproperty(vSelf, "z");            //Apply requested Z offset.

    changeentityproperty(vTarget, "position", fX, fZ, fY);    
}

void bind0003(void vName, void vAlias, void vMap, int iBlend, int iX, int iY, int iZ, int iDir, int iAniFlag){
	
    /*
     bind0003
     Damon Vaughn Caskey
     02/25/2008
     Spawn an entity and then bind it to caller.
     
     vName:      Model name of spawn.
     vAlias:     Display name of spawn. 
     vMap:       Color map of spawn.
     iBlend:     Transparency setting of spawn. 
     fX, fY, fZ: Location offset of binding.
     iDir:       Direction - 0 = no change, 1 = same target, -1 = opposite of target,  2 = right, -2 = left.
     iAniFlag:   See http://www.lavalit.com/index.php?topic=963.msg14445#msg14445
     */
    
    void  vSpawn;
    void  vSelf  = getlocalvar("self");                    //Caller.
    float fRatio = getentityvar(vSelf, 14);                //Caller's current scale ratio.
    float fX     = getentityproperty(vSelf, "x") * fRatio; //Caller X location.
    float fZ     = getentityproperty(vSelf, "z");          //Caller Z location.
    float fY     = getentityproperty(vSelf, "a") * fRatio; //Caller A location.
    
    clearspawnentry();                    //Clear current spawn entry.
    setspawnentry("name", vName);         //Aquire spawn entity by name.
    setspawnentry("alias", vAlias);       //Set alias.
	setspawnentry("map", vMap);           //Set color remap.
	setspawnentry("coords", fX, fZ, fY);  //Spawn location.
    vSpawn = spawn();                     //Spawn entity.
    clearspawnentry();                    //Clear current spawn entry.
    spaw0001(vSpawn, 0, 0);                  //Clean autodraw adjustments.
    
    setentityvar(vSelf, 20, vSpawn);      //Store spawn.

    changeentityproperty(vSpawn, "parent", vSelf);         //Set caller as parent of spawn.
    changeentityproperty(vSpawn, "alpha", iBlend);         //Apply requested transparency setting.               
    
    setentityvar(vSpawn, 10, iBlend);  //Set transparency.
    setentityvar(vSpawn, 11, vMap);  //Set remap.

    //Bind X?
    if (iX){
        iX = autodraw0002(fRatio, iX); //Apply scaling to fX.
    }else{
        iX = NULL();
    }

    //Bind Y?
    if (iY){
        iY = autodraw0002(fRatio, iY); //Apply scaling to fY.
    }else{
        iY = NULL();
    }

    if (!iZ) { iZ = NULL(); }
        
    bindentity(vSpawn, vSelf, iX, iZ, iY, iDir, iAniFlag); //Execute bind.

    return vSpawn;
}

void bind0004(void vTar, int iX, int iY, int iZ, int iDir, int iAniFlag){
     
     /*
     bind0004
     Damon Vaughn Caskey
     03/12/2008
     Bind target to caller.
     
     vTar:       Target entity. See vTar001 function.
     iX, iY, iZ: Location offsets.
     iDir:       Direction - 0 = no change, 1 = same target, -1 = opposite of target,  2 = right, -2 = left.
     iAniFlag:   See http://www.lavalit.com/index.php?topic=963.msg14445#msg14445
     */

     void  vSelf   = getlocalvar("self");           //Calling entity.
     void  vTarget = vTar001(vTar, vSelf);          //Target entity.
     float fRatio  = getentityvar(vSelf, 14);       //Caller's current scale ratio.
     
     if (iDir == 11){
         bindentity(vTarget, NULL());                 
     }else{

         //Bind X?
         if (iX){
             iX = autodraw0002(fRatio, iX); //Apply scaling to fX.
         }
         //Bind Y?
         if (iY){
             iY = autodraw0002(fRatio, iY); //Apply scaling to fY.
         }        

         bindentity(vTarget, vSelf, iX, iZ, iY, iDir, iAniFlag); //Execute bind.
     }
}

void bind0005(void vName, void vAlias, void vMap, int iBlend, float fX, float fY, float fZ, void vAni, int iFrame){
	
    /*
     bind0005
     Damon Vaughn Caskey
     02/25/2008
     Spawn an entity and then bind its animations to caller through autodraw().
     
     vName:      Model name of spawn.
     vAlias:     Display name of spawn. 
     vMap:       Color map of spawn.
     iBlend:     Transparency setting of spawn. 
     fX, fY, fZ: Location offset of spawn.
     iDir:       Direction - 0 = no change, 1 = same target, -1 = opposite of target,  2 = right, -2 = left.
     iAniFlag:   See http://www.lavalit.com/index.php?topic=963.msg14445#msg14445
     */
    
    void  vSpawn;
    void  vSelf  = getlocalvar("self");                     //Caller.
    float fRatio = getentityvar(vSelf, 14);                 //Caller's current scale ratio.
    
    fX     = (getentityproperty(vSelf, "x") + fX) * fRatio; //Caller X location.
    fZ     = getentityproperty(vSelf, "z");                 //Caller Z location.
    fY     = (getentityproperty(vSelf, "a") + fY) * fRatio; //Caller A location.
    
    clearspawnentry();                    //Clear current spawn entry.
    setspawnentry("name", vName);         //Aquire spawn entity by name.
    setspawnentry("alias", vAlias);       //Set alias.
	setspawnentry("map", vMap);           //Set color remap.
	setspawnentry("coords", fX, fZ, fY);  //Spawn location.
    vSpawn = spawn();                     //Spawn entity.
    clearspawnentry();                    //Clear current spawn entry.
    spaw0001(vSpawn, 0);                  //Clean autodraw adjustments.
    
    setentityvar(vSelf, 20, vSpawn);      //Store spawn.

    changeentityproperty(vSpawn, "parent", vSelf);         //Set caller as parent of spawn.
    changeentityproperty(vSpawn, "alpha", iBlend);         //Apply requested transparency setting.               
    //changeentityproperty(vSpawn, "velocity", 0, 0, 0);
    //setentityvar(vSpawn, 16, openborconstant(vAni));      
       
}

void bind0006(void vName, void vAlias, void vMap, int iBlend, int iX, int iY, int iZ, int iDir, int iAniFlag, float fScaleX, float fScaleY, int iFlipX, int iFlipY, int iShiftX, int iFill, int iRotate){
	
    /*
     bind0003
     Damon Vaughn Caskey
     02/25/2008
     Performs bind0003 functions and adds autodraw adjustments.
     
     vName:      Model name of spawn.
     vAlias:     Display name of spawn. 
     vMap:       Color map of spawn.
     iBlend:     Transparency setting of spawn. 
     fX, fY, fZ: Location offset of binding.
     iDir:       Direction - 0 = no change, 1 = same target, -1 = opposite of target,  2 = right, -2 = left.
     iAniFlag:   See http://www.lavalit.com/index.php?topic=963.msg14445#msg14445
     */

     void vTarget = bind0003(vName, vAlias, vMap, iBlend, iX, iY, iZ, iDir, iAniFlag);
            
     setentityvar(vTarget, 5, fScaleX);  //iScaleX adjustment.
     setentityvar(vTarget, 6, fScaleY);  //iScaleY adjustment.
     setentityvar(vTarget, 7, iFlipX);   //Flip X.
     setentityvar(vTarget, 8, iFlipY);   //Flip Y.
     setentityvar(vTarget, 9, iShiftX);  //Shift X.
     setentityvar(vTarget, 12, iFill);   //Fill color.
     setentityvar(vTarget, 13, iRotate); //Rotate.
        
}

void bind0007(void vName, void vAlias, void vMap, int iBlend, int iX, int iY, int iZ, int iDir, int iAniFlag, float fScaleX, float fScaleY, int iFlipX, int iFlipY, int iShiftX, int iFill, int iRotate){
	
    /*
     bind0003
     Damon Vaughn Caskey
     02/25/2008
     Performs bind0006 funtions and kills caller; primarly for fatalities.
     
     vName:      Model name of spawn.
     vAlias:     Display name of spawn. 
     vMap:       Color map of spawn.
     iBlend:     Transparency setting of spawn. 
     fX, fY, fZ: Location offset of binding.
     iDir:       Direction - 0 = no change, 1 = same target, -1 = opposite of target,  2 = right, -2 = left.
     iAniFlag:   See http://www.lavalit.com/index.php?topic=963.msg14445#msg14445
     */

     void vSelf = getlocalvar("Self"); //Caller.

     killentity(vSelf);
     bind0006(vName, vAlias, vMap, iBlend, iX, iY, iZ, iDir, iAniFlag, fScaleX, fScaleY, iFlipX, iFlipY, iShiftX, iFill, iRotate);

}

void bind0008(void vName, void vAlias, void vMap, int iBlend, int iX, int iY, int iZ, int iFlip){
	
    /*
     bind0003
     Damon Vaughn Caskey
     02/25/2008
     Spawn an entity, place it in location with relation to caller, but do not bind.
     
     vName:      Model name of spawn.
     vAlias:     Display name of spawn. 
     vMap:       Color map of spawn.
     iBlend:     Transparency setting of spawn. 
     fX, fY, fZ: Location offset.
     iDir:       Direction - 0 = no change, 1 = same target, -1 = opposite of target,  2 = right, -2 = left.
     */
    
    void  vSpawn;
    void  vSelf  = getlocalvar("self");                    //Caller.
    float fRatio = getentityvar(vSelf, 14);                //Caller's current scale ratio.
    float fX     = getentityproperty(vSelf, "x") * fRatio; //Caller X location.
    float fZ     = getentityproperty(vSelf, "z");          //Caller Z location.
    float fY     = getentityproperty(vSelf, "a") * fRatio; //Caller A location.
    int   iDir   = getentityproperty(vSelf, "direction");  //Caller's facing.

    clearspawnentry();                    //Clear current spawn entry.
    setspawnentry("name", vName);         //Aquire spawn entity by name.
    setspawnentry("alias", vAlias);       //Set alias.
	setspawnentry("map", vMap);           //Set color remap.
	setspawnentry("coords", fX, fZ, fY);  //Spawn location.
    vSpawn = spawn();                     //Spawn entity.
    clearspawnentry();                    //Clear current spawn entry.
    spaw0001(vSpawn, 0, 0);                  //Clean autodraw adjustments.
    
    setentityvar(vSelf, 20, vSpawn);      //Store spawn.

    changeentityproperty(vSpawn, "parent", vSelf);         //Set caller as parent of spawn.
    changeentityproperty(vSpawn, "alpha", iBlend);         //Apply requested transparency setting.               
    
    setentityvar(vSpawn, 10, iBlend);  //Set transparency.
    setentityvar(vSpawn, 11, vMap);  //Set remap.

    if (iFlip){
        if (iDir){
            iDir = 0;
        }else{
            iDir = 1;            
        }
    }
    
    if (iDir) {iX = -iX;}

    //Bind X?
    if (iX){
        iX = autodraw0002(fRatio, iX); //Apply scaling to fX.
    }else{
        iX = NULL();
    }

    //Bind Y?
    if (iY){
        iY = autodraw0002(fRatio, iY); //Apply scaling to fY.
    }else{
        iY = NULL();
    }

    if (!iZ) { iZ = NULL(); }
        
    changeentityproperty(vSpawn, "position", fX + iX, fZ + iZ, fY + iY); //Set location of spawn.

    return vSpawn;
}

void dama0001(void vTar, int iHP, int iDrop, void vType, int iDir, float fY, float fX, float fZ, int iDOL, int iAttacking, int iProj){
     
     /*
     dama0004
     Damon Vaughn Caskey
     04/02/2008
     Damage caller's target.
     
     vTar: Target entity. See vTar001 function.
     iHP: Amount of damage to apply.
     iDrop: Knockdown.
     vType: Attack type.
     iDir: Force direction.
     fX/fY/fZ: Toss entity parameters.
     
     */

     void vSelf   = getlocalvar("self");                     //Calling entity.
     void vTarget = vTar001(vTar, vSelf);                    //Target entity.
     int  iSDir   = getentityproperty(vSelf, "direction");   //Calling entity facing.
     int  iTDir   = getentityproperty(vTarget, "direction"); //Target entity facing.
     int  iType   = openborconstant(vType + "");                  //Attack type.

     /*
     Quick and dirty fix. As of version 2.1954, openborconstant returns empty value for "ATK_NORMAL# > 10".
     
     ATK_NORMAL	   0
     ATK_NORMAL2   1
     ATK_NORMAL3   2
     ATK_NORMAL4   3
     ATK_BLAST	   4
     ATK_BURN	   5
     ATK_FREEZE	   6
     ATK_SHOCK	   7
     ATK_STEAL     8					
     ATK_NORMAL5   9
     ATK_NORMAL6  10
     ATK_NORMAL7  11
     ATK_NORMAL8  12
     ATK_NORMAL9  13
     ATK_NORMAL10 14
     ATK_ITEM	  15
     */
     if (!iType && vType != "ATK_NORMAL"){ iType = vType; }

     damageentity(vTarget, vSelf, iHP, iDrop, iType);          //Apply attack/damage.     
     changeentityproperty(vTarget, "damage_on_landing", iDOL); //Set damage on landing flag.
     changeentityproperty(vTarget, "attacking", iAttacking);   //Set attacking flag.
     changeentityproperty(vTarget, "projectile", iProj);       //Set "hit others" flag.     
     
     if (iDir == 1){ 
         iTDir = iSDir;                 //Same as self.         
     }else if (iDir == 2){
         iTDir = 1;                     //Right.
     }else if (iDir == -1){
         if (iSDir){
             iTDir = 1;             
         }else{
             iTDir = 0;
         }         
     }else if (iDir == -2){
         iTDir = 0;                     //Left.
     }     
     
     if (!iSDir){ fX = -fX; }          
     
     if (fY || fX || fZ) { tossentity(vTarget, fY, fX, fZ); }               //If velocity provided, toss em'.
     changeentityproperty(vTarget,"direction", iTDir);
}

void die0001(void vAni, int iFrameMin, int iFrameMax){

    /*
    die0001()
    Damon Vaughn Caskey
    02/12/2008
    Kills caller if parent is not in specified ID or is outside of give frame range.
    
    iAniID: Animation ID to be tested.
    iFrameMin/iFrameMax: Minimum and maximum frame range.
        
    */
    
    void vSelf        = getlocalvar("self");                        //Caller.
    void vParent      = getentityproperty(vSelf, "parent");         //Caller parent.
    int  iParentAniID = getentityproperty(vParent, "animationID");  //Parent animation.
    int  iParentFrame = getentityproperty(vParent, "animpos");      //Parent aimation frame.
        
    if(openborconstant(vAni) != iParentAniID){    
        killentity(vSelf);               
    }else if(iParentFrame < iFrameMin || iParentFrame > iFrameMax){    
        killentity(vSelf);          
    }
 
}

void die0002(void vTar, int iSlot){

    /*
    die0002()
    Damon Vaughn Caskey
    05/30/2008
    Kills entity found in targets designated "slot" variable.
    
    vTarget: Target entity.
    iSlot:   Target slot.
        
    */
    
    void vSelf   = getlocalvar("self");                              //Caller.
    void vTarget = vSelf; //vTar001(vTar, vSelf);
    void vKill   = getentityvar(vTarget, iSlot);

    killentity(vKill);          
     
}

void die0003(int A, int B, int C, int D, int E, int F){

    /*
    die0002()
    Damon Vaughn Caskey
    05/30/2008
    Performs standard death routines on caller.
        
    */

    void vSelf = getlocalvar("self"); //Caller.

    setentityvar(vSelf, 1, NULL());
    setentityvar(vSelf, 2, NULL());
    setentityvar(vSelf, 15, 1);
    changeentityproperty(vSelf, "map", 1);
}

void dir0001(){

     /*
    die0001()
    Damon Vaughn Caskey
    05/17/2008
    Flips caller.
    */
    
     void vSelf = getlocalvar("self");                              //Caller.   
     int  iDir  = getentityproperty(vSelf, "direction");
     
     if (iDir)
     {
          iDir = 0;
     }else
     {
          iDir = 1;
     }
     
     changeentityproperty(vSelf, "direction", iDir);
               
}

void entityvar(int iIndex, void vValue){

     //Sets passed parameter to caller's entity var.
     
     void vSelf = getlocalvar("self"); //Caller.
     setentityvar(vSelf, iIndex, vValue); //iScaleX adjustment.
    
}

void jump0001(float fY, float fX, float fZ){

    void vSelf  = getlocalvar("self");                   //Caller.
    int  iDir   = getentityproperty(vSelf, "direction"); //Caller's direction.
    
    if (!iDir){ fX = -fX; }        
    tossentity(vSelf, fY, fX, fZ);                       //Toss caller.
    
}

void jump0002(float fY, float fX, float fZ){

    void vSelf   = getlocalvar("self");                     //Caller.
    void vTarget = getentityproperty(vSelf, "opponent");    //Callers opponent.
    int  iDir    = getentityproperty(vTarget, "direction"); //Caller's direction.
    
    if (!iDir){ fX = -fX; }        
    tossentity(vTarget, fY, fX, fZ);                       //Toss opponent.    
}

int keyd001(int iIndex, int iNewKey, void vSelf){
     
     /*
     keyd001
     Damon Vaughn Caskey
     05/13/2007
     
     Wrapper for players keys function, returns integer based on key pressed.
     
     iIndex: Player index for key press.
     iNewKey: New key press or "holding".
     vSelf: Target entity. 
     */
          
     if (getentityproperty(vSelf, "direction")==1 && (playerkeys(iIndex,iNewKey, "moveright"))){     
          return 10; //"Forward" (facing right).
     }else if (getentityproperty(vSelf, "direction")==0 && (playerkeys(iIndex,iNewKey, "moveleft"))){     
          return 10; //"Forward" (facing left).          
     }else if (getentityproperty(vSelf, "direction")==1 && (playerkeys(iIndex,iNewKey, "moveleft"))){     
         if (playerkeys(iIndex, iNewKey, "attack")){
             return 13; //"Back + Attack".
         }else{
             return 11; //"Back" (facing right).
         }
     }else if (getentityproperty(vSelf, "direction")==0 && (playerkeys(iIndex,iNewKey, "moveright"))){     
          return 11; //"Back" (facing left).          
     }else if (playerkeys(iIndex,iNewKey, "moveleft")){                                   
          return 1; //Left.     
     }else if (playerkeys(iIndex,iNewKey, "moveright")){     
          return 2; //Right.                    
     }else if (playerkeys(iIndex,iNewKey, "moveup")){     
          return 3; //Up.                    
     }else if (playerkeys(iIndex,iNewKey, "movedown")){     
          return 4; //Down.                    
     }else if (playerkeys(iIndex,iNewKey, "esc")){     
          return 5; //Escape.                    
     }else if (playerkeys(iIndex,iNewKey, "start")){     
          return 6; //Start.                    
     }else if (playerkeys(iIndex,iNewKey, "special")){     
          return 7; //Special.                    
     }else if (playerkeys(iIndex,iNewKey, "jump")){     
          return 8; //Jump.                    
     }else if (playerkeys(iIndex,iNewKey, "attack")){     
          return 9; //Attack 1.                    
     }else if (playerkeys(iIndex,0, "jump") && playerkeys(iIndex,0, "special")){     
          return 12; //Jump + Special           
     }
     
}

void loc0001(float fX, float fZ, float fY){
     
    /*
    map0001
    Damon Vaughn Caskey
    05/19/2008
     
    Adjust location of entity from current position.

    fX, fY, fZ: Adjustment offsets.
    */
    
    void  vSelf = getlocalvar("self");           //Caller.
	float fCX   = getentityproperty(vSelf, "x"); //Caller X location.
    float fCZ   = getentityproperty(vSelf, "z"); //Caller Z location.
    float fCY   = getentityproperty(vSelf, "a"); //Caller Y location.

	changeentityproperty(vSelf, "position", fCX + fX, fCZ + fZ, fCY + fY);
}

void proj0001(void vName, float fX, float fZ, float fY, float iXSpeed, float iYSpeed, float iZSpeed, int iType, int iPType, int iScaleX, int iScaleY, int iFlipX, int iFlipY, int iShiftX, int iBlend, int iRemap, int iFill, int iRotate, int iFlip){
	
     /*
     proj0001
     Damon Vaughn Caskey
     02/11/2008
     
     Launch projectile with all autodraw adjustments.
     
     vName: projectile model name.
     fX, fY, fZ: Spawn location adjustment.
     iXSpeed, iYSpeed, iZSpeed: Speed adjustment of projectile (as of 02112008, X speed is ignored for knife types).
     iType: Unknown.
     iPType: Projectile launch type. 0 = knife, 1 = bomb.
     iScaleX adjustment.
     iScaleY adjustment.
     Flip X.
     Flip Y.
     Shift X.
     Alpha.
     Remap.
     Fill color.
     Rotation.
     */
     
    void vSelf = getlocalvar("self");                   //Caller.
    int iDir = getentityproperty(vSelf, "direction");   //Caller's direction.
    float fAdjustment = getentityvar(vSelf, 14);        //Caller's current autozoom scale.
    void vProj;
        
    if (iFlip){
        if (iDir){
            iDir = 0;
        }else{
            iDir = 1;            
        }
    }
    
    if (iDir) {fX = -fX;}
        
    fX = (fX + getentityproperty(vSelf, "x")) * fAdjustment; //Apply requested X offset to X location and apply zoom scale.
    fZ = fZ + getentityproperty(vSelf, "z");
    fY = (fY + getentityproperty(vSelf, "a")) * fAdjustment; //Apply requested Y offset to Y location and apply zoom scale.
            
    vProj = projectile(vName, fX, fZ, fY, iDir, iType, iPType, 0); //Launch projectile.
    spaw0001(vProj, 0, 0);                                         //Clean autodraw adjustments.    
    changeentityproperty(vProj, "velocity", 0, iZSpeed, iYSpeed);  //Adjust projectile velocity.
    changeentityproperty(vProj, "Speed", iXSpeed);
    
    //Store settings for autodraw function.                     
    if (iScaleX){ setentityvar(vProj, 5, iScaleX); } //iScaleX adjustment.
    if (iScaleY){ setentityvar(vProj, 6, iScaleY); } //iScaleY adjustment.
    if (iFlipX) { setentityvar(vProj, 7, iFlipX);  } //Flip X.
    if (iFlipY) { setentityvar(vProj, 8, iFlipY);  } //Flip Y.
    if (iShiftX){ setentityvar(vProj, 9, iShiftX); } //Shift X.
    if (iBlend) { setentityvar(vProj, 10, iBlend); } //Alpha.
    if (iRemap) { setentityvar(vProj, 11, iRemap); } //Remap.
    if (iFill)  { setentityvar(vProj, 12, iFill);  } //Fill color.   
    
    if (iRotate){    
       if (!iDir) { iRotate = -iRotate; }  //Reverse rotation.
       setentityvar(vProj, 13, iRotate);   //Set Rotation.    
    }

}

void proj0002(void vName, float fX, float fZ, float fY, float iXSpeed, float iYSpeed, float iZSpeed, int iType, int iPType, int iFlip){
	
     /*
     proj0002
     Damon Vaughn Caskey
     02/11/2008
     
     Launch projectile with auto compensation for current zoom, does not provide draw adjustments.
     
     vName: projectile model name.
     fX, fY, fZ: Spawn location adjustment.
     iXSpeed, iYSpeed, iZSpeed: Speed adjustment of projectile (as of 02112008, X speed is ignored for knife types).
     iType: Unknown.
     iPType: Projectile launch type. 0 = knife, 1 = bomb.
     */

    void vSelf = getlocalvar("self");                   //Caller.
    int iDir = getentityproperty(vSelf, "direction");   //Caller's direction.
    float fAdjustment = getentityvar(vSelf, 14);        //Caller's current autozoom scale.
    void vProj;
        
    if (iFlip){
        if (iDir){
            iDir = 0;
        }else{
            iDir = 1;            
        }
    }

    if (iDir) {fX = -fX;}
        
    fX = (fX + getentityproperty(vSelf, "x")) * fAdjustment; //Apply requested X offset to X location and apply zoom scale.
    fZ = fZ + getentityproperty(vSelf, "z");
    fY = (fY + getentityproperty(vSelf, "a")) * fAdjustment; //Apply requested Y offset to Y location and apply zoom scale.
            
    vProj = projectile(vName, fX, fZ, fY, iDir, iType, iPType, 0); //Launch projectile.
    spaw0001(vProj, 0, 0);                                         //Clean autodraw adjustments.    
    changeentityproperty(vProj, "velocity", 0, iZSpeed, iYSpeed);  //Adjust projectile velocity.
    changeentityproperty(vProj, "Speed", iXSpeed);                 //Adjust projectile velocity.
    
    return vProj;
                     
}

int iRan001(float fLoc1, float fLoc2, float fMin, float fMax){

	//iRange
	//Damon Vaughn Caskey
	//08/07/2007
	//Returns 1 if distance between two locations falls within Minimum and Maximum range.
	//
	//fLoc1: First entity.
	//fLoc2: Second entity.
	//fMin: Minumum range value.
	//fMax: maximum range value.

	int fDis = fLoc1 - fLoc2;    
	if ((fMin) || (fMax)){ //Min or max range provided?            
		if(fDis > fMin && fDis < fMax){ //Are entities within minimum and maximum range?        
			return 1; //Return 1.            
		}else{
			return 0; //Return 0.
		}    
	}else{ //Within range or ranges simply not provided.
		return 1;  //Return 1.
	}

}

void spaw0001(void vTarget, int iSkip, int iEndurance){
    
    int  iList   = getindexedvar(0) + 1;   
    int  iCount;   
    
    if (!vTarget) { vTarget = getlocalvar("self"); }
   
    /*
    Clean and prepare variables. In OpenBOR, entity handles are reused, thus the value of vSelf could 
    (and probably will) be the same as that of the last entity to be killed. It is therefore 
    nesesary to "clean" entity vars before use in order to make sure vSelf does not take 
    on the properties of a previous entity.

    vTarget:    Target entity
    iSkip:      Autodraw skipping flag.
    iEndurance: Maximum stun value before being dizzied.
    */

    if (iEndurance){
        setentityvar(vTarget, 1, 0);              
        setentityvar(vTarget, 2, iEndurance);  
    }
    else
    {
        setentityvar(vTarget, 1, NULL());              
        setentityvar(vTarget, 2, NULL()); 
    }

    setentityvar(vTarget, 5, NULL());              
    setentityvar(vTarget, 6, NULL());  
    setentityvar(vTarget, 7, NULL());  
    setentityvar(vTarget, 8, NULL());  
    setentityvar(vTarget, 9, NULL());  
    setentityvar(vTarget, 10, NULL()); 
    setentityvar(vTarget, 11, NULL()); 
    setentityvar(vTarget, 12, NULL()); 
    setentityvar(vTarget, 13, NULL()); 
            
    setentityvar(vTarget, 15, iSkip);  //Store skip setting.
    setentityvar(vTarget, 0, iList);   //Store artificial handle.
    setindexedvar(0, iList);           //Increment counter.
    
	setentityvar(vTarget, 4, getentityproperty(vTarget, "map")); //Orginal color choice.
}

void stat001(void vTar, int iMPAdjust, int iHPAdjust, int var1, int var2, int var3, int var4, int var5){

    //stat001
    //Damon Vaughn Caskey
    //11/03/2007
    //
    //Change MP or HP level of target.
    //
	//vTarget: Entity or target set.
	//iMPAdjust: MP loss or gain.
	//iHPAdjust: HP loss or gain.
    
	void vSelf   = getlocalvar("self");                  //Calling entity.
	void vTarget = vTar001(vTar, vSelf);                 //Target entity.
    int  iMP     = getentityproperty(vTarget, "mp");     //Target's current MP.
	int  iHP     = getentityproperty(vTarget, "health"); //Target's current HP.

	changeentityproperty(vTarget, "mp", iMP + iMPAdjust); //Adjust target's MP.
    changeentityproperty(vTarget, "health", iHP + iHPAdjust); //Adjust target's MP.
}

void stun0001(void vAni){

     /*
     stun0001
     Damon Vaughn Caskey
     02252008
     -Sets stun animation and resets stun on caller if stun factor is -1.
     -vAni: Stun animation.
     */

     void vSelf = getlocalvar("self");              //Calling entity. 
     int  iStun = getentityvar(vSelf, 1);           //Previous stun factor.
     
     if (iStun == -1){                                   //Stun is -1? Dizzy; your screwed!
         setentityvar(vSelf, 1, 0);                      //Reset stun factor.
         performattack(vSelf, openborconstant(vAni), 1); //Set animation for stun.
     }     
}

void stun0003(void vAni){

     /*
     stun0003
     Damon Vaughn Caskey
     06132008
     -Sets requested animation and does NOT reset stun on caller if stun factor is -1.
     -vAni: Stun animation.
     */

     void vSelf = getlocalvar("self");              //Calling entity. 
     int  iStun = getentityvar(vSelf, 1);           //Previous stun factor.
     
     if (iStun == -1){                                   //Stun is -1? Dizzy; your screwed!
         performattack(vSelf, openborconstant(vAni), 1); //Set animation.
     }     
}

void stun0004(void vTar, int iAdd){

     /*
     stun0003
     Damon Vaughn Caskey
     06132008
     -Adds stun to target.
     -vTarget: Target entity
     -vAni:    Stun animation.
     */

     void vSelf   = getlocalvar("self");              //Calling entity. 
     void vTarget = vTar001(vTar, vSelf);
     int  iStun   = getentityvar(vTarget, 1);           //Previous stun factor.
     
     iStun += iAdd; //Add stun.
     
     setentityvar(vTarget, 1, iStun);   //Store new stun value.
}

void vTar001(void vTarget, void vSelf){
	
	/*
    vTar001
	Damon Vaughn Caskey
	08/02/2007
	
	Returns target entity handle from desired source.
	
	itarget:  Desired target source.
	vSelf:    Entity searching for target.
    */

	if (!(vTarget)){ //Self.
		return vSelf; //Return "self".	
	}else if (vTarget == 1){//Current opponent.		
		return getentityproperty(vSelf, "opponent"); //Get current opponent.
	}else if (vTarget == 2){ //Current hold victum.
		return getentityproperty(vSelf, "grabbing"); //Get entity vSelf is holding.
	}else if (vTarget == 3){ //Nearest hostile entity.
		return findtarget(vSelf);		
    }else if (vTarget == 4){ //Caller's parent.
		return getentityproperty(vSelf, "parent");
	}else{ //Variable.
		return getglobalvar(vTarget + vSelf); //Get and return variable matching caller and vTarget.

	}

}

void varset0001(int iRangeMin, int iRangeMax, void vValue){
     
     /*
     varset0001
     Damon Vaughn Caskey
     02/10/2008
     Set range of entity index variables on caller to given value.
     
     iRangeMin/Max: Start and end range of indexes to be cleaned.
     vValue: Desired value.
     */
     
     void vSelf = getlocalvar("self"); //Caller.

     for(iRangeMin; iRangeMin<iRangeMax; iRangeMin++){     
         setentityvar(vSelf, iRangeMin, vValue); //Clean variable.     
     }

}

void velo001(float fX, float fZ, float fY){
     
    /*
    velo001
	Damon Vaughn Caskey
	05/06/2007
	Replicates movement effect on caller.
	
	fX: X axis speed.
	fZ: Z axis speed.
	fY: Y axis speed.
	*/
	
	void vSelf = getlocalvar("self"); //Calling entity.
	
	if (!getentityproperty(vSelf, "direction")){ //Facing right?                  
        fX = -fX; //Reverse X direction to match facing.
    }         
	
	changeentityproperty(vSelf, "velocity", fX, fZ, fY); //Apply movement.

}
