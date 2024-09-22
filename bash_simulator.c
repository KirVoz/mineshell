#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_INPUT 1000
#define MAX_OUTPUT 5000
#define INPUT_FILE "stored_inputs.txt"

char* custom_shell_path = "/Users/aleks/Developer/42/minishell/minishell";

void run_command_with_redirect(const char* command, char* output, char* error, int* exit_code, const char* shell) {
    char temp_out[] = "/tmp/out_XXXXXX";
    char temp_err[] = "/tmp/err_XXXXXX";
    int fd_out = mkstemp(temp_out);
    int fd_err = mkstemp(temp_err);

    if (fd_out == -1 || fd_err == -1) {
        perror("Failed to create temporary file");
        return;
    }

    char redirect_command[MAX_INPUT + 100];
    snprintf(redirect_command, sizeof(redirect_command), "%s \"%s\" > %s 2> %s", shell, command, temp_out, temp_err);

    FILE* pipe = popen(redirect_command, "r");
    if (pipe == NULL) {
        snprintf(error, MAX_OUTPUT, "Failed to run command: %s", strerror(errno));
        *exit_code = -1;
    } else {
        int pclose_result = pclose(pipe);
        *exit_code = WIFEXITED(pclose_result) ? WEXITSTATUS(pclose_result) : -1;

        // Read stdout
        FILE* out_file = fdopen(fd_out, "r");
        if (out_file) {
            fseek(out_file, 0, SEEK_END);
            long out_size = ftell(out_file);
            fseek(out_file, 0, SEEK_SET);
            fread(output, 1, out_size < MAX_OUTPUT ? out_size : MAX_OUTPUT - 1, out_file);
            fclose(out_file);
        }

        // Read stderr
        FILE* err_file = fdopen(fd_err, "r");
        if (err_file) {
            fseek(err_file, 0, SEEK_END);
            long err_size = ftell(err_file);
            fseek(err_file, 0, SEEK_SET);
            fread(error, 1, err_size < MAX_OUTPUT ? err_size : MAX_OUTPUT - 1, err_file);
            fclose(err_file);
        }
    }

    unlink(temp_out);
    unlink(temp_err);
    close(fd_out);
    close(fd_err);
}

void run_command(const char* command) {
    char bash_output[MAX_OUTPUT] = {0};
    char bash_error[MAX_OUTPUT] = {0};
    char custom_shell_output[MAX_OUTPUT] = {0};
    char custom_shell_error[MAX_OUTPUT] = {0};
    int bash_exit_code, custom_shell_exit_code;
    
    run_command_with_redirect(command, bash_output, bash_error, &bash_exit_code, "/bin/bash -c");
    
    if (custom_shell_path) {
        run_command_with_redirect(command, custom_shell_output, custom_shell_error, &custom_shell_exit_code, custom_shell_path);
    }

    // Display outputs and compare
    printf("Command: %s\n", command);
    printf("Bash output:\n%s\n", bash_output);
    if (bash_error[0] != '\0') {
        printf("Bash error:\n%s\n", bash_error);
    }
    printf("Bash exit code: %d\n\n", bash_exit_code);

    if (custom_shell_path) {
        printf("Custom shell output:\n%s\n", custom_shell_output);
        if (custom_shell_error[0] != '\0') {
            printf("Custom shell error:\n%s\n", custom_shell_error);
        }
        printf("Custom shell exit code: %d\n\n", custom_shell_exit_code);

        printf("Output Match: %s\n", strcmp(bash_output, custom_shell_output) == 0 ? "Yes" : "No");
        printf("Error Match: %s\n", strcmp(bash_error, custom_shell_error) == 0 ? "Yes" : "No");
        printf("Exit Code Match: %s\n", bash_exit_code == custom_shell_exit_code ? "Yes" : "No");
    }
    printf("\n");
}

void run_stored_inputs() {
    FILE* file = fopen(INPUT_FILE, "r");
    if (file == NULL) {
        printf("Input file '%s' not found. Please create it and add commands.\n", INPUT_FILE);
        return;
    }

    char input[MAX_INPUT];
    while (fgets(input, sizeof(input), file)) {
        input[strcspn(input, "\n")] = 0; // Remove newline
        if (strlen(input) > 0) {  // Skip empty lines
            run_command(input);
        }
    }

    fclose(file);
}

void interactive_shell() {
    char input[MAX_INPUT];
    printf("\nStarting interactive mode. Type 'exit' to quit.\n");
    while (1) {
        printf("$ ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Remove newline
        
        if (strcmp(input, "exit") == 0) {
            break;
        }
        
        run_command(input);
    }
}

int main(int argc, char *argv[]) {
    int interactive_mode = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            interactive_mode = 1;
        } else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            custom_shell_path = argv[i + 1];
            i++;  // Skip the next argument
        }
    }

    if (custom_shell_path) {
        printf("Using custom shell: %s\n", custom_shell_path);
    } else {
        printf("Error: Custom shell path not provided. Use -s option to specify the path.\n");
        return 1;
    }

    if (interactive_mode) {
        interactive_shell();
    } else {
        printf("Running stored inputs from '%s':\n", INPUT_FILE);
        run_stored_inputs();
    }
    
    return 0;
}