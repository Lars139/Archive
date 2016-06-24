int smbus_read_bloc_data();
//	the function return block of 32 bytes data. 
//	data.block[0] is the number of bytes in the info.

i2cdev_ioctl(int d, int request);
//	manipulate the device 
//	use for handshaking
