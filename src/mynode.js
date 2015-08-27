
Module.require  = function(id) {
	var cache = Module.getCached(id);

	if(cache) {
		return cache.exports;
	}	
	
	var module = new Module(id);	

	module.load();	
	module.cache();
	return module.exports;
}

function Module(id) {
	this.fileName = id+".js";
	this.id = id;
	this.exports = {};
}

Module.wrapper = [
	'(function(exports,require){ ',
	'\n});'
];

Module._cache = {};

Module.prototype.wrap = function(script) {
	return Module.wrapper[0] + script + Module.wrapper[1];
}

Module.prototype.load = function () {
	
	
	var script = loadScript(this.fileName);	
	script = this.wrap(script);
	var fn = runScript(script);
	fn(this.exports,Module.require);
}

Module.getCached = function(id) {
	return Module._cache[id];
}

Module.prototype.cache = function() {
	Module._cache[this.id] = this;
}



this.require = Module.require
this.Timer = binding('timer').Timer;



print('----------');
print(this.Timer.now());
//var timer = new Timer();
//timer[0] = onTimeout;
//timer.start(5,0);
function onTimeout(){
    print('---timeout---');
}




var timer = require('/Users/hannahzhang/code/v8_work/mynode/src/timer');




timer.setTimeout(onTimeout,3000);




//this.console = require('/Users/kenvi/code/study/mynode/src/console');

