#include <stdio.h>
#include <sstream>
#include <json/json.h>

template <typename itype, typename otype>
static void convert(itype input, otype& output) {
	printf("convert ing ...\n");
	std::stringstream ss;
	ss << input;
	ss >> std::noskipws >> output;
}

template <typename T>
static bool parse_value(Json::Value& value, T& data) {
	if (value.isInt()) {
		printf("parse_value ... int\n");
		convert(value.asInt(), data);
	} else if (value.isUInt()) {
		convert(value.asUInt(), data);
	// } else if (value.isInt64()) {			// 使用的 jsoncpp 中暂时没有对 Int64 和 UInt64 的解析
		// convert(value.asInt64(), data);
	// } else if (value.isUInt64()) {
		// convert(value.asUInt64(), data);
	} else if (value.isDouble()) {
		convert(value.asDouble(), data);
	} else if (value.isString()) {
		convert(value.asString(), data);
	} else if (value.isBool()) {
		convert(value.asBool(), data);
	} else {
		return false;
	}
	return true;
}

int main() {
	Json::Value val;
	int i = 1;
	val["i"] = 100;
	
	printf("val type is %d\n", val.type());
	
	if (val.isInt()) {
		printf("Yes its type is int\n");
	} else if (val.isString()) {
		printf("Yes its type is string\n");
	}
	
	if (parse_value(val, i) == false) {
		printf("parse error\n");
	} else {
		printf("i = %d\n", i);
	}
	
	return 0;
}