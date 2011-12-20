SmileFile

by Stan James http://wanderingstan.com/

based on AutoSmiley : http://fffff.at/auto-smiley/
which in turn is based on
openFrameworks : http://openframeworks.cc/
and MPT : http://mplab.ucsd.edu/grants/project1/free-software/mptwebsite/API/

Distributed under the MIT Licences. See licence.txt


Launch from Terminal. First parameter is name of file to append smile records to. Second (optional) parameter is a command to be executed whenever a smile is detected.

e.g.

open ./SmileFile.app --args "/Users/YOURUSERNAME/Documents/smilelog.txt"

or, to take a screen capture each time a smile is detected:

open ./SmileFile.app --args "/Users/YOURUSERNAME/Documents/smilelog.txt" "/usr/sbin/screencapture -m -x /Users/stan/Pictures/Periodic/screen_$RANDOM.png"

(Replace YOURUSERNAME with your OS X username.)

Have fun!