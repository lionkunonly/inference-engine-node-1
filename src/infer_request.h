#ifndef IE_INFER_REQUEST_H
#define IE_INFER_REQUEST_H

#include <napi.h>

#include "inference_engine.hpp"

namespace ienodejs {

class InferRequest : public Napi::ObjectWrap<InferRequest> {
 public:
  static void Init(const Napi::Env& env);
  static Napi::Value NewInstance(const Napi::Env& env,
                                 const InferenceEngine::InferRequest& actual);
  static void NewInstanceAsync(
      Napi::Env& env,
      const InferenceEngine::ExecutableNetwork& exec_net,
      Napi::Promise::Deferred& deferred);
  InferRequest(const Napi::CallbackInfo& info);

 private:
  friend class CreateInferReqAsyncWorker;
  static Napi::FunctionReference constructor;

  // APIs
  Napi::Value GetBlob(const Napi::CallbackInfo& info);
  Napi::Value Infer(const Napi::CallbackInfo& info);
  Napi::Value StartAsync(const Napi::CallbackInfo& info);
  void SetCompletionCallback(const Napi::CallbackInfo& info);
  void NativeStartAsync(const Napi::CallbackInfo& info);

  InferenceEngine::InferRequest actual_;
  Napi::ThreadSafeFunction _threadSafeFunction;
};

}  // namespace ienodejs

#endif  // IE_INFER_REQUEST_H