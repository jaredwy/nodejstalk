
#include <node.h>


#include <v8.h>

v8::Handle<v8::Value> Func(const v8::Arguments& args)
{
	v8::HandleScope scope;
    if (args.Length() < 1) {
        return ThrowException(v8::Exception::TypeError(v8::String::New("Must provide an argument")));
    }
    v8::Local<v8::String> toSay = args[0]->ToString();
    return scope.Close(toSay);
}

extern "C" {
    void init(v8::Handle<v8::Object> target)
    {
        NODE_SET_METHOD(target, "helloWorld", Func);
    }
}

NODE_MODULE(demo, init)