#pragma once

class Temperature
{
public:
	Temperature(double temp) : temperature(temp) {};
	Temperature operator+(double delta) { return Temperature(this->temperature + delta); }
	Temperature operator-(double delta) { return Temperature(this->temperature - delta); }

private:
	double temperature;
};
