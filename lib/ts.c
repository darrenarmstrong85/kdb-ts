#include"k.h"
#include <sys/timerfd.h>
#include <unistd.h>
#include <iostream>

int timerfd=0;

// from code.kx.com
I up(J f){return (f/8.64e13+10957)*8.64e4;}  // unix from kdb+ timestamp
J pu(I u){return 8.64e13*(u/8.64e4-10957);}  // kdb+ timestamp from unix


extern "C" {
	K start(K dummy) {
		if(timerfd) {
			return krr((S) "Timer already started");
		}

		timerfd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
		return ki(timerfd);
	}

	K stop(K dummy) {
		if(not timerfd) {
			return krr((S) "Timer not started");
		}
		close(timerfd);
		return ki(timerfd);
	}

	K getnext (K dummy) {
		if(not timerfd) return ktj(-KN,nj);

		struct itimerspec spec;
		timerfd_gettime(timerfd, &spec);
		J ns = pu(spec.it_value.tv_sec) + spec.it_value.tv_nsec;
		K timeuntil = ktj(-KP, ns!=0 ? ns : nj);
		return timeuntil;
	}

	K setnext (K nexttime) {
		if(not timerfd) return krr((S)"Timer not started");

		itimerspec newtimer;

		newtimer.it_value.tv_sec = up(nexttime->j);
		newtimer.it_value.tv_nsec = nexttime->j%(J)1e9;
		newtimer.it_interval.tv_sec = 0;
		newtimer.it_interval.tv_nsec = 0;

		timerfd_settime(timerfd, 0, &newtimer, nullptr);

		return getnext((K) 0);
	}

}
