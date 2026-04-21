/* $begin tinymain */
/*
 * tiny.c - A simple, iterative HTTP/1.0 Web server that uses the
 *     GET method to serve static and dynamic content.
 *
 * Updated 11/2019 droh
 *   - Fixed sprintf() aliasing issue in serve_static(), and clienterror().
 */
#include "csapp.h"

void doit(int fd);
void read_requesthdrs(rio_t *rp);
int parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg,
                 char *longmsg);

int main(int argc, char **argv)
{
  int listenfd, connfd;
  char hostname[MAXLINE], port[MAXLINE];
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;

  /* Check command line args */
  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }

  listenfd = Open_listenfd(argv[1]);
  while (1)
  {
    clientlen = sizeof(clientaddr);
    connfd = Accept(listenfd, (SA *)&clientaddr,
                    &clientlen); // line:netp:tiny:accept
    Getnameinfo((SA *)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE,
                0);
    printf("Accepted connection from (%s, %s)\n", hostname, port);
    doit(connfd);  // line:netp:tiny:doit
    Close(connfd); // line:netp:tiny:close
  }
}

/* doit() : 한 개의 HTTP 트랜잭션 처리하는 함수 */
/* 코드 흐름
1. 요청 라인(request line) 읽기
2. GET인지 확인
3. 나머지 헤더 읽고 버리기
4. URI를 파일 경로/CGI 인자로 해석
5. 파일 존재 여부 확인
6. 정적이면 읽기 권환 검사 후 파일 전송
7. 동적이면 실행 권한 검사 후 CGI 실행
*/
void doit(int fd) // fd : 클라이언트와 연결된 소켓 descriptor
{
  int is_static; // 요청한 URI가 정적 콘텐츠인지 여부를 저장할 변수 -> 1이면 static, 0이면 dynamic
  struct stat sbuf; // 시스템 콜의 결과를 담을 구조체 : 파일 존재, 권한 여부, 크기
  char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE]; // HTTP 요청 라인을 파싱하기 위한 버퍼
  char filename[MAXLINE], cgiargs[MAXLINE]; //filename : 실제 파일 경로, cgiargs: CGI 프로그램에 넘길 query string 인자
  rio_t rio; //Robust I/O 버퍼 구조체

  // 요청 읽기 단계 진입
  Rio_readinitb(&rio, fd); //rio 버퍼를 이 연결 소켓 fd에 묶어서 초기화
  Rio_readinitb(&rio, buf, MAXLINE); // 클라이언트가 보낸 첫 줄, request line 읽음
  printf("Request headers\n"); //출력 흐름 시작
  printf("%s", buf); //디버깅용 로그
  sscanf(buf, "%s %s %s", method, uri, version); // request line을 세 부분으로 파싱
  if(strcaseemp(method, "GET")) { //strcaseemp : 대소문자 무시 문자열 비교
    clienterror(fd, method, "501", "Not implemented", "Tiny does not implement this method");
    return;
  }

  // request line 다음에 오는 HTTP 헤더를 읽고 무시
  rio_requesthdrs(&rio);

  // URI를 실제 처리 가능한 서버 내부 정보로 바꾸겠다
  is_static = parse_uri(uri, filename,  cgiargs); //static이면 filename을, dynamic이면 ?뒤를 cgiargs로 분리 
  // stat으로 해당 filename의 상태를 읽어와라
  if (stat(filename, &buf) < 0) {
    clienterror(fd, filename, "404", "Not found", "Tiny coudln't find this file");
    return;
  }

  // parse_uri 결과가 static인 경우 : 파일을 보내기 전에 안정성/유효성 검사 
  if(is_static) { 
    if(!(IS_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) { // 일반파일인가 or 소유자 읽기 권한이 있는가
      clienterror(fd, filename, "403", "Forbidden", "Tiny couldn't read the file");
      return;
    }
    serve_static(fd, filename, sbuf.st_size); // 검사 통과했으면 정적 파일 보냄
  } else {
    if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)){ // 일반파일인가 or 실행 권한이 있는가
      clienterror(fd, filenmae, "403", "Forbidden","Tiny couldn't run the CGI program");
      return;
    }
    serve_dynamic(fd, filename, cgiargs);
  }





}