#include <unistd.h>
#include "profiling.h"

int main() {
    TIME_THIS(getpid());
}