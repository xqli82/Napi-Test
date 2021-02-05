# 模块导出
```
NAPI_MODULE(addon,init)
```
# 初始化函数
```
void init(napi_env env, napi_value exports,napi_vlue module, void* priv)
{
    //init function
}
```
其中:
+ napi_env 表示底层N-API的特定状态上下文;
+ napi_value exports相当于exports 对象;
+ napi_value module 是module对象;
# N-API函数声明样式
```
napi_value 函数名(napi_env env , napi_callback_info info){

}
```
示例:
```
napi_value echo(napi_env env,napi_callback_info info){
    napi_statue status;
    size_t argc=1;
    napi_value argv[1];
    status =napi_get_cb_info(env,info,&argc,argv,0,0);
    if(status!= napi_ok || argc <1){
        napi_throw_type_error(env,"EBADARGS:,"wrong number of arguments");
        return 0;
    }
    return argv[0];
}
```
# N-API数据类型
+ napi_status
+ napi_extended_error_info
+ napi_env
+ napi_value
## napi_staus
用于接收N-API各函数的状态结果---即调用是否成功,如:
```
napi_status status = napi_define_properties(env,exports,1,&desc);
//表示给exports对象上挂上desc中所描述的属性,若成功返回napi_ok
```
napi_status是一个枚举变量:
```
typedef enum{
    napi_ok,
    napi_invalid_arg,
    napi_object_expected,
    napi_string_expected,
    napi_name_expected,
    napi_function_expected,
    napi_number_exprect,
    napi_boolen_exprect,
    napi_array_exprect,
    napi_generic_exprect,
    napi_pending_exprect,
    napi_cancelled,
    napi_cancelled,
    napi_status_last,
} napi_status;
```
可以通过napi_get_last_error_info()函数来获得最后一次调用的失败详细信息;
## napi_extended_error_info
表示调用失败的详细信息,其实际是一个结构体,声明如下:
```
typedef struct{
    const char* error_message;
    void* engin_reserved;
    uint_32 engine_error_code;
    napi_status error_code;
} napi_extended_error_info
```
## napi_value
这是一个指针,声明如下:
```
typedef struct napi_value_ *napi_value;
```