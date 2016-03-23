#include "stdafx.h"
#include "Variant.h"

Variant::Variant()
{
	_type = Undefined;
}

Variant::Variant(int value) : _intValue(value)
{
	_type = Int;
}

Variant::Variant(float value) : _floatValue(value)
{
	_type = Float;
}

Variant::Variant(bool value) : _boolValue(value)
{
	_type = Bool;
}

Variant::Variant(std::string value) : _strValue(value)
{
	_type = String;
}

VariantType Variant::getType()
{
	return _type;
}

int Variant::getIntValue()
{
	return _intValue;
}

float Variant::getFloatValue()
{
	return _floatValue;
}

bool Variant::getBoolValue()
{
	return _boolValue;
}

std::string Variant::getStringValue()
{
	return _strValue;
}
