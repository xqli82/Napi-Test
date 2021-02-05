#include <node_api.h>
#include <iostream>

using namespace std;

napi_value SayHello(napi_env env,napi_callback_info info){
  cout << "hello world" << endl;
  return NULL;
}

napi_value Init(napi_env env, napi_value exports){
  napi_status status;
  napi_value method;

  status = napi_create_function(env,"exports",NAPI_AUTO_LENGTH,SayHello,NULL,&method);
  if(status!= napi_ok){
    return NULL;
  }

  status = napi_set_named_property(env,exports,"sayHello",method);
  if(status != napi_ok){
    return NULL;
  }

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME,Init)