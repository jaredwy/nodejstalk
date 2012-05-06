
#include <node.h>
#include <v8.h>

v8::Handle<v8::Value> Func(const v8::Arguments& args)
{
    v8::HandleScope scope;
    v8::Local<v8::String> helloWorld = v8::String::New("hello, world");
    return scope.Close(helloWorld);
}

extern "C" {
    void init(v8::Handle<v8::Object> target)
    {
        NODE_SET_METHOD(target, "helloWorld", Func);
	}
}

NODE_MODULE(demo, init)