#include "client.h"

#include <funapi.h>
#include <funapi/test/network.h>
#include <gflags/gflags.h>
#include <glog/logging.h>


DEFINE_string(server_ip, "127.0.0.1", "");
DEFINE_uint64(server_port, 8012, "");


namespace engine_example_kakao_game_authentication {

namespace {

void InitializeKakaoGameSdk(const Ptr<funtest::Session> &session) {
  // 카카오 게임 SDK 를 연동하지 않았으므로 여기서는
  // 카카오 게임 인증에 필요한 데이터들을 임의로 만든다.

  const string access_token = RandomGenerator::GenerateAlphanumeric(10, 20);
  const string user_id = RandomGenerator::GenerateAlphanumeric(10, 20);

  // 발급받은 access_token, user_id 를 세션 컨텍스트에 저장한다.
  Json &ctxt = session->GetContext();
  ctxt["access_token"] = access_token;
  ctxt["user_id"] = user_id;
}


void OnSessionOpened(const Ptr<funtest::Session> &session) {
  // 연결되었다. 서버로 로그인 메시지를 보낸다.

  // 서버에서 카카오 게임 토큰 인증을 하므로 관련 데이터도 같이 보낸다.
  const Json &ctxt = session->GetContext();
  LOG_ASSERT(ctxt.HasAttribute("access_token", Json::kString));
  LOG_ASSERT(ctxt.HasAttribute("user_id", Json::kString));

  Json message;
  message["access_token"] = ctxt["access_token"].GetString();
  message["user_id"] = ctxt["user_id"].GetString();
  session->SendMessage("cs_login", message, kTcp);
}


void OnSessionClosed(const Ptr<funtest::Session> &session,
                     SessionCloseReason reason) {
}


void OnTcpTransportAttached(const Ptr<funtest::Session> &session, bool success) {
  if (success == false) {
    LOG(ERROR) << "Failed to connect to the server.";
    return;
  }
}


void OnTcpTransportDetached(const Ptr<funtest::Session> &session) {
}


// 서버가 cs_login 에 대한 응답 메시지인 sc_login 를 보내면 호출된다.
void OnLogin(const Ptr<funtest::Session> &session, const Json &message) {
  LOG_ASSERT(message.HasAttribute("result", Json::kBoolean));

  // result 값에 따라 적당히 성공/실패 로그를 출력한다.
  const bool result = message["result"].GetBool();
  if (result == true) {
    LOG(INFO) << "Succeeded to authenticate Kakao Game Token.";
  } else {
    LOG(ERROR) << "Failed to authenticate Kakao Game Token.";
  }
}

}  // unnamed namespace


void InstallClient() {
  funtest::Network::Install(OnSessionOpened, OnSessionClosed, 4);
  funtest::Network::RegisterTcpTransportHandler(
      OnTcpTransportAttached, OnTcpTransportDetached);

  // 서버에서 보내는 메시지를 받을 핸들러를 등록한다.
  funtest::Network::Register("sc_login", OnLogin);
}


void StartClient() {
  // 세션을 만들고 TCP 연결을 맺는다.
  const Ptr<funtest::Session> session = funtest::Session::Create();
  LOG_ASSERT(session != NULL);

  // 가상의 카카오 게임 SDk 초기화를 진행한다.
  InitializeKakaoGameSdk(session);

  // 서버로 연결한다. 연결이 되면 OnSessionOpened() 함수가 불린다.
  session->ConnectTcp(FLAGS_server_ip, FLAGS_server_port, kJsonEncoding);
}

}  // namespace engine_example_kakao_game_authentication
