#include"k.h"
#include <sys/timerfd.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

int timerfd=0;
char * fn_callback;

K callback(int fd) {
	uint64_t num_expirations = 0;
	ssize_t num_read = 0;
	if((num_read = read(timerfd, &num_expirations, sizeof(uint64_t))) != -1)
		k(0, fn_callback, kj(num_expirations), (K)0);

	return ki(0);
}

extern "C" {
	K start(K cbk) {
		if(timerfd)	return krr((S) "alreadystarted");
		if(cbk->t != 10) return krr((S) "badcallback");

		fn_callback = static_cast<char *>( calloc(cbk->n+1, sizeof(char)) );
		memcpy(fn_callback, cbk->G0, cbk->n);

		timerfd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
		sd1(timerfd, &callback);
		return ki(timerfd);
	}

	K stop(K dummy) {
		int fd = timerfd;
		if(not timerfd)	return krr((S) "notstarted");

		sd0(timerfd);
		close(timerfd);
		timerfd=0;
		fn_callback = static_cast<char *>( calloc(1, sizeof(char)) );

		return ki(fd);
	}

	K getnext (K dummy) {
		if(not timerfd) return ktj(-KN,nj);

		struct itimerspec spec;
		if(timerfd_gettime(timerfd, &spec) != 0)
			return krr(
				(S) std::string("ts:getnext:error: " + std::string(strerror(errno))).c_str()
				);

		J ns = 0;
		ns += spec.it_value.tv_sec*(J)1e9;
		ns += (J)spec.it_value.tv_nsec;
		K timeuntil = ktj(-KN, ns!=0 ? ns : nj);
		return timeuntil;
	}

	K setnext (K nexttime) {
		if(not timerfd) return krr((S)"notstarted");

		itimerspec newtimer;
		newtimer.it_interval.tv_sec = 0;
		newtimer.it_interval.tv_nsec = 0;
		newtimer.it_value.tv_sec = (nexttime->j) / (J)1e9;
		newtimer.it_value.tv_nsec = nexttime->j%(J)1e9;

		if(timerfd_settime(timerfd, 0, &newtimer, nullptr) != 0)
			std::cout << "ts:setnext:error: " << strerror(errno) << std::endl;

		return getnext((K) 0);
	}

	K is_timer_set(K dummy) {
		return kb(timerfd == 0);
	}

	K cbk(K dummy) {
		if(timerfd) callback(timerfd);
	}
}
