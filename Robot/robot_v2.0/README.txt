|*************************|
|robot version 2.0        |
|*************************|

Function: 
1¡¢the robot can read some of the basic sentences and give out a right respond. For example, I
ask it "what are you doing?", it will respond with "I'm working.", and I say "i gonna go.",
it will answer "see you, sir!". The key is that the robot can understand your sentences even
you spell in a wrong way but similar to the original one.
2¡¢Another important idea is that the robot can raise up a topic at any time it prefer, there 
are so many interesting topics it knows that it seems like a real speaker.
3¡¢the last function is decided for myself. Because i am bad at controlling myself to study hard,
i say "make agenda", it will help me to build up a plan for tomorrow. Next day 11 o'clock at night
it will inform me to check the homework automatically.

Differences from version_1.0:
	This version has build up a emotion system for the robot. It is included in "memory.h", until
now, I make it knowledgeable enough to justify whether the asker is happy or not by some simple
sentence (only simple sentence). My method is that use a list of ordered typical words sequences
to match the sentence in an intelligent way, and the result of matching will change the data of its
emotion system (robot's happiness, my happiness, our relationship). Also, every change will make
the system different and this emotion system make the robot seems like a real changeable human.
	Feedback mechanism is the key of the system's function, while the data of the robot's memory
has changed largely, then its behavior will come to different so that we can recognize its emotion.
	  
Program structure:
		  AI-----AI.cpp-----agender.h--------agenda.txt
		  	  |	         |			      |
		  	  |          ---algorithm.h   ---agenda_score.txt
		  	  |          |
		  	  |          ---memory.h---------main_memory.txt
		  	  |          |                |
		  	  |          |                ---typical_words.txt
		  	  |          |
		  	  |          ---temp.txt
		  	  |          |
		  	  |          ---topic.txt
			  |
		      ---AI.exe
		      |
		      ---README.txt
		      
Robot maker:
	Lin Chuting, Sun Yat-sen University (Department of Electronic Engineering, School of Data and
Computer Science, Guangzhou 510006,China)

A letter for all readers:
	There are still many problem that needed to be solved, such as how to learn from user while
talking and how to build up the emotion for itself. It is such a long way to go, but i am not
quiting untill dead. Thanks for all crazy AI-Lover reading my program and if you have any good
idea to make the robot more advanced, please contact me with e-mail: 937426466@qq.com

