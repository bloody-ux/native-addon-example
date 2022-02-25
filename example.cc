#include <node.h>

const int maxValue = 10;
int numberOfCalls = 0;

void WhoAmI(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  auto message = v8::String::NewFromUtf8(isolate, "I'm a Node Hero!").ToLocalChecked();
  args.GetReturnValue().Set(message);
}

void Increment(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();

  if (!args[0]->IsNumber()) {
    isolate->ThrowException(v8::Exception::TypeError(
          v8::String::NewFromUtf8(isolate, "Argument must be a number").ToLocalChecked()));
    return;
  }

  int argsValue = args[0]->ToInteger(isolate->GetCurrentContext()).ToLocalChecked()->Value();
  if (numberOfCalls + argsValue > maxValue) {
    isolate->ThrowException(v8::Exception::Error(
          v8::String::NewFromUtf8(isolate, "Counter went through the roof!").ToLocalChecked()));
    return;
  }

  numberOfCalls += argsValue;
  args.GetReturnValue().Set(numberOfCalls);
}


void Initialize(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "whoami", WhoAmI);
  NODE_SET_METHOD(exports, "increment", Increment);
}

NODE_MODULE(module_name, Initialize)
