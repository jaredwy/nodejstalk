#include <node.h>
#include <v8.h>

#include <string>

struct Baton {
    uv_work_t request;
    v8::Persistent<v8::Function> callback;
    std::string toSay;
};


void Work(uv_work_t* req) {
    Baton* baton = static_cast<Baton*>(req->data);
    long i = 0;
    while(i< 1000000000) {
        i++;
    }
}

void After(uv_work_t* req) {
    v8::HandleScope scope;
    Baton* baton = static_cast<Baton*>(req->data);
    const unsigned argc = 2;
    v8::Local<v8::Value> argv[argc] = {
        v8::Local<v8::Value>::New(v8::Null()),
        v8::Local<v8::Value>::New(v8::String::New(baton->toSay.c_str()))
    };
    v8::TryCatch try_catch;
        baton->callback->Call(v8::Context::GetCurrent()->Global(), argc, argv);
        if (try_catch.HasCaught()) {
            node::FatalException(try_catch);
        }
    baton->callback.Dispose();
    delete baton;
}

v8::Handle<v8::Value> Func(const v8::Arguments& args)
{
	v8::HandleScope scope;
    if (args.Length() < 2) {
        return ThrowException(v8::Exception::TypeError(v8::String::New("Must provide a callback")));
    }

    v8::Local<v8::Function> callback = v8::Local<v8::Function>::Cast(args[1]);
    std::string toSayNonV8 = std::string(*v8::String::Utf8Value(args[0]));

    Baton* baton = new Baton();
    baton->request.data = baton;
    baton->toSay = toSayNonV8;
    baton->callback = v8::Persistent<v8::Function>::New(callback);

    int status = uv_queue_work(uv_default_loop(), &baton->request, Work, After);
    assert(status == 0);
    return v8::Undefined();
}

extern "C" {
    void init(v8::Handle<v8::Object> target)
    {
        NODE_SET_METHOD(target, "helloWorld", Func);
    }
}

NODE_MODULE(demo, init)