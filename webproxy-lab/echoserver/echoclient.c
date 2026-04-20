/*
 * echoclient.c - Echo 클라이언트 구현 파일
 *
 * 사용자가 입력한 텍스트를 서버에 보내고,
 * 서버가 되돌려 보낸 내용을 받아 화면에 출력한다.
 * csapp 라이브러리를 활용하여 소켓 통신을 구현한다.
 *
 * 사용법: ./echoclient <host> <port>
 *   host : 접속할 서버의 호스트명 또는 IP 주소 (예: localhost)
 *   port : 접속할 서버의 포트 번호 (예: 8080)
 */

#include "../csapp.h"

int main(int argc, char **argv)
{
    /* clientfd: 서버와 연결된 소켓 파일 디스크립터 */
    /* n: 읽은 바이트 수 */
    /* buf: 사용자 입력 및 서버 응답을 임시 저장하는 버퍼 (MAXLINE 크기) */
    /* rio: Robust I/O 구조체 - 안정적인 읽기/쓰기를 위해 사용 */
    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio;

    /* 명령줄 인수로 호스트명과 포트 번호를 받아야 한다 */
    /* 인수 개수가 부족하면 사용법을 출력하고 종료 */
    /* 사용법 예시: fprintf(stderr, "usage: %s <host> <port>\n", argv[0]); */
    if(argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }


    /* Open_clientfd()를 사용해 argv[1](호스트), argv[2](포트)로 서버에 연결한다 */
    /* 연결 성공 시 clientfd에 소켓 fd가 저장된다 */
    host = argv[1];
    port = argv[2];

    /* Rio_readinitb()로 rio 구조체를 clientfd에 연결하여 초기화한다 */
    /* 이후 서버로부터 데이터를 읽을 때 이 rio 구조체를 사용한다 */
    clientfd = Open_readinitb(host, port);
    Rio_readinitb(&rio, clientfd);

    /* 루프: 사용자가 EOF(Ctrl+D)를 입력할 때까지 반복 */
    /* Fgets()로 표준 입력(stdin)에서 한 줄을 읽어 buf에 저장한다 */
    /* Fgets()가 NULL을 반환하면 EOF이므로 루프를 종료한다 */
    while (Fgets(buf, MAXLINE, stdin) != NULL) {


        /* Rio_writen()으로 buf의 내용을 서버에 전송한다 */
        /* 전송 크기는 strlen(buf)로 계산한다 */
        Rio_writen(clientfd, buf, strlen(buf));

        /* Rio_readlineb()로 서버가 되돌려 보낸 응답을 한 줄 읽는다 */
        /* Fputs()로 읽은 응답을 표준 출력(stdout)에 출력한다 */
        Rio_readlineb(&rio, buf, MAXLINE);
        Fputs(buf, stdout);

    /* Close()로 clientfd를 닫고 서버와의 연결을 종료한다 */
    }
    Close(clientfd);
    exit(0);
    return 0;
}
