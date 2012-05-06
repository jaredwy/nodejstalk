
#include <node.h>
#include <v8.h>

v8::Handle<v8::Value> Func(const v8::Arguments& args)
{
	v8::HandleScope scope;
    if (args.Length() < 2) {
        return ThrowException(v8::Exception::TypeError(v8::String::New("Must provide a callback")));
    }

    v8::Local<v8::Function> callback = v8::Local<v8::Function>::Cast(args[1]);


    v8::Local<v8::String> toSay = args[0]->ToString();
    const unsigned argc = 2;
    v8::Local<v8::Value> argv[argc] = {   
            v8::Local<v8::Value>::New(v8::Null()),
            toSay
    };

    callback->Call(v8::Context::GetCurrent()->Global(), argc, argv);

    return v8::Undefined();
}

extern "C" {
    void init(v8::Handle<v8::Object> target)
    {
        NODE_SET_METHOD(target, "helloWorld", Func);
    }
}

NODE_MODULE(demo, init)