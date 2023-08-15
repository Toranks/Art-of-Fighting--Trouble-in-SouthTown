void main()
{
    int iPlIndex = getlocalvar("player"); //Get calling player
    void vSelf = getplayerproperty(iPlIndex , "entity"); //Get calling entity
    void self = getlocalvar("self");
    void vAniID = getentityproperty(self,"animationID"); //Get current animation ID
    int iDir = getentityproperty(self, "direction");  //Get current facing direction


    int iVx = getentityproperty(self, "xdir");
    int iVy = getentityproperty(self, "tossv");

    void iUp = playerkeys(iPlIndex, 1, "moveup"); // New key status of "Up"
    void iDown = playerkeys(iPlIndex, 1, "movedown"); // New key status of "Down"
    void iLeft = playerkeys(iPlIndex, 1, "moveleft"); // New key status of "Left"
    void iRight = playerkeys(iPlIndex, 1, "moveright"); // New key status of "Right"
    void iJump = playerkeys(iPlIndex, 1, "jump"); //New key status of "Jump"
    void iSpecial = playerkeys(iPlIndex, 1, "Special"); //New key status of "Special"
    void iAttack = playerkeys(iPlIndex, 1, "attack"); //New key status of "Attack"
    void iAttack2 = playerkeys(iPlIndex, 1, "attack2"); // New key status of "Attack 2"
    void iAttack3 = playerkeys(iPlIndex, 1, "attack3"); // New key status of "Attack 3"
    void iAttack4 = playerkeys(iPlIndex, 1, "attack4"); // New key status of "Attack 4"

    void iUpR = playerkeys(iPlIndex, 2, "moveup"); // Release status of "Up"
    void iDownR = playerkeys(iPlIndex, 2, "movedown"); // Release status of "Down"
    void iLeftR = playerkeys(iPlIndex, 2, "moveleft"); // Release status of "Left"
    void iRightR = playerkeys(iPlIndex, 2, "moveright"); // Release status of "Right"
    void iAttackR = playerkeys(iPlIndex, 2, "attack"); //Release status of "Attack"

    void iDownH = playerkeys(iPlIndex, 0, "movedown");
    void iUpH = playerkeys(iPlIndex, 0, "moveup");
    void iLeftH = playerkeys(iPlIndex, 0, "moveleft");
    void iRightH = playerkeys(iPlIndex, 0, "moveright");



//Move while flying
    if(vAniID != openborconstant("ANI_SPAWN") && vAniID != openborconstant("ANI_RESPAWN")){ //Not in improper animations?
      if(iLeftR || iRightR){ //Left or Right released?
        if(!iLeftH && !iRightH){ //Left and Right not pressed?
          changeentityproperty(vSelf, "velocity", 0, 0, iVy);
        }
      } else if(iLeft){ //Left pressed?
        changeentityproperty(self, "velocity", -1, 0, iVy);
        changeplayerproperty(self, "playkeys", 0);
      } else if(iRight){ //Right pressed?
        changeentityproperty(self, "velocity", 1, 0, iVy);
        changeplayerproperty(self, "playkeys", 0);
      }

      if(iUpR || iDownR){ //Up or Down released?
        if(!iUpH && !iDownH){ //Up and Down not pressed?
          changeentityproperty(vSelf, "velocity", iVx, 0, 0);
        }
      } else if(iUp){ //Up pressed?
        changeentityproperty(vSelf, "velocity", iVx, 0, 1);
        changeplayerproperty(vSelf, "playkeys", 0);
      } else if(iDown){ //Down pressed?
        changeentityproperty(vSelf, "velocity", iVx, 0, -1);
        changeplayerproperty(vSelf, "playkeys", 0);
      }
	else if(iAttackR){
     	performattack(vSelf, openborconstant("ANI_FOLLOW1"));
	}


    }

//Missile Shoot
    if(iAttack2){ //Attack pressed?
      int TPhase = getentityvar(vSelf, 0);

      if(vAniID == openborconstant("ANI_IDLE") || vAniID == openborconstant("ANI_WALK")){ //Idle or walk?
        if(TPhase != NULL() && TPhase <= openborvariant("elapsed_time") - 120){
          setentityvar(vSelf, 0, NULL());
          TPhase = NULL();
        }
        if (TPhase == NULL()){
          performattack(vSelf, openborconstant("ANI_FOLLOW1"));
        }
      }
    }

}