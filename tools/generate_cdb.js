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


// another approach


//// get filesystem module
//const fs = require('fs');
//
//// get arguments
//const [root_dir, src, obj, cxx, cxxflags] = process.argv.slice(2);
//
//// convert flags to array
//const cxxflags_array = cxxflags.split(' ');
//
//// Check if compile_commands.json exists
//let compile_commands = [];
//if (fs.existsSync('compile_commands.json')) {
//	compile_commands = JSON.parse(fs.readFileSync('compile_commands.json', 'utf-8'));
//}
//
//// Check if the file is already present in compile_commands.json
//const file_exists = compile_commands.some(entry => entry.file === src);
//
//if (!file_exists) {
//	// Add new entry to compile_commands.json
//	const new_entry = {
//		directory: root_dir,
//		file: src,
//		output: obj,
//		arguments: [cxx, ...cxxflags_array, '-c', src, '-o', obj]
//	};
//
//	// Append the new entry
//	compile_commands.push(new_entry);
//
//	// Write the updated compile_commands.json
//	fs.writeFileSync('compile_commands.json', JSON.stringify(compile_commands, null, '\t'));
//
//	console.log(`Added ${src} to compile_commands.json`);
//}
