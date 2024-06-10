#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "test_pop.cpp"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"


struct Time {
    int hours, minutes, seconds;
    long nanoseconds;
};

struct Time get_time(long time_taken) {
    double seconds_total = (double) time_taken / 1e9;
    struct Time time;
    time.hours = (int) (seconds_total / 3600);
    seconds_total -= time.hours * 3600;
    time.minutes = (int) (seconds_total / 60);
    seconds_total -= time.minutes * 60;
    time.seconds = (int) seconds_total;
    seconds_total -= time.seconds;
    time.nanoseconds = (int) (seconds_total * 1e9);
    return time;
}

char *time_to_string(struct Time time) {
    char *time_str = static_cast<char *>(malloc(30 * sizeof(char)));
    sprintf(time_str, "%02d:%02d:%02d.%09ld", time.hours, time.minutes, time.seconds, time.nanoseconds);
    return time_str;
}

long diff(struct timespec start, struct timespec end) {
    long diff = (end.tv_sec - start.tv_sec) * (long) 1e9;
    diff += end.tv_nsec - start.tv_nsec;
    return diff;
}

void run_test(bool (*func_to_run)(), char *test_name) {
    struct timespec t_start, t_end;
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    bool result = func_to_run();
    clock_gettime(CLOCK_MONOTONIC, &t_end);
    struct Time time = get_time(diff(t_start, t_end));

    if (result) {
        printf(GREEN "Test <%s> PASSED; Time taken: %s\n" RESET, test_name, time_to_string(time));
    } else {
        printf(RED "Test <%s> FAILED\n" RESET, test_name);
    }
}

int main() {
    run_test(test_delete_root_both_empty, "Test delete root without both");
    run_test(test_delete_root_without_right, "Test delete root without right");
    run_test(test_delete_root_without_right_short, "Test delete root without right short");
    run_test(test_delete_root_without_left, "Test delete root without left");
    run_test(test_delete_root_without_left_short, "Test delete root without left short");
    run_test(test_delete_root, "Test delete root");
    run_test(test_delete_when_element_not_exist, "Test delete when element not exist");
    run_test(test_delete_step_by_step, "Test delete step by step");
    return 0;
}