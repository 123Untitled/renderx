#!/usr/bin/env -S zsh --no-rcs --no-globalrcs --errexit --pipefail


# -- F U N C T I O N S --------------------------------------------------------

# var error
function _print_error() {
	echo $1 "'\x1b[32m"$2"\x1b[0m'"
}


# -- A R G U M E N T S --------------------------------------------------------

# require only one argument
if [[ $# -ne 1 ]]; then
	_print_error 'missing argument:' 'environment file'
	exit 1
fi

# source the environment file
if ! source $1 &> '/dev/null'; then
	_print_error 'failed to source:' $1
	exit 1
fi


# -- V A R I A B L E S --------------------------------------------------------

# required environment variables
declare -r var_names=(
	'library_name'
	'target_directory'
	'repository_url'
	'branch_name'
	'cmake_flags'
)


# loop over the required environment variables
for var_name in $var_names; do

	# check if the variable is set
	if [[ ! -n ${(P)var_name} ]]; then
		_print_error 'missing environment variable:' $var_name
		exit 1
	fi
done

# repository directory
declare -r repo_directory=$library_name

# build directory
declare -r build_directory=$target_directory'/'$library_name


# -- O S ----------------------------------------------------------------------

# get the operating system
declare -r os=$(uname -s)

# get number of processors
if   [[ $os == 'Darwin' ]]; then
	declare -r threads=$(sysctl -n hw.logicalcpu)
elif [[ $os == 'Linux' ]]; then
	declare -r threads=$(nproc)
else
	_print_error 'unsupported operating system:' $os
fi


# -- R E P O S I T O R Y ------------------------------------------------------

# check if the repository is already cloned
if [[ ! -d $repo_directory ]]; then

	# clone the repository
	if ! git clone --branch $branch_name --single-branch --depth 1 \
		$repository_url $repo_directory; then
		_print_error 'failed to clone the repository:' $repository_url
		exit 1
	fi
fi

# create directories
if ! mkdir -p $target_directory $build_directory; then
	_print_error 'failed to create directories' \
		$target_directory'|'$build_directory
	exit 1
fi


# -- B U I L D ----------------------------------------------------------------

# check if ninja is available
if command -v 'ninja' &> '/dev/null'; then

	cmake_flags+=('-G Ninja')

	declare -r build_command=('ninja'
							  '-j'$threads
							  '-C'
							  $build_directory)

	declare -r install_command=('ninja'
								'-C'
								$build_directory
								'install')

# check if make is available
elif command -v 'make' &> /dev/null; then

	cmake_flags+=('-G Unix Makefiles')

	declare -r build_command=('make'
							  '--directory='$build_directory
							  '--jobs='$threads)

	declare -r install_command=('make'
								'--directory='$build_directory
								'install')

else
	_print_error 'missing build system:' 'ninja'
	_print_error 'missing build system:' 'make'
	exit 1
fi

# configure the build
if ! cmake -S $repo_directory -B $build_directory $cmake_flags; then
	_print_error 'failed to configure:' $library_name
	exit 1
fi

# build the library
if ! $build_command; then
	_print_error 'failed to build:' $library_name
	exit 1
fi


# -- I N S T A L L ------------------------------------------------------------

# install the library
if ! $install_command; then
	_print_error 'failed to install:' $library_name
	exit 1
fi


# -- C L E A N U P ------------------------------------------------------------

# cleanup
if ! rm -rf $repo_directory; then
	echo 'failed to cleanup:' $repo_directory
	exit 1
fi
