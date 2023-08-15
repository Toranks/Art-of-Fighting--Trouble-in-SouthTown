void main()
{
	release();
}

void release()
{
		void self = getlocalvar("self");
		int victim = getentityvar(self, "player");
		int HP = getentityproperty(self,"health");
		void iUp = playerkeys(victim, 1, "moveup"); // New key status of "Up"
		void iDown = playerkeys(victim, 1, "movedown"); // New key status of "Down"
		void iLeft = playerkeys(victim, 1, "moveleft"); // New key status of "Left"
		void iRight = playerkeys(victim, 1, "moveright"); // New key status of "Right"
		void iJump = playerkeys(victim, 1, "jump"); //New key status of "Jump"
		void iSpecial = playerkeys(victim, 1, "special"); //New key status of "Special"
		void iAttack = playerkeys(victim, 1, "attack"); //New key status of "Attack

		if(iUp || iDown || iLeft || iRight || iJump || iSpecial || iAttack){// button is pressed?
    	
		changeentityproperty(self, "health", HP+1);
		
	}
}