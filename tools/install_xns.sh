#!/usr/bin/env -S zsh --no-rcs --no-globalrcs


# -- V A R I A B L E S --------------------------------------------------------

# get current directory
ROOT=$(pwd -P)

# get basename
BASENAME=${ROOT##*/}

# library name
LIBRARY='xns'

# repository url
REPO_URL='https://github.com/123Untitled/xns.git'

# repo
REPO='123Untitled/xns'

# branch
BRANCH='main'

# commit hash url
COMMIT_URL='https://api.github.com/repos/123Untitled/xns/commits/main'

# hash of url (avoid conflicts)
REPOSITORY=$ROOT'/d776502056cec639501e1f8aa494d06c'

# prefix directory
PREFIX=$ROOT'/external'

# target directory
TARGET=$PREFIX'/'$LIBRARY

# last commit
COMMIT=$TARGET'/.last_commit'

# required programs
REQUIRED_PROGRAMS=('pwd' 'cd' 'rm' 'mv' 'mkdir' 'echo' 'git' 'curl' 'jq')


function clean_directories() {
	rm -rf $REPOSITORY $TARGET
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
	echo 'error: this script must be run from' "'vulkan_engine'" 'repository'
	exit 1
fi

# check if library is missing
if [[ ! -d $TARGET ]]; then

	# create prefix directory if not exists
	mkdir -p $PREFIX
	# remove repository if exists
	rm -rf $REPOSITORY

	# clone repository
	if ! git clone -v $REPO_URL $REPOSITORY; then
		echo 'error: failed to clone xns repository'
		clean_directories
		exit 1
	fi

	# build library
	cd $REPOSITORY

	if ! ./make.sh install $PREFIX; then
		echo 'error: failed to build xns library'
		clean_directories
		exit 1
	fi

	cd $ROOT

	# get latest commit hash
	if ! git -C $REPOSITORY rev-parse HEAD > $COMMIT; then
		echo 'error: failed to get latest commit hash'
		clean_directories
		exit 1
	fi

	rm -rf $REPOSITORY

	exit 0
fi

local REQUEST=''

# get latest commit hash
if ! REQUEST=$(curl -s $COMMIT_URL); then
	echo 'curl: failed to get latest xns library commit hash'
	exit 1
fi


local NEW_COMMIT=''

# extract commit hash
if ! NEW_COMMIT=$(jq -r '.sha' <<< $REQUEST); then
	echo 'jq: failed to extract commit hash'
	exit 1
fi

# check if xns library is up to date
if [[ ! -f $COMMIT || $(<$COMMIT) != $NEW_COMMIT ]]; then
	echo 'updating xns library...'
	rm -rf $TARGET
	# call this script again
	$0
	exit $?
else
	echo 'xns library is up to date'
fi

exit 0
