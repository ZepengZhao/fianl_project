Final Project
Here is my project "Tank War". I played this kind of game in the period of my childhood, and now I have the change to make my own game.
Without so much knowledge with QT, I begin this project studying the syntax and the basic organization of QT. I study through 
http://doc.qt.io/(the official website) and https://www.devbean.net/2012/08/qt-study-road-2-catelog/(a tutorial written by a software
engineer). Also, stackoverflow, google, Quora, etc. After a preliminary knowledge of QT, I decide to settle down on the"Tank War". First
the struggle comes up is that I have no idea how to organize the whole project. How many header and cpp files I should make to separate 
the project? So, I study the "https://github.com/wojiushimogui/Tank"(It's a program written by Java, I merely study the organization).
After a thoughtful thinking, I decide to make explode/missile/tank/wall---that Big 4 elements.
After searching for the pictures of elements, I struggle how to allocate the path of pictures. At first, I can successfully show the
pictures by "absolute path"(for example, "\C:user:......"). However, I fail to show the picture by the way of resource file. After several
days trying, I run "qmake" accidentally. Miraculously, it successd.

It is somehow troublesome to make different directions of the tank and the different sizes of "explode". And turn them into cartoon is a big
diffculty for me. My favorite design is setting the wall(block) since I have a feeling that I'm actual designing. 

My design is like below:
W-up                                          
S-down                                     
A-left                                           
D-right                                         
J-fire                        
Solid Wall-- can't be destroyed
Wood block--can be destroyed 
Bush—can hide tank 
Water—can hide tank(same as Bush) 
(This documention can be found in the game)

What I should improve is that I didn't make "tank hit tank"(that mean a tank can go through other tanks).Actully, I tried to fix this, but
a run-time error occured. :(
Also, I didn't provide any destructor.(I try to fix this but there are lot of error) :(

Thank you for the whole quarter teaching!
If you have any questions, or it can't compile on your machine, or it complies but not so neatly, please contact me. zhaozepeng46@gmail.com



