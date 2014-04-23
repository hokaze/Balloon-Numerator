### Level Format Guide ###

## Objects ##

# Player #
Format: player;x;y;
Example: player;50;50

Additional Notes:
Levels don't create a new player instance, it sets the new starting/respawn point and moves the player there.
In the future this will reset the player's location upon death or exiting to menu and restarting.

# Enemy1 #
Format: enemy1;x;y;z;
Example: enemy1;550;350;2;

Additional Notes:
Enemies are spawned at the specified location (x,y) with z balloons. Additional paramaters may come later, along with alternate foes.

# Platform #
Format: ground;x;y;
Example: ground;-10;550;

Additional Notes:
When placing platforms near or at the edges of the screen, make them go out of bounds by at least 10 pixels.
This eliminates some potential collision issues with how screen-wrap works on the player.

# TextDisplay #
Format: textDisplay;x;y;message;font;colour;size;
Example: textDisplay;250;10;What is 84 split in half?;Roboto.ttf;white;30;

Additional Notes:
Spawns message at x, y. Colour must be a valid SDL_Color, Font is the file used, message is a short string.
The player and other entities should NOT be able to collide with this.

# NumberBalloon #
Format: numberBalloon;x;y;filename;number;font;colour;size;correct;
Example: numberBalloon;700;200;img/numberBalloon.png;42;Roboto.ttf;white;18;1;

Additional Notes:
Spawns a balloon at x, y, that has a number on it. Colour, font, size follows TextDisplay rules.
The number is in fact a string for the font to render, but it should be restricted to integers only.
"Correct" is a 0/1 bool, where 1 means the correct answer and 0 means an incorrect answer.

# Spiky #
Format: spiky;x;y;direction;speed;
Example: spiky;700;300;01;

Additional Notes:
Enemy/Obstacle, cannot be beaten. Adapted from the "birds" of the mockups. A mascot of sorts, maybe?
Flies either right or left based on the direction bool (1 = right) at a rate of speed pixels per frame.
Not subject to gravity, screen-wraps. Harms player and enemy balloonists alike. No bouncing.

## Further Information ##

Seperation is done by semi-colons instead of commas to allow for easier inclusion of strings containing commas.
All level files are plain text files (preferably UTF-8) and need the semi-colon on the end of each line too.
Files starting with "main" are normal levels, those with "sub" are educational question levels.

THIS REMAINS AN EXPERIMENTAL WIP FEATURE.