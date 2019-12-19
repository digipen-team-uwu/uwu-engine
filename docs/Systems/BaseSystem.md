# Base System

Base system is the "base system" of the [UWU Engine](../../README.md)

Systems are where all the engine logics are being stored in. 


All systems need to inherit from the according specialized base system class and implement their constructor, destructor and update function for system initialization, shutdown and update. The systems will be registered by the system updater when it inherits the base system class specialization.

The system init order, update order are specified in `SystemOrder.h`.
