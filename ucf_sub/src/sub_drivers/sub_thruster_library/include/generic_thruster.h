#ifndef Generic_Thruster_H
#include "i2c_interface.h"
#include <string>

////////////////////////////////////////////////////////////////////////////////
/// \brief Abstract base class for AUV thrusters on the robotics club vehicle
/// 
/// Specifies methods for setting output
///
////////////////////////////////////////////////////////////////////////////////
class GenericThruster
{
public:
GenericThruster();

////////////////////////////////////////////////////////////////////////////////
/// \brief Disables copy constructors for thrusters
/// Thruster objects usually get completely rekt by copying because then they get
/// destroyed when they fall out of scope, which closes the file handle and fucks up
/// all the other thruster objects that got copied from the original
////////////////////////////////////////////////////////////////////////////////
GenericThruster(GenericThruster const &) = delete;
void operator=(GenericThruster const &x) = delete;

~GenericThruster();

////////////////////////////////////////////////////////////////////////////////
/// \brief Function for setting the thruster's velocity.
///
/// Overload to set thruster direction and power as a ratio of maximum supported velocity
///
/// \param velocity_ratio    The ratio between -1.0 and 1.0 for thruster power.
////////////////////////////////////////////////////////////////////////////////
virtual void setVelocityRatio(double  velocity_ratio) = 0;
////////////////////////////////////////////////////////////////////////////////
/// \brief linearizes thruster output and almost eliminates deadzone
///
/// Function that takes desired thrust output as a fraction from 1.0 to -1.0 and
/// applies a linear function based on data from the manufacturer so that deadband is 
/// reduced to a range from 0.01 to -0.01 and maximum output is the same in both 
/// directions
///
/// \param velocity_desired desired thruster output
////////////////////////////////////////////////////////////////////////////////
virtual double linearizeOutput(double velocity_desired) = 0;
////////////////////////////////////////////////////////////////////////////////
/// \brief Forces the thruster to update its most recent status data.
///
/// Initiates communication to the thruster and retrieves all status bytes
/// supported by some thrusters for use in status exposure functions.
////////////////////////////////////////////////////////////////////////////////
virtual void updateStatus() = 0;

////////////////////////////////////////////////////////////////////////////////
/// \brief Get the current voltage supplied to the thruster.
///
////////////////////////////////////////////////////////////////////////////////
virtual double getVoltage() = 0;

////////////////////////////////////////////////////////////////////////////////
/// \brief Get the temperature of the ESC in degrees Celsius.
///
////////////////////////////////////////////////////////////////////////////////
virtual double getTemperature() = 0;

////////////////////////////////////////////////////////////////////////////////
/// \brief Get the current supplied to the thruster.
///
////////////////////////////////////////////////////////////////////////////////
virtual double getCurrent() = 0;

////////////////////////////////////////////////////////////////////////////////
/// \brief Checks that the ESC is communicating as expected.
///
////////////////////////////////////////////////////////////////////////////////
virtual bool isAlive() = 0;

////////////////////////////////////////////////////////////////////////////////
/// \brief returns a string indicating what make and model of thruster is being controlled
////////////////////////////////////////////////////////////////////////////////

virtual std::string getType() = 0;

virtual bool inLimits() = 0;

private:

ByteBuffer status_data_;
I2C_Interface i2c_interface_;
};

#endif
