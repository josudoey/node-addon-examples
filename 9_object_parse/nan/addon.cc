#include <nan.h>
#include <stdio.h>

//ref http://izs.me/v8-docs/classv8_1_1Handle.html
//ref http://izs.me/v8-docs/classv8_1_1Value.html

void ValDump(v8::Handle<v8::Value> v){
    int i,len;
    if(v->IsBoolean()||v->IsNumber()){
        fprintf(stderr,"%s",*v8::String::Utf8Value(v));
        return;
    }
    if(v->IsString()){
        fprintf(stderr,"\"%s\"",*v8::String::Utf8Value(v));
        return;
    }
    if(v->IsArray()){
        v8::Handle<v8::Array> arr = v.As<v8::Array>();
        len=arr->Length();
        fprintf(stderr,"[");
        for(i=0;i<len;i++){
            v8::Handle<v8::Value> item = arr->Get(i);
            ValDump(item);
            if(i<len-1){
                fprintf(stderr,",");
            }
        }
        fprintf(stderr,"]");
        return;
    }
    if(v->IsFunction()){
        v8::Handle<v8::Function> func=v.As<v8::Function>();
        fprintf(stderr,"%s",*v8::String::Utf8Value(func));
        return;
    }
    if(v->IsDate()){
        v8::Handle<v8::Date> date=v.As<v8::Date>();
        fprintf(stderr,"%s",*v8::String::Utf8Value(date));
        return;
    }
    if(v->IsObject()){
        v8::Handle<v8::Object> obj = v.As<v8::Object>();
        v8::Handle<v8::Array> keys = obj->GetOwnPropertyNames();
        len = keys->Length();
        fprintf(stderr,"{");
        for(i=0;i<len;i++){
            v8::Handle<v8::String>key = keys->Get(i)->ToString();
            fprintf(stderr,"\"%s\":",*v8::String::Utf8Value(key));
            ValDump(obj->GetRealNamedProperty(key));
            if(i<len-1){
                fprintf(stderr,",");
            }
        }
        fprintf(stderr,"}");
        return;
    }
    fprintf(stderr,"%s",*v8::String::Utf8Value(v));
}

void RunObjectParse(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    ValDump(info[0]);
}

void Init(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
  Nan::SetMethod(module, "exports", RunObjectParse);
}

NODE_MODULE(addon, Init)
