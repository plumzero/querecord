
#pragma once

#include <iostream>
#include <sstream>

#include <string.h>

#define LEN  256

struct ProtoStruct {
    ProtoStruct() { memset(val_, 0, LEN); }
    ProtoStruct(int8_t tag, int32_t len, const unsigned char *val) : tag_(tag), len_(len)
    { 
        memset(val_, 0, LEN);
        memcpy(val_, val, strlen((const char*)val));
    } 
    ~ProtoStruct(){}

    void Print() {
        std::cout << "ProtoStruct::Print: " << std::to_string(tag_) << "," << len_ << "," << val_ << std::endl;
    }

    std::string ToString() {
        std::cout << "ProtoStruct::ToString" << std::endl;

        std::ostringstream oss;
        oss << tag_;
        oss << len_;
        oss << val_;

        return oss.str();
    }

    void ParseFromString(const std::string& msg) {
        std::cout << "ProtoStruct::ParseFromString: msg.size = " << msg.size() << std::endl;
        std::istringstream iss(msg);

        iss >> tag_;
        iss >> len_;
        iss.get((char*)val_, LEN);
    }

    int8_t tag_;
    int32_t len_;
    unsigned char val_[LEN];
};

struct RosStruct {
    RosStruct() { memset(val_, 0, LEN); }
    ~RosStruct() {}

    void Print() {
        std::cout << "RosStruct::Print: " << std::to_string(tag_) << "," << len_ << "," << val_ << std::endl;
    }

    int8_t tag_;
    int32_t len_;
    unsigned char val_[LEN];
};

void FromProtoToRos(const ProtoStruct& proto, RosStruct& ros)
{
    std::cout << "FromProtoToRos" << std::endl;

    ros.tag_ = proto.tag_;
    ros.len_ = proto.len_;
    memcpy(ros.val_, proto.val_, strlen((const char*)proto.val_));

    ros.Print();
}