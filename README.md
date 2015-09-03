# kdb-ts

## Description

Event timer library for kdb.  Provides multiple high-efficiency
implementations of timer loops, which are picked based on availability
and suitability to operating system.

 - Linux: timerfd.  Events implmented as sd1/read() on timerfd.
   timerfd allows for nanosecond resolution of event specification.

 - Default handler: Uses q's system["t"] api to specify the next event
   timer.  Allows for millisecond resolution.

## Notes on resolution vs accuracy

There are several issues to address here.

True nanosecond resolution timing sources remain the exception rather
than the rule and the usual interfaces used in modern operating
systems stop at microsecond resolution at best.  So any applications
requiring very high resolution should bear this in mind.

Accuracy at these timescales is also a very hard problem: using the
best-in-class sources (e.g. GPS hardware) along with well implemented
NTP or PTP systems, you may be able to maintain clock sychronization
to <1ms, perhaps even a few hundred microseconds.  At this timescale
any concept of 'absolute time' between sources becomes a bit hairy and
you should account for this in your design also.

Finally, whilst I am confident in the design of the API and event
loops within this code, it has not been designed with *hard* real-time
constraints in mind.  In particular:

 - There has been no attempt to ensure fairness or to avoid priority
   inversion between events; patches welcome if you happen to know how
   to do this.

 - Event lookups will display linear complexity (at best!) with number
   of events, regardless of frequency of calls.  It's possible that
   this could be improved by using a hash lookup on event ids and
   looking up the next event id, reducing most maintenance logic to
   constant-time lookups and updates.  I did consider making the
   events table a sorted step-lookup but did not have an obvious
   solution to the problem of having two events with identical timers.
   This also leads me to the next consideration...

 - I have developed this library from the outset to prefer simplicity
   over cleverness.  Right now this is a pet project for me and I want
   to enjoy it :-) Changes will be made based on their maintainability
   as much as possible.
