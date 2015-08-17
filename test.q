/
  Test script for ts library.

    - Loads ts
	- Loads callback function in case it's necessary
	- Sets a timer to fire in 5 seconds, shows result
	- Retrieves that timer (should be very similar to above +/- jitter)
\

.utl.require "ts"

\d .ts

start[".ts.private.callback"];

0N!(`setevent;)private.setnext {0N!(`nextevent;.z.p;x);x}.z.p+00:00:01;

0N!(`retrievedevent;)private.getnext[];

-1 "end script";

\d .

\
cbk:libpath 2:(`callback;1);

cbk[];
