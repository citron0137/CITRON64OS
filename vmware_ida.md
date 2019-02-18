# Intro

## 쌩 부팅과정 VMware와 IDA로 리버싱 하기 입니다.
~~(간지나는)~~ 다른 말로, MBR 레벨에서 커널 디버깅 하기

### 현 실습은 IDA와 VMware가 설치된 Window 환경에서 진행하는 것을 기준으로 작성되었습니다.

### 이해를 하지 못하거나 진행이 막힌 경우에는 누구든 부담없이 연락부탁드립니다.
https://www.facebook.com/profile.php?id=100004945183754

### (뉴비 대 환영!!!)
~~(정작 본인이 늅늅)~~

# 0. 환경설정

citron64OS hcamp.ver을 다운로드 합니다.

https://github.com/citron0137/CITRON64OS/tree/hcamp19
 
새로운 가상 머신을 만들어서 
```
CITRON64OS-hcamp19 > CITRON64 > Disk.img
```
위 디렉터리의 Disk.img를 **플로피 디스크로** 추가합니다.

실행을 하면 정상적으로 부팅이 되는것을 확인할 수 있습니다.

가상머신 속에서 키보드로 입력이 가능합니다.
~~ㄷㄷㄷㄷㄷㄷ~~

# 1. VMware 디버깅 옵션

위 과정에서 만든 VMware가 저장된 위치로 가서 *.vmx파일을 텍스트 편집기로 수정합니다.

그리고 가장 아랫줄에
```
debugStub.listen.guest32 = "TRUE"
debugStub.listen.guest64 = "TRUE"
debugStub.hideBreakpoints = "TRUE"
monitor.debugOnStartGuest32 = "TRUE"
```
을 추가해줍니다.

이제 가상머신을 다시 실행하면 가상머신이 검정화면에서 멈춰있습니다.

이제 localhost의 8832포트가 디버깅 포트로 열려있습니다.

# 2. IDA로 디버깅 하기

IDA 32bit를 켜고 GO버튼으로 바로 workspace로 들어옵니다.

workspace의 메뉴바에서 
```
Debugger > Attach > Remote gdb debugger
``` 
를 선택합니다.
```
Workspace에서 메뉴를 펼친 사진
```
Host name과 port에 각각
127.0.0.1과 8832를 입력합니다.

```
hostname과 port를 입력한 사진
```
그럼 다음과 같은 화면이 나타납니다.
```
세팅된 화면
```

이제 breakpoint 탭에서 우클릭 > insert bp 또는 insert 버튼을 눌러서 break point를 추가해줍니다.
(소스코드를 분석해서 적당한 위치를 찾아줘야 합니다.)
```
0x7c00

0x10200

0x200000
```
위에서 부터 순서대로 bootloader, 32bit kernel, 64bit kernel의 시작 주소입니다.

```
breakpoint 추가하는 사진
```

이제 f9 버튼을 눌러서 진행합니다.
```
bootloader에서 bp 걸린 사진
```
bootloader에서는 소스코드가 제대로 보이지 않습니다. (16bit 어셈블리이기 때문)

진행을 하다 보면 0x10200에서 코드를 볼 수 있습니다.

혹시 코드가 보이지 않는다면 
```
분석할 부분을 드래그 해서 선택
우클릭 > analysis code > yes
```
으로 강제로 어셈블리 코드로 분석할 수 있습니다.

0x200000 주소로 continue(f9)를 하면 브레이킹 포인트가 걸리지 않지만 가상머신이 멈춥니다.

64bit모드로 전환을 했기 때문입니다.

이 때는 IDA 64bit를 켜서 127.0.0.1, 8864로 attach 합니다.
```
attach 하는 사진
```
이제 64bit 영역을 분석하면 됩니다.
