/*
 * echoserver.c - Echo 서버 구현 파일
 *
 * 클라이언트로부터 받은 데이터를 그대로 되돌려주는 서버.
 * csapp 라이브러리를 활용하여 소켓 통신을 구현한다.
 */

#include "../csapp.h"

/* 클라이언트와의 에코 통신을 처리하는 함수 선언 */
void echo(int connfd);

int main(int argc, char **argv)
{
    /* 명령줄 인수로 포트 번호를 받아야 한다 */
    /* 인수 개수가 부족하면 사용법을 출력하고 종료 */
    int listenfd, connfd; 
    socklen_t clientlen; // 이 주소 구조체가 몇 바이트짜리인지 나타내는 변수의 타입
    struct sockaddr_storage clientaddr; // 어떤 종류의 소켓 주소든 담을 수 있게 크게 만든 범용 주소 구조체 : IPv4, IPv6 등
    char client_hostname[MAXLINE], client_port[MAXLINE]; // 배열 크기를 정하는 상수 매크로

    if (argc !=2){
        fprintf(stderr, "usage:%s <port>\n", argv[0]);
        exit(0);
    }



    /* listenfd: 서버가 연결 요청을 기다리는 소켓 파일 디스크립터 */
    /* connfd:   클라이언트와 실제 통신에 사용하는 소켓 파일 디스크립터 */
    /* clientlen: 클라이언트 주소 구조체의 크기 */
    /* clientaddr: 클라이언트의 주소 정보를 담는 구조체 */
    /* client_hostname, client_port: 클라이언트의 호스트명과 포트 번호 문자열 */

    /* Open_listenfd()를 사용해 지정된 포트로 리스닝 소켓을 연다 */

    /* 무한 루프: 클라이언트 연결 요청을 반복적으로 처리 */
    while (1) {
        /* Accept()로 클라이언트 연결을 수락하고 connfd를 얻는다 */

        /* Getnameinfo()로 클라이언트의 호스트명과 포트 번호를 가져온다 */

        /* 연결된 클라이언트 정보를 출력한다 */

        /* echo() 함수를 호출해 에코 처리를 수행한다 */

        /* 에코가 끝나면 connfd를 닫는다 */
    }

    return 0;
}

/*
 * echo - 연결된 클라이언트로부터 한 줄씩 읽고 그대로 되돌려 보내는 함수
 *
 * @connfd: 클라이언트와 연결된 소켓 파일 디스크립터
 */
void echo(int connfd)
{
    /* n: 읽은 바이트 수 */
    /* buf: 데이터를 임시 저장하는 버퍼 (MAXLINE 크기) */
    /* rio: Robust I/O 구조체 - 안정적인 읽기/쓰기를 위해 사용 */

    /* Rio_readinitb()로 rio 구조체를 connfd에 연결하여 초기화한다 */

    /* 루프: 클라이언트가 보낸 데이터를 한 줄씩 읽는다 */
    /* Rio_readlineb()로 한 줄을 읽고, 읽은 바이트 수를 n에 저장한다 */
    /* n이 0이면 클라이언트가 연결을 끊은 것이므로 루프를 종료한다 */
    /* Rio_writen()으로 읽은 내용을 그대로 클라이언트에게 전송한다 */
}
