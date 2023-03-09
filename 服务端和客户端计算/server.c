#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <math.h>
#define MAX_EXPRESSION_LENGTH 256
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
double evaluate_expression(char *expression)
{
    int i, j, len;
    double num_stack[MAX_EXPRESSION_LENGTH];
    char op_stack[MAX_EXPRESSION_LENGTH];
    int num_top = -1, op_top = -1;
    len = strlen(expression);
    for (i = 0; i < len; i++) {
        if (expression[i] == ' ') {
            continue;
        } else if (expression[i] >= '0' && expression[i] <= '9') {
            double num = 0;
            while (i < len && expression[i] >= '0' && expression[i] <= '9') {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            if (i < len && expression[i] == '.') {
                i++;
                double frac = 0.1;
                while (i < len && expression[i] >= '0' && expression[i] <= '9') {
                    num += frac * (expression[i] - '0');
                    frac /= 10;
                    i++;
                }
            }
            num_stack[++num_top] = num;
            i--;
        } else {
            while (op_top >= 0 && (op_stack[op_top] == '*' || op_stack[op_top] == '/' || op_stack[op_top] == '+' || op_stack[op_top] == '-')) {
                double num2 = num_stack[num_top--];
                double num1 = num_stack[num_top--];
                char op = op_stack[op_top--];
                double result;
                switch (op) {
                    case '*':
                        result = num1 * num2;
                        break;
                    case '/':
                        result = num1 / num2;
                        break;
                    case '+':
                        result = num1 + num2;
                        break;
                    case '-':
                        result = num1 - num2;
                        break;
                }
                num_stack[++num_top] = result;
            }
            op_stack[++op_top] = expression[i];
        }
    }
    while (op_top >= 0) {
        double num2 = num_stack[num_top--];
        double num1 = num_stack[num_top--];
        char op = op_stack[op_top--];
        double result;
        switch (op) {
            case '*':
                result = num1 * num2;
                break;
            case '/':
                result = num1 / num2;
                break;
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
        }
        num_stack[++num_top] = result;
    }
    return num_stack[0];
}
int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[MAX_EXPRESSION_LENGTH];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,&clilen);
    if (newsockfd < 0) 
        error("ERROR on accept");
    bzero(buffer, MAX_EXPRESSION_LENGTH);
    n = read(newsockfd, buffer, MAX_EXPRESSION_LENGTH - 1);
    if (n < 0) error("ERROR reading from socket");
    printf("Here is the expression: %!s\n", buffer);
    double result = evaluate_expression(buffer);
    bzero(buffer, MAX_EXPRESSION_LENGTH);
    sprintf(buffer, "%f", result);
    n = write(newsockfd, buffer, strlen(buffer));
    if (n < 0) error("ERROR writing to socket");
    close(newsockfd);
    close(sockfd);
    return 0; 
}
