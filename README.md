# iFunEngine Example - Kakao Game Authentication

본 프로젝트에서는 카카오 게임에 로그인한 클라이언트의 access token 의 유효성 검사를
[아이펀 엔진](https://www.ifunfactory.com/engine/) 으로 만든 서버에서 어떻게
구현할 수 있는지 구현된 샘플 코드를 통해 안내해 드리고 있습니다.

본 샘플로 테스트하기 위한 환경은 다음과 같습니다.

* Ubuntu 14.04 혹은 16.04, CentOS 6 혹은 7

**이어지는 내용에서는 Ubuntu 14.04 에서 진행하였습니다.**

## 목차

* [다운로드](#다운로드)
* [환경 설정](#환경-설정)
* [빌드 환경 구축](#빌드-환경-구축)
* [빌드하기](#빌드하기)
* [실행하기](#실행하기)
* [올바른 값으로 토큰 인증하기](#올바른-값으로-토큰-인증하기)
* [구현된 코드 확인하기](#구현된-코드-확인하기)

## 다운로드

아래와 같이 git clone 또는 zip 파일을 다운받습니다.

**Clone**
```bash
  git clone https://github.com/iFunFactory/engine-example-kakao-game-authentication.git
```

또는

**Download**

```
https://github.com/iFunFactory/engine-example-kakao-game-authentication/archive/master.zip
```

## 환경 설정

engine-example-kakao-game-authentication 을 구동하기 위해 엔진 외 추가로 설치할 것은 없습니다.
엔진 설치 및 개발 환경 설정은 [아이펀 엔진 레퍼런스](https://www.ifunfactory.com/engine/documents/reference/ko/development-environment.html)을 참고해 주세요.


## 빌드 환경 구축

[다운로드](#다운로드) 의 설명과 같이 진행하였다면 다음과 같이 명렁을 입력하여 빌드 디렉토리를 만듭니다.

```bash
$ cd engine-example-kakao-game-authentication/
$ engine_example_kakao_game_authentication-source/setup_build_environment --type=makefile
```

빌드 디렉토리 생성이 완료되면 프로젝트 루트 디렉터리에 `engine_example_kakao_game_authentication-build` 디렉토리가 생성됩니다.
이 build 디렉토리를 보면 `debug`와 `release` 디렉터리가 생성되는데, 각각의 디렉터리에서 debug버전 빌드와
release버전의 빌드를 할 수 있습니다. 이후 설명은 debug 디렉토리를 기준으로 진행합니다만,
release 와 진행 방법이 다르지 않습니다.

## 빌드하기

다음과 같이 명령을 입력하여 빌드합니다.

```bash
$ cd engine_example_kakao_game_authentication-build/debug
$ make

Scanning dependencies of target internal_create_launchers
[  3%] Generating engine_example_kakao_game_authentication.client-launcher
[  6%] Generating engine_example_kakao_game_authentication.client-local
[  9%] Generating engine_example_kakao_game_authentication.server-launcher
[ 12%] Generating engine_example_kakao_game_authentication.server-local
[ 12%] Built target internal_create_launchers
Scanning dependencies of target internal_import_manifest_dirs
[ 15%] Generating manifests/client/MANIFEST.json
[ 18%] Generating manifests/server/MANIFEST.json
[ 18%] Built target internal_import_manifest_dirs
Scanning dependencies of target internal_import_resource_dirs
[ 21%] Generating resources/game_data
[ 25%] Generating resources/client_data
[ 28%] Generating resources/json_protocols
[ 28%] Built target internal_import_resource_dirs
[ 31%] Generating funapi/network/fun_message.pb.cc, funapi/network/fun_message.pb.h, funapi/network/fun_message_pb2.py
[ 34%] Generating funapi/distribution/fun_rpc_message.pb.cc, funapi/distribution/fun_rpc_message.pb.h, funapi/distribution/fun_rpc_message_pb2.py
[ 37%] Generating funapi/service/multicast_message.pb.cc, funapi/service/multicast_message.pb.h, funapi/service/multicast_message_pb2.py
[ 40%] Generating funapi/service/redirect_message.pb.cc, funapi/service/redirect_message.pb.h, funapi/service/redirect_message_pb2.py
[ 43%] Generating funapi/management/maintenance_message.pb.cc, funapi/management/maintenance_message.pb.h, funapi/management/maintenance_message_pb2.py
[ 46%] Generating funapi/network/ping_message.pb.cc, funapi/network/ping_message.pb.h, funapi/network/ping_message_pb2.py
[ 50%] Generating engine_example_kakao_game_authentication_rpc_messages.pb.cc, engine_example_kakao_game_authentication_rpc_messages.pb.h, engine_example_kakao_game_authentication_rpc_messages_pb2.py
[ 53%] Generating /tmp/engine-example-kakao-game-authentication/engine_example_kakao_game_authentication-source/src/engine_example_kakao_game_authentication_object.h, /tmp/engine-example-kakao-game-authentication/engine_example_kakao_game_authentication-source/src/object_model/engine_example_kakao_game_authentication_object.cc, /tmp/engine-example-kakao-game-authentication/engine_example_kakao_game_authentication-source/src/engine_example_kakao_game_authentication_object.py
/usr/lib/python2.7/dist-packages/funapi/json/__init__.pyc
[ 56%] Generating engine_example_kakao_game_authentication_loggers.h, engine_example_kakao_game_authentication_loggers.cc
[ 59%] Generating engine_example_kakao_game_authentication_messages.pb.cc, engine_example_kakao_game_authentication_messages.pb.h, engine_example_kakao_game_authentication_messages_pb2.py
Scanning dependencies of target engine_example_kakao_game_authentication
[ 62%] Building CXX object src/CMakeFiles/engine_example_kakao_game_authentication.dir/object_model/engine_example_kakao_game_authentication_object.cc.o
[ 65%] Building CXX object src/CMakeFiles/engine_example_kakao_game_authentication.dir/engine_example_kakao_game_authentication_loggers.cc.o
[ 68%] Building CXX object src/CMakeFiles/engine_example_kakao_game_authentication.dir/funapi/distribution/fun_rpc_message.pb.cc.o
[ 71%] Building CXX object src/CMakeFiles/engine_example_kakao_game_authentication.dir/funapi/service/multicast_message.pb.cc.o
[ 75%] Building CXX object src/CMakeFiles/engine_example_kakao_game_authentication.dir/funapi/service/redirect_message.pb.cc.o
[ 78%] Building CXX object src/CMakeFiles/engine_example_kakao_game_authentication.dir/funapi/management/maintenance_message.pb.cc.o
[ 81%] Building CXX object src/CMakeFiles/engine_example_kakao_game_authentication.dir/funapi/network/ping_message.pb.cc.o
[ 84%] Building CXX object src/CMakeFiles/engine_example_kakao_game_authentication.dir/funapi/network/fun_message.pb.cc.o
[ 87%] Building CXX object src/CMakeFiles/engine_example_kakao_game_authentication.dir/client.cc.o
[ 90%] Building CXX object src/CMakeFiles/engine_example_kakao_game_authentication.dir/server.cc.o
[ 93%] Building CXX object src/CMakeFiles/engine_example_kakao_game_authentication.dir/engine_example_kakao_game_authentication_server.cc.o
[ 96%] Building CXX object src/CMakeFiles/engine_example_kakao_game_authentication.dir/engine_example_kakao_game_authentication_messages.pb.cc.o
[100%] Building CXX object src/CMakeFiles/engine_example_kakao_game_authentication.dir/engine_example_kakao_game_authentication_rpc_messages.pb.cc.o
Linking CXX shared module libengine_example_kakao_game_authentication.so
[100%] Built target engine_example_kakao_game_authentication
```

빌드가 완료되면 해당 디렉토리에 서버 실행을 위한 스크립트와 클라이언트 실행을
위한 스크립트가 생성됩니다.

* `engine_example_kakao_game_authentication.server-local`: 클라이언트의 로그인 요청을 처리하는 서버입니다.
  로그인 요청 메시지를 받으면 카카오 게임 토큰 인증을 처리합니다.
* `engine_example_kakao_game_authentication.client-local`: 서버로 로그인 요청 메시지를 보내는 클라이언트입니다.
  카카오 게임 토큰 인증을 위해 클라이언트는 몇 가지 정보를 메시지와 함께 보냅니다.

## 실행하기

빌드하기 위해 이동했던 디렉토리에서 다음과 같이 스크립트를 실행합니다.
서버와 클라이언트 모두 실행하기 위해 터미널을 하나 더 열어서 동일한 디렉토리로
이동하는 것이 좋습니다.

```bash
# 서버 실행을 위한 터미널1
# 실행이 완료되었다면 다음과 같이 로그가 출력될 것입니다.

$ cd engine_example_kakao_game_authentication-build/debug
$ ./engine_example_kakao_game_authentication.server-local

...
I0623 10:48:12.535740 24649 manifest_handler.cc:744] Starting Object
I0623 10:48:12.535747 24649 manifest_handler.cc:744] Starting EventDispatcher
I0623 10:48:12.535759 24649 manifest_handler.cc:744] Starting SessionService
I0623 10:48:12.535825 24649 session_service.cc:1565] tcp json server start: port(8012)
I0623 10:48:12.535851 24649 manifest_handler.cc:744] Starting EngineExampleKakaoGameAuthenticationServer
```

클라이언트를 실행합니다.

```bash
# 클라이언트 실행을 위한 터미널2
# 실행이 완료되었다면 다음과 같이 로그가 출력될 것입니다.

$ cd engine_example_kakao_game_authentication-build/debug
$ ./engine_example_kakao_game_authentication.client-local

...
I0623 10:55:08.890281 24718 manifest_handler.cc:744] Starting ObjectDirectoryService
I0623 10:55:08.890291 24718 manifest_handler.cc:744] Starting Object
I0623 10:55:08.890298 24718 manifest_handler.cc:744] Starting EventDispatcher
I0623 10:55:08.890310 24718 manifest_handler.cc:744] Starting EngineExampleKakaoGameAuthenticationServer
E0623 10:55:08.929054 24733 client.cc:72] Failed to authenticate Kakao Game Token.
```

클라이언트를 실행하면 서버와는 다르게 에러 로그가 출력됩니다.
이때 서버에는 다음과 같은 로그가 출력되어 있을 것입니다.

```
I0623 10:55:08.892338 24670 session_service.cc:1846] session created: sid=0728d8b4-8ece-499b-9df4-341cf253eb17, protocol=TCP, address=127.0.0.1:38594
E0623 10:55:08.928113 24671 server.cc:58] Failed to authenticate Kakao Game Token. http_status_code=401, response_body=invalid_token :: User token is required
```

위 로그에서는 실패한 것으로 나오는데 본 샘플에서는 카카오 게임 토큰 인증 처리를
위해 관련 값을 임의로 설정하였기 때문입니다.

발생된 상황을 정리하면 다음과 같습니다.

1. 클라이언트가 서버와 연결된 이후 로그인 요청 메시지를 보냅니다.
  메시지에는 카카오 게임 토큰 인증을 위한 데이터도 포함되어 있습니다.
2. 로그인 요청 메시지를 받은 서버는 클라이언트가 보낸 토큰 인증 관련 데이터로
  카카오 게임 API 서버로 인증 요청을 보냅니다.
3. 카카오 게임 API 서버로부터 응답이 오면 성공/실패를 확인합니다.
4. 서버는 클라이언트로 로그인 요청에 대한 응답을 보내면서 토큰 인증 처리 결과도
  같이 보냅니다.
5. 응답 메시지를 받은 클라이언트는 성공/실패에 대한 로그를 출력합니다.


## 올바른 값으로 토큰 인증하기

실제 카카오 게임 토큰으로 인증하기 위해서 설정이 필요한 항목은 다음과 같습니다.

* client_id, sdkver, user_id, access_token

client_id, sdkver 는 카카오 게임 센터에 입점하면서 발급받을 수 있을 것입니다.
user_id 와 access_token 은 클라이언트에 카카오 게임 SDK 를 연동한 뒤 이를 초기화
하는 단계에서 얻을 수 있을 것입니다.

클라이언트는 로그인 요청을 보내면서 user_id 와 access_token 을 서버로 보냅니다.
서버는 전달받은 user_id 와 access_token 와 함께 client_id 와 sdkver 를 가지고
카카오 게임 API 서버와 통신합니다.

따라서 서버는 실행하기 전에 올바른 client_id 와 sdkver 을 입력해야 합니다.
소스 디렉토리에 존재하는 MANIFEST.server.json 파일에서 수정할 수 있습니다.

```
...
"arguments": {
  "kakao_game_client_id": "12345",
  "kakao_game_sdkver": "12345"
},
...
```

서버뿐만 아니라 클라이언트에서도 user_id 와 access_token 을 임의의 값으로 사용합니다.
만약 서버와 마찬가지로 클라이언트도 발급받은 값으로 설정하려는 경우에는
소스 디렉토에 존재하는 MANIFEST.client.json 파일에서 수정할 수 있습니다.

```
"arguments": {
  "server_ip": "127.0.0.1",
  "server_port": 8012,  // TCP JSON port
  "kakao_game_access_token": "12345",
  "kakao_game_user_id": "12345"
},
```

MANIFEST 파일만 수정해도 재빌드없이 서버, 클라이언트를 실행하면 수정한 값이
적용되지만 서버, 클라이언트를 실행하면서 값을 수정할 수도 있습니다.

서버를 실행할 때 수정하고 싶은 항목을 입력하면 됩니다. 서버는 다음과 같이 입력합니다.

```bash
$ cd engine_example_kakao_game_authentication-build/debug
$ ./engine_example_kakao_game_authentication.server-local -kakao_game_client_id="6789" -kakao_game_sdkver="6789"
```

클라이언트는 다음과 같이 입력합니다.

```bash
$ cd engine_example_kakao_game_authentication-build/debug
$ ./engine_example_kakao_game_authentication.client-local -kakao_game_access_token="6789" -kakao_game_user_id="6789"
```

## 구현된 코드 확인하기

클라이언트는 소스 디렉토리에서 engine_example_kakao_game_authentication-source/src/client.cc
파일에 작성되어 있습니다. 클라이언트를 실행하면 InstallClient() 함수가 불린 후
StartClient() 함수가 불립니다. InstallClient() 함수는 서버와 비슷하게 메시지
핸들러를 등록합니다. OnSCLogin() 함수는 서버가 sc_login 메시지 타입으로 응답 메시지를
보내면 불립니다.

StartClient() 함수가 불리면 가상으로 카카오 게임 SDK 초기화를 진행하고 서버에 연결합니다.
연결되면 세션이 맺어지면서 OnSessionOpened() 함수가 불립니다. 이 함수를 시작으로
클라이언트가 인증을 위한 데이터와 함께 메시지를 보냅니다.

서버는 소스 디렉토리에서 engine_example_kakao_game_authentication-source/src/server.cc
파일에 작성되어 있습니다. InstallServer() 함수에서 cs_login 이라는 메시지 타입과
함께 OnCSLogin() 이라는 핸들러 함수를 등록합니다. 클라이언트가 서버와 연결되면
cs_login 이라는 메시지 타입으로 메시지를 보내는데 이때 OnCSLogin() 함수가 불립니다.
그리고 이 함수에서 카카오 게임 토큰 인증을 진행하고 카카오 게임 API 서버에서
응답이 오면 OnKakaoGameAuthenticated() 함수가 불립니다.
