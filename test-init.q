/
  Test script for ts library.

    - Loads ts
	- Loads callback function in case it's necessary
	- Sets a timer to fire in 5 seconds, shows result
	- Retrieves that timer (should be very similar to above +/- jitter)
\

.utl.require "ts"

func:{[t;id]
  0N!(`func;id;t;.z.p);
  }

.ts.add[func;.z.p;] enlist[`interval]!enlist 00:00:05n;
-1 "end script";

.z.ts:0N!

\t 1000
