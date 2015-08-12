#include"k.h"
#include <sys/timerfd.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

int timerfd=0;

// from code.kx.com
I up(J f){return (f/8.64e13+10957)*8.64e4;}  // unix from kdb+ timestamp
J pu(I u){return 8.64e13*(u/8.64e4-10957);}  // kdb+ timestamp from unix


K callback(int fd) {
	uint64_t num_expirations = 0;
	ssize_t num_read = 0;
	while((num_read = read(timerfd, &num_expirations, sizeof(uint64_t))) != -1) {
		k(0, (S)".ts.private.callback", kj(num_expirations), (K)0);
	}

	return ki(0);
}

extern "C" {
	K start(K dummy) {
		if(timerfd) {
			return krr((S) "alreadystarted");
		}

		timerfd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
		sd1(timerfd, &callback);
		return ki(timerfd);
	}

	K stop(K dummy) {
		if(not timerfd) {
			return krr((S) "notstarted");
		}

		callback(timerfd);
		close(timerfd);
		return ki(timerfd);
	}

	K getnext (K dummy) {
		if(not timerfd) return ktj(-KN,nj);

		struct itimerspec spec;
		if(timerfd_gettime(timerfd, &spec) != 0) {
			std::cout << "ts:getnext:error: " << strerror(errno) << std::endl;
		}

		J ns = 0;
		ns += spec.it_value.tv_sec*(J)1e9;
		ns += (J)spec.it_value.tv_nsec;
		K timeuntil = ktj(-KN, ns!=0 ? ns : nj);
		return timeuntil;
	}

	K setnext (K nexttime) {
		if(not timerfd) return krr((S)"notstarted");

		itimerspec newtimer;
		itimerspec oldtimer;

		newtimer.it_interval.tv_sec = 0;
		newtimer.it_interval.tv_nsec = 0;
		newtimer.it_value.tv_sec = (nexttime->j) / (J)1e9;
		newtimer.it_value.tv_nsec = nexttime->j%(J)1e9;

		std::cout << newtimer.it_value.tv_nsec << " " << newtimer.it_value.tv_sec << std::endl;

		if(timerfd_settime(timerfd, 0, &newtimer, &oldtimer) != 0) {
			std::cout << "ts:setnext:error: " << strerror(errno) << std::endl;
		}

		return getnext((K) 0);
	}
	K cbk(K dummy) {
		if(timerfd) callback(timerfd);
	}
}
