// get filesystem module
const fs = require('fs');

// get arguments
const [root_dir, srcs, objs, cxx, cxxflags] = process.argv.slice(2);

// convert arguments to array
const srcs_array     =     srcs.split(' ');
const objs_array     =     objs.split(' ');
const cxxflags_array = cxxflags.split(' ');

// create cdb file
const compile_commands = srcs_array.map((src, i) => ({
	directory: root_dir,
	file: src,
	output: objs_array[i],
	arguments: [cxx, ...cxxflags_array, '-c', src, '-o', objs_array[i]]
}));

// write cdb file
fs.writeFileSync('compile_commands.json', JSON.stringify(compile_commands, null, '\t'));
