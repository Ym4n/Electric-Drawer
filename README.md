# Electric-Drawer
Electric Drawer for laser projector. control by Arduino.

https://user-images.githubusercontent.com/82320340/115971307-6bd4b180-a550-11eb-89f3-70404eacda08.mp4

# The Goal -
1.  Drawer can pool in and out to a specific position - No more manual operation.
2. Accuracy position - No more fine tune the projector to the accurate projection position. 
With every 1mm of distance between projector’s back to the projection surface, 0.2 inches are gained in picture size. 
see video below -

https://user-images.githubusercontent.com/82320340/115971346-9a528c80-a550-11eb-801a-cefcc77d8984.mp4

# How Dose it work?
1. User sends command with a remote control to IR reader or click on an arcade button . 
(Note: currently I aded 2 remotes. You can add/remove/change it)
2. IR-reader/button signal connected to Arduino.
3. Arduino decides to which position to get to. Far out or far in. 
In case of the drawer is already in the correct position, no movement will be made. 
(This is being determined by the Arduino using the two sensors that are located at the beginning and end of the movement range).
4. Motion control by arduino ,stepper motor and inductive sensors.


you can check mechanical design at solidworks folder or electrical design in electrical drawing .
