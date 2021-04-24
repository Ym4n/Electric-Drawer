# Electric-Drawer
Electric Drawer for laser projector . control by arduino .

# The Goal -
1. Drawer go to specific loction - No more manual operation and calibrate the projector to the right spot. 
2. Accuracy - drawer movement = 1mm . 1 mm move from the wall equal to increase the screen by 0.2 inch. 

# How it's work?
With Remote control user send command to IR reader, also added arcade button to send command. 
(Note : currently I add 2 remotes , you can add/remove/change it) 
IR reader signal connect to Arduino . 
Arduino control Steper motor and sense inductive sensors .

