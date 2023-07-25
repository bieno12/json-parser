#ifndef MYJSON_VALUE_HPP
#define MYJSON_VALUE_HPP
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <variant>
namespace myjson
{
	class Value
	{
	public:
		enum Type
		{
			Null,
			String,
			Number,
			Object,
			Array,
			Boolean
		};
	public:
		Value();
		Value(const char * str);
		Value(std::string str);
		Value(double number);
		Value(std::map<std::string, myjson::Value> object);
		Value(std::vector<Value> array);
		Value(bool );


		Value(const Value& other);
		Value& operator =(const Value& other);
		Value& operator =(Value&& other);
		Value(Value&& other);
		~Value();
	
		Value& operator =(const std::string&);
		Value& operator =(double);
		Value& operator =(const std::map<std::string, myjson::Value>& object);
		Value& operator =(const std::vector<Value> array);
		Value& operator =(bool boolean);
		Type type();
		std::string& get_string();
		double& get_number();
		std::map<std::string, Value>& get_object();
		std::vector<Value>& get_array();
		bool& get_bool();
		bool is_null();

		std::string to_string();
	private:
		//crude way to do it
		std::variant<std::monostate, std::string, double, std::map<std::string, Value>, std::vector<Value>, bool> m_value;
	};
} // namespace myjson

#endif