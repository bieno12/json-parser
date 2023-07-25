#include <myjson/Value.hpp>
#include <sstream>
#include <iostream>

myjson::Value::Value()
{
	m_value = std::monostate();
}

myjson::Value::Value(const char *str)
{
	m_value = std::string(str);
}
myjson::Value::Value(std::string str)
{
	m_value = str;
}
myjson::Value::Value(double number)
{
	m_value = number;
}
myjson::Value::Value(std::map<std::string, myjson::Value> object)
{
	m_value = object;
}
myjson::Value::Value(std::vector<Value> array)
{
	m_value = array;
}

myjson::Value::Value(bool boolean)
{
	m_value = boolean;
}

myjson::Value &myjson::Value::operator=(const myjson::Value &other)
{
	m_value = other.m_value;
	return *this;
}
myjson::Value &myjson::Value::operator=(myjson::Value &&other)
{
	m_value = other.m_value;
	return *this;
}
myjson::Value::Value(const Value &other)
{
	m_value = other.m_value;
}
myjson::Value::Value(Value &&other)
{
	m_value = other.m_value;
}
myjson::Value::~Value()
{
}

myjson::Value::Type myjson::Value::type()
{
	return (myjson::Value::Type)m_value.index();
}
std::string &myjson::Value::get_string()
{
	return std::get<Type::String>(m_value);
}
double &myjson::Value::get_number()
{
	return std::get<Type::Number>(m_value);
}
std::map<std::string, myjson::Value> &myjson::Value::get_object()
{
	return std::get<Type::Object>(m_value);
}

std::vector<myjson::Value> &myjson::Value::get_array()
{
	return std::get<Type::Array>(m_value);
}

bool &myjson::Value::get_bool()
{
	return std::get<Type::Boolean>(m_value);
}

bool myjson::Value::is_null()
{
	return std::holds_alternative<std::monostate>(m_value);
}

myjson::Value &myjson::Value::operator=(const std::string &value)
{
	m_value = value;
	return *this;
}
myjson::Value &myjson::Value::operator=(double value)
{
	m_value = value;
	return *this;
}
myjson::Value &myjson::Value::operator=(const std::map<std::string, myjson::Value> &value)
{
	m_value = value;
	return *this;
}
myjson::Value &myjson::Value::operator=(const std::vector<Value> value)
{
	m_value = value;
	return *this;
}
myjson::Value &myjson::Value::operator=(bool value)
{
	m_value = value;
	return *this;
}
std::string myjson::Value::to_string()
{
	std::stringstream ss;
	switch (m_value.index())
	{
	case myjson::Value::Type::String:
	{
		ss << "\"" << get_string() << "\"" ;
		break;
	case myjson::Value::Type::Number:
		ss << get_number();
	}
	break;
	case myjson::Value::Type::Object:
	{
		ss << "{";
		size_t i = 0;
		auto &obj = get_object();
		for (auto pr : obj)
		{
			ss << "\"" << pr.first << "\":";
			ss << pr.second.to_string();
			if (i++ < obj.size() - 1)
				ss << ",";
		}
		ss << "}";
	}
	break;
	case myjson::Value::Type::Array:
	{
		ss << "[";

		auto &array = get_array();
		for (int i = 0; i < (int)array.size() - 1; i++)
		{
			ss << array[i].to_string() << ',';
		}
		if (array.size() >= 1)
			ss << array.back().to_string() ;
		ss << ']';
	}
	break;
	case myjson::Value::Type::Boolean:
	{
		if (get_bool())
			ss << "true";
		else
			ss << "false";
	}
	break;
	case myjson::Value::Type::Null:
	{
		ss << "null";
	}
	break;
	}
	return ss.str();
}