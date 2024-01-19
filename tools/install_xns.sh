#!/usr/bin/env -S zsh --no-rcs --no-globalrcs


# -- V A R I A B L E S --------------------------------------------------------

# get current directory
ROOT=$(pwd)

# get basename
BASENAME=${ROOT##*/}

# library name
LIBRARY='xns'

# repository url
REPO_URL='https://github.com/123Untitled/xns.git'

# commit hash url
COMMIT_URL='https://api.github.com/repos/123Untitled/xns/commits/main'

# repository path (hash)
REPO_PATH='7856e1141a018922cb5f202e9e536280f6a1c4a27f948f7710d379b3'

# install path
INSTALL_PATH='external/'$LIBRARY

# last commit
LAST_COMMIT=$INSTALL_PATH'/.last_commit'

# required programs
REQUIRED_PROGRAMS=('pwd' 'cd' 'rm' 'mv' 'mkdir' 'echo' 'git' 'curl' 'jq')


function clean_directories() {
	rm -rf $REPO_PATH $INSTALL_PATH
}


# check if required programs are installed
for PROGRAM in $REQUIRED_PROGRAMS; do
	if ! command -v $PROGRAM &> /dev/null; then
		echo 'error:' $PROGRAM 'is not installed'
		exit 1
	fi
done

# check if we are in right directory
if [[ $BASENAME != 'vulkan_engine' ]]; then
	echo 'error: this script must be run from' "'vulkan_engine'" 'directory'
	exit 1
fi

# check if library is missing
if [[ ! -d $INSTALL_PATH ]]; then

	# create install directory
	mkdir -p $INSTALL_PATH
	# remove repository directory if exists
	rm -rf $REPO_PATH

	# clone repository
	if ! git clone -v $REPO_URL $REPO_PATH; then
		echo 'error: failed to clone xns repository'
		clean_directories
		exit 1
	fi

	# get latest commit hash
	if ! git -C $REPO_PATH rev-parse HEAD > $LAST_COMMIT; then
		echo 'error: failed to get latest commit hash'
		clean_directories
		exit 1
	fi

	# build library
	cd $REPO_PATH
	if ! ./make.sh release; then
		echo 'error: failed to build xns library'
		clean_directories
		exit 1
	fi

	tools/single_header.sh

	cd '..'
	mv $REPO_PATH'/libxns.a' $INSTALL_PATH
	mv $REPO_PATH'/xns/xns'  $INSTALL_PATH
	rm -rf $REPO_PATH

	echo 'xns library installed'
	exit 0
fi


local REQUEST=''

# get latest commit hash
if ! REQUEST=$(curl -s $COMMIT_URL); then
	echo 'curl: failed to get latest xns library commit hash'
	exit 1
fi


# extract commit hash
local NEW_COMMIT=$(jq -r '.sha' <<< $REQUEST)

# check if xns library is up to date
if [[ ! -f $LAST_COMMIT || $(<$LAST_COMMIT) != $NEW_COMMIT ]]; then
	echo 'updating xns library...'
	rm -rf $INSTALL_PATH
	# call this script again
	$0
	exit $?
else
	echo 'xns library is up to date'
fi

exit 0
