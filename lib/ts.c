#include"k.h"
#include <sys/timerfd.h>
#include <unistd.h>
#include <iostream>

int timerfd=0;

extern "C" {
	K start(K dummy) {
		if(not timerfd) {
			timerfd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
		}

		return ki(timerfd);
	}

	K stop(K dummy) {
		if(not timerfd) {
			close(timerfd);
		}
		return ki(timerfd);
	}

	K setnext (K dummy) {
		return (K) 0;
	}

	K getnext (K dummy) {
		if(not timerfd) return ktj(-KN,nj);

		struct itimerspec spec;
		timerfd_gettime(timerfd, &spec);
		std::cout << spec.it_interval.tv_sec << "\t" << spec.it_interval.tv_nsec << "\t"
				  << spec.it_value.tv_sec << "\t" << spec.it_value.tv_nsec << std::endl;
		J ns = (1e9 * spec.it_value.tv_sec) + spec.it_value.tv_nsec;
		K timeuntil = ktj(-KN, ns!=0 ? ns : nj);
		return timeuntil;
	}
}
