#pragma once

enum VariantType
{
	Int,
	Float,
	Bool,
	String,
	Undefined
};

class Variant
{
public:
	Variant();

	Variant(int value);

	Variant(float value);

	Variant(bool value);

	Variant(std::string value);

	VariantType getType();

	int getIntValue();

	float getFloatValue();

	bool getBoolValue();

	std::string getStringValue();

private:
	VariantType _type;
	int _intValue;
	float _floatValue;
	bool _boolValue;
	std::string _strValue;
};

