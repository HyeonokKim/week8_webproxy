# echoserver 빌드를 위한 Makefile
#
# CC:      사용할 C 컴파일러를 지정한다 (gcc)
# CFLAGS:  컴파일 옵션을 지정한다
#          -g: 디버깅 심볼 포함
#          -Wall: 모든 경고 출력
#          -pthread: 멀티스레드 지원 (csapp 라이브러리 필요)
# LDFLAGS: 링크 시 필요한 옵션 (csapp.c 경로 포함, -lpthread 등)

# all 타겟: 기본 빌드 대상, echoserver 실행 파일을 만든다

# echoserver 타겟:
#   - echoserver.c와 ../csapp.c를 함께 컴파일하여 실행 파일 생성
#   - $(CC) $(CFLAGS) 옵션으로 소스 파일들을 컴파일하고 링크한다

# clean 타겟: 빌드 결과물(실행 파일, 오브젝트 파일)을 제거한다
