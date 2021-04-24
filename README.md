# Electric-Drawer
Electric Drawer for laser projector. control by Arduino.

# The Goal -
1. Drawer go to specific location - No more manual operation and calibrate the projector to the right spot. 
2. Accuracy - drawer movement = 1mm
1mm move from the wall equal to increase the screen by 0.2 inch. 

# How it's work?
1. User send command with remote control to IR reader or added arcade button to send command. 
(Note: currently I add 2 remotes, you can add/remove/change it) 
2. IR reader signal connect to Arduino. 
3. Arduino control stepper motor and sense inductive sensors.
