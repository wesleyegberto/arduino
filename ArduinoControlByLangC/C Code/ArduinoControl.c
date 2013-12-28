#include <stdio.h>    // Standard input/output definitions
#include <unistd.h>   // UNIX standard function definitions
#include <fcntl.h>    // File control definitions
#include <errno.h>    // Error number definitions
#include <termios.h>  // POSIX terminal control definitions
#include <string.h>   // String function definitions
#include <sys/ioctl.h>

#define MAX_LENGHT 20

void printMenu();
void sendCommand(char command);

int main() {
    int opc;
    while(1 == 1) {
        printMenu();
        scanf("%d", &opc);
       
        switch(opc) {
            case 1:
                sendCommand('R');
                break;
            case 2:
                sendCommand('Y');
                break;
            case 3:
                sendCommand('G');
                break;
            case 4:
                sendCommand('L');
                break;
            default: 
                printf("\nInvalid command");
                break;
        }
    }
}

void printMenu() {
    printf("\n%s\n%s\n%s\n%s\n%s\n%s",
    "**************Command menu**************",
    "1) Turn on red LED",
    "2) Turn on yellow LED",
    "3) Turn on green LED",
    "4) Read the luminosity",
    "\nEnter the command: ");
}

void sendCommand(char command) {
   // Open the Arduino's Serial file
    struct termios toptions;
    int port = open("/dev/ttyACM0", O_RDWR | O_NONBLOCK);
    
    if(port == -1) {
        printf("\nCommunication with Arduino failed");
        return;
    }
    
    speed_t brate = B9600;
    cfsetispeed(&toptions, brate);
    cfsetospeed(&toptions, brate);
    
     // 8N1
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    // no flow control
    toptions.c_cflag &= ~CRTSCTS;
    //toptions.c_cflag &= ~HUPCL; // disable hang-up-on-close to avoid reset
    toptions.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl
    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    toptions.c_oflag &= ~OPOST; // make raw
    toptions.c_cc[VMIN]  = 0;
    toptions.c_cc[VTIME] = 0;
    
    tcsetattr(port, TCSANOW, &toptions);
    
    
    char cmd[1];
    cmd[0] = command;
    int len = strlen(cmd);
    printf("\nSending the command %c", command);
    int resp = write(port, &cmd, len);
    
    if(resp != len) {
        printf("\nwhole string was not written");
        return;
    }
    
    printf("\nWaiting...");
    sleep(1);
 
    printf("\nReading response");
    int maxLen = 20; // max lenght of response
    char buffer[maxLen + 1]; // the response read
    char charRead[1]; // used to read a char
    int i = 0;
    while(i < maxLen && charRead[0] != '\n') {
        resp = read(port, charRead, 1);
        if(resp == -1) {
            printf("could not read the response from arduino");
            return;
        } else if(resp == 0) { // wait 1 sec before try again
            printf("\n    no response yet");
            sleep(1);
            continue;
        }
        buffer[i++] = charRead[0];
    }
    buffer[i] = '\n';
    
    printf("\nRead: ");
    puts(buffer);
    
    close(port);
}
