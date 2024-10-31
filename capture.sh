#!/usr/bin/env -S zsh --no-rcs --no-globalrcs --errexit --pipefail

# script to capture screen using ffmpeg

declare -r output='output.mp4'
declare -r resolution='1920x1080'
declare -r framerate='30'

if [[ -z $DISPLAY ]]; then
	echo 'DISPLAY not set'
	exit 1
fi


ffmpeg -f x11grab -s $resolution -framerate $framerate -i $DISPLAY \
-c:v huffyuv output.mkv
#-c:v libx264 -preset ultrafast -crf 0 $output

#-vcodec rawvideo -pix_fmt yuv420p $output


