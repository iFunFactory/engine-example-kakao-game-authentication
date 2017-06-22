// PLEASE ADD YOUR EVENT HANDLER DECLARATIONS HERE.

#include <boost/bind.hpp>
#include <funapi.h>
#include <gflags/gflags.h>

#include "client.h"
#include "server.h"
#include "engine_example_kakao_game_authentication_object.h"

DECLARE_string(app_flavor);


namespace {

class EngineExampleKakaoGameAuthenticationServer : public Component {
 public:
  static bool Install(const ArgumentMap &arguments) {
    LOG(INFO) << "Built using Engine version: " << FUNAPI_BUILD_IDENTIFIER;

    if (FLAGS_app_flavor == "server") {
      engine_example_kakao_game_authentication::ObjectModelInit();
      engine_example_kakao_game_authentication::InstallServer();
    } else if (FLAGS_app_flavor == "client") {
      engine_example_kakao_game_authentication::InstallClient();
    }

    return true;
  }

  static bool Start() {
    if (FLAGS_app_flavor == "client") {
      engine_example_kakao_game_authentication::StartClient();
    }
    return true;
  }

  static bool Uninstall() {
    return true;
  }
};

}  // unnamed namespace


REGISTER_STARTABLE_COMPONENT(EngineExampleKakaoGameAuthenticationServer,
                             EngineExampleKakaoGameAuthenticationServer)
