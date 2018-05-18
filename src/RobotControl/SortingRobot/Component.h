// Component.h

// Defines a signature for a callback
#pragma once

class Component
{
public:
	virtual void loop() = 0;

	virtual void setup() = 0;
};

