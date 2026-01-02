#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    // Open connection to the system logger for a program.
    openlog(NULL, 0, LOG_USER);

    // Verify expected number of arguments are provided to the script
    if (argc < 3) {
        syslog(LOG_ERR, "Invalid number of arguments: %d", argc);
        return 1;
    }

    // Verify full path to a file is provided and open if it exists.
    // If it doesn't exist, create the file
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        syslog(LOG_ERR, "Invalid file path: %s", argv[1]);
        return 1;
    }

    // Verify text string is provided
    char* buf = argv[2];
    if (buf[0] == '\0') {
        syslog(LOG_ERR, "Invalid text string: %s", buf);
        return 1;
    }

    // Write text to the file
    syslog(LOG_DEBUG, "Writing %s to %s", argv[1], argv[2]);
    ssize_t n = write(fd, buf, strlen(buf));
    if (n == -1) {
        const int err = errno;
        syslog(LOG_ERR, "Failed to write: %s", strerror(err));
    } else if(n != strlen(buf)) {
        syslog(LOG_ERR, "Failed to write complete text");
    }

    closelog();

    return 0;
}

