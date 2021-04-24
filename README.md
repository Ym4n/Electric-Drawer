# Electric-Drawer
Electric Drawer for laser projector. control by Arduino.

https://user-images.githubusercontent.com/82320340/115971307-6bd4b180-a550-11eb-89f3-70404eacda08.mp4

# The Goal -
1. Drawer go to specific location - No more manual operation and calibrate the projector to the right spot. 
2. Accuracy - 1mm move from the wall equal to increase the screen by 0.2 inch. see video below -

https://user-images.githubusercontent.com/82320340/115971346-9a528c80-a550-11eb-801a-cefcc77d8984.mp4

# How it's work?
1. User send command with remote control to IR reader or click on arcade button . 
(Note: currently I add 2 remotes, you can add/remove/change it) 
2. IR-reader/button signal connect to Arduino.
3. Arduino decide which direction to move or if it's possible to move.  
4. Arduino control stepper motor and sense inductive sensors.


you can check mechanical design at solidworks folder or electrical design in electrical drawing .
