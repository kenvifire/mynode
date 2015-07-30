
function Module(id) {
	this.fileName = id+".js";
	this.id = id;
	this.exports = {};
}

Module.wrapper = [
	'(function(){ ',
	'\n});'
];

Module.prototype.wrap = function(script) {
	return Module.wrapper[0] + script + Module.wrapper[1];
}

Module.prototype.load = function () {
	var script = loadScript(this.fileName);	
	script = this.wrap(script);
	var fn = runScript(script);
	fn();
}

var module = new Module('/Users/kenvi/code/study/mynode/src/module');
module.load();



