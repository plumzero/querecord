#pragma once

#include <signal.h>
#include <time.h>
#include <functional>
#include <iostream>
#include <memory>

class PosixTimer {
 public:
  using TimerCallback = std::function<void()>;

  PosixTimer() : timerid_(CreateTimerid()) {}

  void StartTimer(uint64_t interval_ms, const TimerCallback &call_back) {
    call_back_ = call_back;
    interval_ms_ = interval_ms;

    SetTime();
  }

  ~PosixTimer() { timer_delete(timerid_); }

 private:
  static void TimerEntry(union sigval sv) {
    if (nullptr != sv.sival_ptr) {
      PosixTimer *timer = (PosixTimer *)sv.sival_ptr;
      timer->Drive();
    }
  }

  PosixTimer(const PosixTimer &) = delete;

  PosixTimer &operator=(const PosixTimer &) = delete;

  void SetTime() {
    timespec timeval{};
    timeval.tv_sec = interval_ms_ / 1000;
    timeval.tv_nsec = interval_ms_ % 1000 * 1000000;
    if (timeval.tv_sec == 0 && timeval.tv_nsec == 0) {
      timeval.tv_nsec = 1;
    }

    struct itimerspec new_value {
      {0, 0}, timeval
    };
    struct itimerspec old_value = {};

    if (-1 == timer_settime(timerid_, 0, &new_value, &old_value)) {
      std::cerr << "timer_settime failed!" << std::endl;
    }
  }

  void Drive() {
    call_back_();

    SetTime();
  }

  timer_t CreateTimerid() {
    struct ::sigevent sev {};
    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = TimerEntry;
    sev.sigev_notify_attributes = nullptr;
    sev.sigev_value.sival_ptr = this;

    timer_t timerid{};
    if (-1 == timer_create(CLOCK_REALTIME, &sev, &timerid)) {
      std::cerr << "timer_create failed!" << std::endl;
      return nullptr;
    }

    return timerid;
  }

 private:
  timer_t timerid_{};
  uint64_t interval_ms_{};
  TimerCallback call_back_;
};