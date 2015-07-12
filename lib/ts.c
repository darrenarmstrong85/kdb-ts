#include"k.h"
#include <sys/timerfd.h>
#include <unistd.h>

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
		return (K) 0;
	}
}
