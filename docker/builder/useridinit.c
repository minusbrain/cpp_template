#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

int main(void)
{
    char scratch[1024];
    int result = 0;

    uid_t u_id = getuid();
    gid_t g_id = getgid();

    if (u_id == 0 || g_id == 0) {
        return 0;
    }

    struct passwd *c_pwd = getpwuid(u_id);
    if (c_pwd != NULL && strcmp(c_pwd->pw_name, "user") != 0) {
        // the user already exists and has a different name then "user"
        return 0;
    }

    struct passwd *u_pwd = getpwnam("user");
    struct group *u_grp = getgrnam("user");
    if (u_pwd == NULL) {
        printf("Error obtaining passwd information user\n");
        return -1;
    }
    if (u_grp == NULL) {
        printf("Error obtaining group information user\n");
        return -1;
    }

    if (u_pwd->pw_uid == u_id && u_pwd->pw_gid == g_id) {
        return 0;
    }

    // change the id of group "user"
    result = sprintf (scratch, "groupmod -g %d user", g_id);
    if (result < 0) {
        printf("Error formatting groupmod command: %d\n", result);
        return result;
    }

    setreuid(geteuid(), getuid());
    FILE *p_groupmod = popen(scratch, "r");
    setreuid(geteuid(), getuid());
    if (p_groupmod == NULL) {
        printf("Error launching groupmod\n");
        return -3;
    }

    result = pclose(p_groupmod);
    if (result != 0) {
        printf("groupmod utility exited with %d\n", result);
        return result;
    }

    // change id of "user"
    result = sprintf (scratch, "usermod -u %d -g %d user", u_id, g_id);
    if (result < 0) {
        printf("Error formatting usermod command: %d\n", result);
        return result;
    }

    setreuid(geteuid(), getuid());
    FILE *p_usermod = popen(scratch, "r");
    setreuid(geteuid(), getuid());
    if (p_usermod == NULL) {
        printf("Error launching usermod\n");
        return -3;
    }

    result = pclose(p_usermod);
    if (result != 0) {
        printf("usermod utility exited with %d\n", result);
        return result;
    }

    // change ownership of home directory
    result = sprintf (scratch, "chown %d:%d /home/user /home/user/.profile /home/user/.bashrc /home/user/.bash_logout", u_id, g_id);
    if (result < 0) {
        printf("Error formatting chown command: %d\n", result);
        return result;
    }

    setreuid(geteuid(), getuid());
    FILE *p_chown = popen(scratch, "r");
    setreuid(geteuid(), getuid());
    if (p_usermod == NULL) {
        printf("Error launching chown\n");
        return -3;
    }

    result = pclose(p_usermod);
    if (result != 0) {
        printf("chown utility exited with %d\n", result);
        return result;
    }

    return 0;
}
