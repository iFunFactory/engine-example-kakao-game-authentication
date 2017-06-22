#include "server.h"

#include <funapi.h>
#include <gflags/gflags.h>
#include <glog/logging.h>

#include <sstream>


// 실제 카카오 게임 센터에 입점하여 발급받은 것이 있다면
// MANIFEST.server.json 의 Arguments 에서 동일한 이름의 항목값을 수정한다.
//
// 카카오 게임 센터에 입점하지 않았으므로 여기서는 임의의 값으로 설정한다.
DEFINE_string(kakao_game_client_id, "12345", "");
DEFINE_string(kakao_game_sdkver, "12345", "");


namespace engine_example_kakao_game_authentication {

namespace {

const string kURL("https://api.kakao.com/v1/token/check.json?");


string MakeURL(const string &access_token, const string &user_id) {
  std::stringstream ss;
  ss << "access_token=" << access_token
     << "&user_id=" << user_id
     << "&client_id=" << FLAGS_kakao_game_client_id
     << "&sdkver=" << FLAGS_kakao_game_sdkver;

  string encoded;
  http::Escape(ss.str(), &encoded);

  const string url = kURL + encoded;
  return url;
}


void OnKakaoGameAuthenticated(const CURLcode rc,
                              const http::Response &http_response,
                              const Ptr<Session> &session) {
  // 통신에 문제가 생겼다. 적당한 로그와 함께 응답 메시지를 보낸다.
  if (rc != CURLE_OK) {
    const char *curl_error_str = curl_easy_strerror(rc);
    LOG(ERROR) << "Failed to http request. "
               << "error_code=" << rc
               << ", error_desc=" << curl_error_str;
    Json message;
    message["result"] = false;
    session->SendMessage("sc_login", message);
    return;
  }

  // 카카오 게임 API 서버가 응답으로 HTTP OK 를 보내지 않았다.
  // 적당한 로그와 함께 응답 메시지를 보낸다.
  if (http_response.status_code != http::kOk) {
    LOG(ERROR) << "Failed to authenticate Kakao Game Token. "
               << "http_status_code=" << http_response.status_code
               << ", response_body=" << http_response.body;
    Json message;
    message["result"] = false;
    session->SendMessage("sc_login", message);
    return;
  }

  // 다음 두 가지를 만족할 경우 성공이다.
  //   1) HTTP status code: 200
  //   2) { "status": 0, ... }
  // 그 외는 여기서는 다루지 않으며, 상세한 내용은 카카오 게임 센터에서
  // API 스펙을 확인한다.

  // JSON 파싱 실패 또는 JSON Object 가 아닌 경우.
  // 카카오 게임 API 스펙이 변경되었는지 확인한다.
  Json kakao_response;
  if (kakao_response.FromString(http_response.body) == false ||
      kakao_response.IsObject() == false) {
    LOG(ERROR) << "Unknown Kakao Game protocol. "
               << "kakao_response=" << kakao_response.ToString();
    Json message;
    message["result"] = false;
    session->SendMessage("sc_login", message);
    return;
  }

  // JSON Object 에 status attribute 가 없거나 Integer 타입이 아닌 경우.
  // 카카오 게임 API 스펙이 변경되었는지 확인한다.
  if (kakao_response.HasAttribute("status", Json::kInteger) == false) {
    LOG(ERROR) << "Unknown Kakao Game protocol. "
               << "Wrong 'status' attribute. "
               << "kakao_response=" << kakao_response.ToString();
    Json message;
    message["result"] = false;
    session->SendMessage("sc_login", message);
    return;
  }

  // status 값을 확인하여 처리 결과를 sc_login 메시지로 보낸다.
  const int64_t status = kakao_response["status"].GetInteger();
  if (status != 0) {
    LOG(ERROR) << "Failed to authenticate Kakao Game Token. "
               << "status=" << status;
  }

  Json message;
  message["result"] = (status == 0);
  session->SendMessage("sc_login", message);
}


// 서버가 cs_login 보내면 호출된다.
void OnCSLogin(const Ptr<Session> &session, const Json &message) {
  LOG_ASSERT(message.HasAttribute("access_token", Json::kString));
  LOG_ASSERT(message.HasAttribute("user_id", Json::kString));

  // 클라이언트가 보낸 데이터를 꺼내온다.
  const string access_token = message["access_token"].GetString();
  const string user_id = message["user_id"].GetString();

  // 카카오 게임 API 서버와 통신하기 위한 URL 을 만든다.
  const string url = MakeURL(access_token, user_id);

  // 카카오 게임 API 서버와 통신하기 위해 HttpClient 를 만든다.
  const Ptr<HttpClient> http_client = boost::make_shared<HttpClient>();
  LOG_ASSERT(http_client);

  // GET method 로 비동기 통신을 한다. 카카오 게임 API 서버로부터 응답이 오면
  // 클라이언트에게 응답 메시지를 보내기 위해 session 을 핸들러에 넘겨준다.
  http_client->GetAsync(
      url, boost::bind(OnKakaoGameAuthenticated, _1, _2, session), 0);
}

}  // unnamed namespace


void InstallServer() {
  HandlerRegistry::Register("cs_login", OnCSLogin);
}

}  // namespace engine_example_kakao_game_authentication
