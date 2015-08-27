var Timer = binding('timer').Timer;

var kOnTimeout = Timer.kOnTimeout | 0;

var TIMEOUT_MAX = 2147483647;

exports.setTimeout = function(callback, after) {
	var timer;
	
	after *= 1;

    if (!(after >=1 && after <= TIMEOUT_MAX)) {
		after = 1;
    }
	
	timer = new Timer();

    if (arguments.length <= 2) {
		timer[kOnTimeout]= callback;
     } else {
		var args = Array.prototype.slice.call(arguments, 2);
		timer[kOnTimeout]= function() {
			callback.apply(timer, args);
		}
	 }
	timer.start(after/1000, after%1000);
}




	
