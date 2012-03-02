#!/bin/bash
# See for more info: http://www.cyberciti.biz/tips/shell-scripting-creating-reportlog-file-names-with-date-in-filename.html
# ---------------------------------------------------------------------------------------------------------
 
## date format ##
NOW=$(date "+%Y-%m-%dT%H-%M-%SZ%z")

# Take a picture of the screen
SCREEN=$HOME"/smilefile/"$NOW"-screen.jpg"
echo -n `/usr/sbin/screencapture -m -x $SCREEN`

# rename webcam shot
echo -n `mv /tmp/latest-smile.jpg ~/smilefile/$NOW-smile.jpg`

## Periodic Data Path ##
#DIR="/Users/stan/Pictures/Periodic"
#BINDIR=$DIR"/bin"
DIR=$(cd "$(dirname "$0")"; pwd)
BINDIR=$DIR"/bin"

# Remember what app was on top
#TOPAPP=$DIR"/log/current_"$NOW".txt"
TOPAPP=`/usr/bin/osascript $BINDIR/testapp.scpt`
TEMPCURRENT="/tmp/smile-file-current-app.txt"
echo -n `/usr/bin/osascript $BINDIR/testapp.scpt > $TEMPCURRENT`

# If browser, record current URL
if grep -q "Google Chrome.app" $TEMPCURRENT
then
	# if found, append URL
	URL=`/usr/bin/osascript $BINDIR/current-browser-url.scpt`
fi

# Record our geographic location
#LATLON=`$BINDIR/whereami > $LATLON`

# print out results that will go into log file
echo -e "\t$SCREEN\t$TOPAPP\t$URL"

