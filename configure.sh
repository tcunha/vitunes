#!/bin/sh

if [[ "$#" != "0" ]];
then
   echo "usage: $0\n" \
        "   to blah blah blah"
fi

# flag to determine if we found any media backends
HaveBackend=false

#######################################################################
# Determine install locations (based on OS)
#######################################################################

# defaults (hey, they suite me)
PREFIX="/usr/local"
BINDIR="${PREFIX}/bin"
MANDIR="${PREFIX}/man/man1"

# get OS name determine from that.  Are Linux distros all common with this?
os=`uname`
case ${os} in
"Linux")
   PREFIX="/usr"
   echo "Detected: OS is Linux"
   echo "          Setting install prefix to '${PREFIX}'"
   ;;
"FreeBSD"|"NetBSD"|"OpenBSD")
   echo "Detected: OS is ${os}"
   echo "          Setting install prefix to '${PREFIX}'"
   ;;
esac

echo "          Will install vitunes to the following locations:"
echo "                  binary into:   ${BINDIR}"
echo "                man-page into:   ${MANDIR}"


#######################################################################
# Detect TagLib
#######################################################################
result=`pkg-config --exists taglib`
if [[ "$?" == "0" ]];
then
   echo "Detected: TagLib IS installed."
   TAGLIB_BLOCK="
# taglib library detected by pkg-config
TAGLIB_CFLAGS  = \`pkg-config taglib --cflags\`
TAGLIB_LDFLAGS = \`pkg-config taglib --libs\` -ltag_c
"
else
   echo "Detected: TagLib IS NOT installed."
   echo "ERROR: taglib is REQUIRED to build vitunes!"
   TAGLIB_BLOCK="
# taglib library not detected by pkg-config (vitunes will not build)
"
fi


#######################################################################
# Detect MPlayer
#######################################################################
result=`which mplayer`
if [[ "$?" == "0" ]];
then
   HaveBackend=true
   echo "Detected: mplayer IS installed."
else
   echo "Detected: mplayer IS NOT installed."
   echo "          Note that mplayer support is still enabled.  To make use of"
   echo "          it, simply install mplayer and make sure the 'mplayer'"
   echo "          program appears in your \$PATH."
fi


#######################################################################
# Detect gstreamer
#######################################################################
gstreamer=gstreamer-0.10
result=`pkg-config --exists ${gstreamer}`
if [[ "$?" == "0" ]];
then
   HaveBackend=true
   echo "Detected: gstreamer (${gstreamer}) IS installed."
   GSTREAMER_BLOCK="
# gstreamer library (${gstreamer}) detected by pkg-config
GSTREAMER_CFLAGS  = \`pkg-config ${gstreamer} --cflags\` -DENABLE_GSTREAMER
GSTREAMER_LDFLAGS = \`pkg-config ${gstreamer} --libs\`
GSTREAMER_OBJS    = gstplayer.o
"
else
   echo "Detected: gstreamer (${gstreamer}) IS NOT installed."
   echo "          To add support for using gstreamer for multimedia playback,"
   echo "          first install gstreamer and then re-run this script and"
   echo "          build vitunes."
   GSTREAMER_BLOCK="
# gstreamer library (${gstreamer}) not detected by pkg-config
"
fi


#######################################################################
# Begin Building config.mk
#######################################################################

echo

# backup the stock config.mk
backup=config.mk.stock
if [[ -f config.mk && ! -f ${stock} ]];
then
   echo "Backing up stock config.mk to ${backup}"
   cp config.mk ${backup}
fi

# start writing
echo "Creating config.mk..."
cat >> config.mk <<EOF
# This file was generated by the 'configure.sh' script.
# Its contents should probably not be modified directly (if they should,
# please contact the vitunes developers and let them know why).
#
# Contents generated on: `date`
# Run on OS: `uname -a`


# Install Locations
PREFIX = ${PREFIX}
BINDIR = ${BINDIR}
MANDIR = ${MANDIR}


# TagLib
${TAGLIB_BLOCK}


# gstreamer
${GSTREAMER_BLOCK}


# configure.sh output ending
EOF

# completed.  provide some instructions.
echo "COMPLETED: config.mk generated."
echo
echo "If there were no errors above, and you are satisfied with the install"
echo "locations listed above, then you should now be able to install vitunes"
echo "with:"
echo "   $ make install"
echo "G'luck!"

