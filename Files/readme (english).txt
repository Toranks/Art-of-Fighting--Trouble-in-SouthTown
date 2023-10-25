
		******************************************
		*				 	                     *
		*	     AOF TROUBLE IN SOUTH TOWN	     *
		*		       BEST/DEFAULT		         * 
		*		         OPTIONS 		         *
		*					                     *
		******************************************


THIS GAME ONLY WORKS ON OPENBOR 6XXX OR HIGHER SINCE 3.0 - For lower versions you need to play 1.X or 2.X versions of the game.

NOTE: The recomended version is the version provided with the game, 

-----------------------//--VIDEO-OPTIONS--//------------------------------------

	- ( ive set video options to default to prevent compatibility issues )

	- for best quality image if youre playing
	  in a pc you should use the options below


	DISPLAY MODE	- FULL
	VIDEO BACKEND	- OPENGL
	SCALE		- AUTOMATIC
	HARDWAREFILTER	- BILINEAR
	SOFTWAREFILTER	- 16bit MAME or HO2X --*important*-- great improvement
	FULLSCREENTYPE	- PERSERVE ASPECT RATIO


	- Ive made the game for resolution 480x272
	  should you try to change it in video.txt file although
	      it will look better most levels wont work.


---------------------//--IN-GAME-NOTES--//----------------------------------
	
	 - during the game by pressing certain buttons a tutotial will pop up

	 * PLAYERS - ATTACK2
	 * CURSOR MAP - JUMP
	 * VEHICLES2 - ATTACK2

	 - all special attacks for all players/secret are very easy to master
	   and they wont fall from under the basics except for buttons attack/jump/special
	 - here are the most common

		down / foward

		foward / down

		foward / down / foward

		down / up
	
	 - all running slide attack is performed with run+d/f+j instead of run+d+j as it
	   appears on the manual
	 - all running dodge up / dodge down is performed with run+f,d/f,f,d/f or run+f,u/f,f,u/f
	   instead of run+d,d or run+u,u as it appears on the manual. You can keep running holding
	   f button at the end of movement.
	 - SECRET: You can change tutorial music by replacing data/music/begin2.ogg with the same file on Files/begin2.ogg
---------------------//--CONTROLS-OPTIONS--//----------------------------------

	- game works better with certain defined
	  setup controls

	- if you've set controls to default and
	  want to change them to the way i use
	  with a Xbox gamepad setup it up this way

		ATTACK1 - X
		ATTACK2 - Y
		ATTACK3 - L1
		ATTACK4 - L2
		JUMP	- A
		SPECIAL - B
		SCREENSHOT - Start or F12

  ( attack4 are only used with some characters )

	- note: screenshot key should remain "f12"
	        has you might need it in game for
		when you find password tablets.
	( its best to take a screenshot than write 
	     the whole dam thing on a piece of paper 
	  image should be located in the screenshots folder)



--------------------//-----------------//------------------------------------

	Art of Fighting Trouble in South Town
		made on pc core2duo 3.0
		    gforce 550 ti 1gb drr
			windows 7 
		updated and tested on a pc intel celeron 2.80
			gforce gt710 2gb ddr
			windows 7


  --- to contact me for bugs or visit the game website please go to ---
	  	http://jon-fretes-silva.wix.com/aofsouthtown

  --- to contact with 2.3.1 updater ---
  
		https://www.youtube.com/toranks

NOTE:	i havent tested the game on xbox360/psp or android
	i can teste it on xbox360 and psp if people ask me
		but android its out of my reach


-----------------------//--BUGS-AND-ISSUES--//------------------------------

	- Here are some bugs that iam currently aware

	
	1- In the test your might level you may find to dificult if not impossible
	   to raise the focus bar. The problem seems to have something to do with
	   the CPU/GPU speed if your playing in a 4core 3.0/i5/i7 cpu it may be to dificult
	   to raise the focus bar.

	2- the cup game in club kat can fail sometimes in the last very fast i think it 
	   also has something to do with CPU speed.
	   
	3- If you get a black screen loading any stage (only happens on elevators of Mr Big for me),
		and you	have already finished the game, go to Sout Town Free Map, load the stage that
		is giving you problems, exit, and (without exiting Openbor), load the savegame.
		If you haven't finished the game yet, open the levels.txt file in data folder on
		notepad and change this line:
	
	set		south_town_free_map
	ifcomplete	1
	
		with
	
	set		south_town_free_map
	#ifcomplete	1
	
		Start AOF.exe and and do the method described before. You can delete the # symbol
		when you solve the problem.

	*NOTE:	i was unable to fix this errors, but they only happen very rarely
		I've tested the game and now it is very stable. 
		
	4- If you experience crashes, slowdowns or memory problems at the stage with Johnny where many animals help you, there is a lighter version of that level in the "Files" folder. Make a backup copy and replace the file in /data/levels/beyond/bydlvl17.txt with the one in the folder /Files/bydlvl17.txt

	5- If the game is shuttering (bbbbrrrrr..Hiiickkk) or slowing down.
	  delete all files in the Saves folder (AOF.cfg AOF.sav etc)
	  its probably reading the config that was used on another computer.
	  
#########################################################################################
